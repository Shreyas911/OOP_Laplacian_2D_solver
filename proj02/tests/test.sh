#!/usr/bin/env bats
# To use bats, type - export  PATH=/work/00161/karl/stampede2/public/bats/bin/:$PATH
### Basic test that the code is working and is in verification mode 
### Also ensure that module hdf5 is loaded

cd ../src/

@test "verify that the code is compiling" {

        awk -v dimension=1 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v solver='gauss' '{if($1 ~ /solver_name/){$3 = solver;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat   
        awk -v order=2 '{if($1 ~ /order/){$3 = order;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v num_points=10 '{if($1 ~ /grid_points/){$3 = num_points;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat

	run heat_solve 
	[ "$status" -eq 0 ]
}

@test "verify that the verification mode runs fine" {

        run heat_solve
        [ "$status" -eq 0 ]
        [ "${lines[0]}" = "--> verification_mode = 1" ]
        
        ./heat_solve | grep -q "VERIFICATION"
        [ "$status" -eq 0 ]

}

### Test that all configurations give the same output as their reference output files
### Full of awk commands changing ../src/input.dat, followed by running heat_solve
### followed by checking data.h5 against a reference log file
@test "verify all gauss solver outputs match reference outputs" {
	

	awk -v dimension=1 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
	awk -v solver='gauss' '{if($1 ~ /solver_name/){$3 = solver;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat	
	awk -v order=2 '{if($1 ~ /order/){$3 = order;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
	awk -v num_points=100 '{if($1 ~ /grid_points/){$3 = num_points;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        run heat_solve 
	[ "$status" -eq 0 ]

	run h5diff -p 0.000000000000001 data.h5 reference_sol_gauss_dim1_order2_n100.h5 "temperature/Numerical Temperature"
	[ "$status" -eq 0 ]

        awk -v dimension=1 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v solver='gauss' '{if($1 ~ /solver_name/){$3 = solver;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v order=4 '{if($1 ~ /order/){$3 = order;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v num_points=100 '{if($1 ~ /grid_points/){$3 = num_points;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        run heat_solve
        [ "$status" -eq 0 ]

        run h5diff -p 0.000000000000001 data.h5 reference_sol_gauss_dim1_order4_n100.h5 "temperature/Numerical Temperature"
        [ "$status" -eq 0 ]

        awk -v dimension=2 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v solver='gauss' '{if($1 ~ /solver_name/){$3 = solver;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v order=2 '{if($1 ~ /order/){$3 = order;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v num_points=10 '{if($1 ~ /grid_points/){$3 = num_points;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        run heat_solve
        [ "$status" -eq 0 ]

        run h5diff -p 0.000000000000001 data.h5 reference_sol_gauss_dim2_order2_n10.h5 "temperature/Numerical Temperature"
        [ "$status" -eq 0 ]

        awk -v dimension=2 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v solver='gauss' '{if($1 ~ /solver_name/){$3 = solver;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v order=4 '{if($1 ~ /order/){$3 = order;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v num_points=10 '{if($1 ~ /grid_points/){$3 = num_points;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        run heat_solve
        [ "$status" -eq 0 ]

        run h5diff -p 0.000000000000001 data.h5 reference_sol_gauss_dim2_order4_n10.h5 "temperature/Numerical Temperature"
        [ "$status" -eq 0 ]
}

@test "verify all jacobi solver outputs match reference outputs" {

        awk -v dimension=1 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v solver='jacobi' '{if($1 ~ /solver_name/){$3 = solver;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v order=2 '{if($1 ~ /order/){$3 = order;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v num_points=100 '{if($1 ~ /grid_points/){$3 = num_points;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        run heat_solve
        [ "$status" -eq 0 ]

        run h5diff -p 0.000000000000001 data.h5 reference_sol_jacobi_dim1_order2_n100.h5 "temperature/Numerical Temperature"
        [ "$status" -eq 0 ]

        awk -v dimension=2 '{if($1 ~ /dimension/){$3 = dimension;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v solver='jacobi' '{if($1 ~ /solver_name/){$3 = solver;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v order=2 '{if($1 ~ /order/){$3 = order;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        awk -v num_points=10 '{if($1 ~ /grid_points/){$3 = num_points;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat
        run heat_solve
        [ "$status" -eq 0 ]

        run h5diff -p 0.000000000000001 data.h5 reference_sol_jacobi_dim2_order2_n10.h5 "temperature/Numerical Temperature"
        [ "$status" -eq 0 ]
}

@test "verify that the debug mode runs fine" {
		
	awk -F " " -v temp='debug' '{if($1 ~ /mode/){$3 = temp;} print $0;}' input.dat > input.tmp && mv input.tmp input.dat 

        run heat_solve
        [ "$status" -eq 0 ]

        ./heat_solve | grep -q "DEBUG"
        [ "$status" -eq 0 ]	
}
