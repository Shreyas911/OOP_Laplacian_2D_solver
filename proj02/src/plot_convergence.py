import numpy as np
import pandas as pd
import os
import matplotlib as mpl
### Use non-interactive backend on stampede2 since te DISPLAY env variable is not set
#if os.environ.get('DISPLAY','') == '':
#    print('no display found. Using non-interactive Agg backend')
#    mpl.use('Agg')
import matplotlib.pyplot as plt

n = []
l2norm = []
time = []
orders = [2, 4]
dimensions = [1, 2]

### Compare error norms for gauss and petsc solvers
solvers = ['gauss', 'petsc']

for order in orders:
	for dimension in dimensions:
		for solver in solvers:

			with open('output_'+solver+'_dim'+str(dimension)+'_order'+str(order)+'.dat', 'r') as f:
				next(f)
				for line in f:
					values = [float(s) for s in line.split()]
					n.append(values[0])
					l2norm.append(values[1])
			f.close()
			slope, intercept = np.polyfit(np.log(n), np.log(l2norm), 1)
			plt.xscale("log")
			plt.yscale("log")
			plt.plot(n,l2norm, label=solver+" slope "+str(slope))
			plt.scatter(n,l2norm, label=solver)
			plt.title("l2_norm_residual vs n for dimension "+str(dimension)+" order "+str(order))
			plt.xlabel("n")
			plt.ylabel("l2norm")
			n = []
			l2norm = []
		plt.legend()
		plt.savefig('l2norm_petsc_gauss_order_'+str(order)+'_dimension_'+str(dimension))
		plt.clf()

### Time comparison plots for all 3 solvers
solvers = ['gauss', 'petsc', 'jacobi']
orders = [2]
for order in orders:
	for dimension in dimensions:
		for solver in solvers:
			with open('output_'+solver+'_dim'+str(dimension)+'_order'+str(order)+'.dat', 'r') as f:
				next(f)
				for line in f:
					values = [float(s) for s in line.split()]
					n.append(values[0])
					time.append(values[2])
			f.close()
			plt.xscale("log")
			plt.yscale("log")
			plt.plot(n, time, label=solver)
			plt.scatter(n, time, label=solver)
			plt.title("Time taken vs n for dimension "+str(dimension)+" order "+str(order))
			plt.xlabel("n")
			plt.ylabel("Time")
			n = []
			time = []
		plt.legend()
		plt.savefig('time_all_solvers_order_'+str(order)+'_dimension_'+str(dimension))
		plt.clf()

solvers = ['gauss', 'petsc']
orders = [4]
for order in orders:
	for dimension in dimensions:
		for solver in solvers:
			with open('output_'+solver+'_dim'+str(dimension)+'_order'+str(order)+'.dat', 'r') as f:
				next(f)
				for line in f:
					values = [float(s) for s in line.split()]
					n.append(values[0])
					time.append(values[2])
			f.close()
			plt.xscale("log")
			plt.yscale("log")
			plt.plot(n, time, label=solver)
			plt.scatter(n, time, label=solver)
			plt.title("Time taken vs n for dimension "+str(dimension)+" order "+str(order))
			plt.xlabel("n")
			plt.ylabel("Time")
			n = []
			time = []

		plt.legend()
		plt.savefig('time_all_solvers_order_'+str(order)+'_dimension_'+str(dimension))
		plt.clf()


