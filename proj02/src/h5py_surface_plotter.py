import h5py
import numpy as np
import os
import matplotlib as mpl
### Use non-interactive backend on stampede2 since te DISPLAY env variable is not set
if os.environ.get('DISPLAY','') == '':
    print('no display found. Using non-interactive Agg backend')
    mpl.use('Agg')
import matplotlib.pyplot as plt

f = h5py.File('output_100x100.h5', 'r')

coordinates = f['coordinates']
temperature = f['temperature']
x_vector = coordinates['x data'][()]
y_vector = coordinates['y data'][()]
T_exact_vector = temperature['Analytical Temperature'][()]
T_computed_vector = temperature['Numerical Temperature'][()]

nn = T_computed_vector.shape[0]
n = int(np.sqrt(nn))
T_computed_matrix = np.zeros((n,n))
T_exact_matrix = np.zeros((n,n))
grid_vector = np.zeros(n)

for i in range(n):
	grid_vector[i] = x_vector[i]
	for j in range(n):
		T_computed_matrix[i,j] = T_computed_vector[i+j*n]
		T_exact_matrix[i,j] = T_exact_vector[i+j*n]

plt.contourf(grid_vector, grid_vector, T_computed_matrix, 100, cmap = "RdBu")
plt.colorbar()
plt.savefig('hdf5_surface_plot.png')
