#!/bin/bash

# Declare all configurations you want here
declare -a n=(100)
declare -a solvers=("gauss" "jacobi")
declare -a dimensions=(1)
declare -a orders=(2)

### This line is necessary to let the code know that data.hdf5 exists, we use it to create reference solutions
> data.h5
### This giant loop loops over dimensions, solvers, orders and finally n to produce temporary output files 
### which are used to plot grid convergence

for dimension in "${dimensions[@]}"
do

	awk -v dimension=$dimension '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat

	for solver in "${solvers[@]}"
	do

		awk -v solver=$solver '{if($1 ~ /solver_name/){$3 = solver;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat

		for order in "${orders[@]}"
		do
		
			awk -v order=$order '{if($1 ~ /order/){$3 = order;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
		
			for i in "${n[@]}"
			do 

				awk -v num_points=$i '{if($1 ~ /grid_points/){$3 = num_points;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
				./heat_solve
				### Store reference outputs for regression test
				cp  data.h5 reference_sol_${solver}_dim${dimension}_order${order}_n${i}.h5
			done
		done

	done
        ### Notice that the plotting is done outside the order loop.
done
