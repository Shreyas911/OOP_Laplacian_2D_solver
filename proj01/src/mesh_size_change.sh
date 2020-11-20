#!/bin/bash

# Declare all configurations you want here
declare -a n=(10 20 30 40 50 75 100 150 200 300)
declare -a solvers=("gauss" "jacobi")
declare -a dimensions=(1)
declare -a orders=(2 4)

### This line is necessary to let the code know that output.log exists, we use it to create reference solutions
> output.log
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
				### output.log also gets modified automatically
				./heat_solve >> temp.tmp
				### Store output.log files for reference for regression test
				## cp output.log reference_sol_${solver}_dim${dimension}_order${order}_n${i}.log
			done

			echo "n       L2_error          Time taken" >> output_${solver}_dim${dimension}_order${order}.tmp
			
			awk '{if($1 == "L2"){printf("%s %s ", $7, $9);}if($1 == "Total"){print $5;}}' temp.tmp >> output_${solver}_dim${dimension}_order${order}.tmp

			### Remove the temporary file
			rm temp.tmp

		done

	done
        ### Notice that the plotting is done outside the order loop.
        gnuplot -e "dimension = '${dimension}'" plot_convergence.script
done
