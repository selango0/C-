import glob
import matplotlib

matplotlib.use('Agg')

import matplotlib.pyplot as plt
import numpy as np

files = glob.glob('points_*.dat')

for f in files:
   data = np.genfromtxt(f, unpack=True)
   plt.plot(data[0], data[1], '.')

plt.xlim([-1,7])
plt.ylim([-1,7])
plt.grid()
plt.savefig('scatter.png', bbox_inches='tight')
#plt.show()

