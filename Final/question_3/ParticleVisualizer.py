# Special visualizer for the Abelian Sandpile Model
#

import matplotlib.pyplot as plt
import numpy as np

plt.ion()
im = []

def setup():
    '''
    Sets up the initial image
    '''
    pass

def plot(data):
    '''
    Updates the image data and refreshes the plot window
    '''
    global im
    for i in range(len(data)/2):
        if len(im) < i+1:
            tmp_handle, = plt.plot(data[i*2], data[i*2 + 1], 'o')
            im.append(tmp_handle)
        else:
            im[i].set_xdata(data[i*2])
            im[i].set_ydata(data[i*2 +1 ])

    plt.draw()

