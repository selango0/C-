#!/usr/bin/python3
# make_data.py
#

import pandas as pd
import numpy as np

def main():
    '''
    '''
    data = np.random.random_integers(0, 100, size=[100000, 1])
    np.savetxt('sample_vector_1.dat', data, fmt='%d')

    data = np.random.random_integers(0, 100, size=[100000, 1])
    np.savetxt('sample_vector_2.dat', data, fmt='%d')


if __name__ == '__main__':
    main()

