# profile.py
#
#

import subprocess
import timeit

def test():
    '''
    '''

    typical_benchmark_time = 21.0
    target_benchmark_time = 19.25
    cheater_benchmark_time = 18.0
    time = timeit.timeit('''subprocess.Popen(['./main.exe'], stdout=subprocess.PIPE).communicate()''', setup='import subprocess', number=1000)
     
    if time < typical_benchmark_time:
        if time < cheater_benchmark_time:
            print('??? Your profile time {}s is much less than expected! Did you cheat? This will be evaluated case-by-case...'.format(time))
            return False

        if time < target_benchmark_time:
            print('Success! Profile time of {}s less than the target benchmark timing!'.format(time))
            return True
        print('Execution time {}s is under the typical timing of {}s'.format(time, typical_benchmark_time))

    print('Execution time {}s is greater than the target benchmark of {}s'.format(time, target_benchmark_time))
    return False

if __name__ == '__main__':
    test()
