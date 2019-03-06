#!/usr/bin/python3
import os
import re
import subprocess
import sys
import yaml
sys.dont_write_bytecode=True

class TestCase():
    def __init__(self, case_name, argv, stdin, stdout, stderr, ofstreams, extra_tests):
        self.case_name = case_name.decode('string_escape')
        self.argv = [a.decode('string_escape') for a in argv]
        self.stdin = [i.decode('string_escape') for i in stdin]
        self.stdout = stdout.decode('string_escape')
        self.stderr = stderr.decode('string_escape')
        self.ofstreams = ofstreams
        self.extra_tests = extra_tests

    def execute(self):
        print('Executing {} test case:'.format(self.case_name))

        test_args = [os.path.join(os.getcwd(), 'main.exe')]
        test_args.extend(self.argv)

        proc = subprocess.Popen(test_args, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = proc.communicate('\n'.join(self.stdin))
        
        errors = 0
        errors += self.check_streams('stdout', self.stdout, stdout)
        errors += self.check_streams('stderr', self.stderr, stderr)

        for ofstream in self.ofstreams:
            test_file = ofstream['test-file']
            file_name = ofstream['file-name']
            if test_file and file_name:
                with open(test_file, 'r') as tfile:
                    with open(file_name, 'r') as pfile:
                        errors += self.check_streams(file_name, tfile.read(), pfile.read())

        for extra_test in self.extra_tests:
            print('    Executing: {}'.format(extra_test))
            import extra_test
            if not extra_test.test():
                errors += 1
                print('    Failed!')
        
        return errors
                
    @staticmethod
    def check_streams(stream, expected, received):
        print('    Executing {} stream test'.format(stream))
        for e, r in zip(re.split('\n+', expected), re.split('\n+', received)): 
            if e != r:
                print('    Failure:\n        Expected "{}"\n        Received "{}"'.format(e, r))
                return 1
        return 0

test_matrix = yaml.load(open('test/test_cases.yaml', 'r'))
test_cases = []
for test_case in test_matrix['test-cases']:
    test = test_matrix['test-cases'][test_case]
    test_cases.append(TestCase(test_case, 
                               test['argv'],
                               test['stdin'],
                               test['stdout'],
                               test['stderr'],
                               test['ofstreams'],
                               test['extra-tests']))

errors = 0
for test in test_cases:
    errors += test.execute()
    
print('=======================================================================')
print('{} errors found!'.format(errors if errors else 'No'))

