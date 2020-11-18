#!/bin/bash

# Declare all configurations you want here
declare -a n=(7)
declare -a solvers=("gauss" "jacobi")
declare -a dimensions=(1 2)
declare -a orders=(2 4)

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
			> output_${solver}_dim${dimension}_order${order}.tmp	
			
			for i in "${n[@]}"
			do 

				awk -v num_points=$i '{if($1 ~ /grid_points/){$3 = num_points;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
				./heat_solve >> temp.tmp
			done

			echo "n       L2_error          Time taken" >> output_${solver}_dim${dimension}_order${order}.tmp
			
			awk '{if($1 == "L2"){printf("%s %s ", $7, $9);}if($1 == "Total"){print $5;}}' temp.tmp >> output_${solver}_dim${dimension}_order${order}.tmp

			### Remove the temporary file
			rm temp.tmp

		done

		### Notice that the plotting is done outside the order loop.
		gnuplot -e "solver = '${solver}'; dimension = '${dimension}'" plot_convergence.script

	done

done
