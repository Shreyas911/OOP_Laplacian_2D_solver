#!/bin/bash

# Declare all configurations you want here
declare -a n=(7 8 9 10 15 20 25 50)
declare -a solvers=("petsc")
declare -a dimensions=(2)
declare -a orders=(4)

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
			### Create empty files (temporary) to store the output - n L2_error Time	
			>temp.tmp
			> output_${solver}_dim${dimension}_order${order}.dat		
			for i in "${n[@]}"
			do 
				echo $i
				awk -v num_points=$i '{if($1 ~ /grid_points/){$3 = num_points;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
				./heat_solve >> temp.tmp
				### Store reference outputs for regression test
				#cp  data.h5 reference_sol_${solver}_dim${dimension}_order${order}_n${i}.h5
			done
			
			echo "n       L2_error          Time taken" >> output_${solver}_dim${dimension}_order${order}.dat
			awk '{if($1 == "L2"){printf("%s %s ", $7, $9);}if($1 == "Total"){print $5;}}' temp.tmp >> output_${solver}_dim${dimension}_order${order}.dat
			rm temp.tmp

		done

	done
        ### Notice that the plotting is done outside the order loop.
done
