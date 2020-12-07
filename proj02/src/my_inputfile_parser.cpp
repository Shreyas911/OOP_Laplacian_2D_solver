#include <iostream>
#include <grvy.h>
#include "global_variables.h"

using namespace std;
using namespace GRVY;

GRVY_Input_Class iparse;

class my_inputfile_parser{

public:
	// Declare and read variables
	int n, dimension, accuracy, MAX_ITERS, order, nn, dim_system, verification_mode;
	double L, TOL, dx, k_0;
	double** A;
	double *q, *T_exact, *T_computed, *delta_T;
	std::string solver, mode;
	void parse_input_file();
};	

void my_inputfile_parser::parse_input_file(){

		gt.BeginTimer(__func__);
		grvy_log_setlevel(GRVY_INFO);
	
		if(! iparse.Open("./input.dat"))
    			exit(1);

		// BE WARNED - Post-processing scripts grep and awk for certain 
		// strings to parse std::out properly, change print
		// statements after careful consideration

		if( iparse.Read_Var("verification",&verification_mode) )
			printf("--> %-11s = %i\n","verification_mode",verification_mode);

		if( iparse.Read_Var("mode",&mode) )
			printf("--> %-11s = %s\n","mode",mode.c_str());

		// Set debug mode if the input specification is such
		std::string str1 ("debug");
		if(mode.compare(str1) == 0)
			grvy_log_setlevel(GRVY_DEBUG);
			
		if( iparse.Read_Var("grid/grid_points",&n,0) )
    			printf("--> %-11s = %i\n","n",n);
		if( n < 2 ) cerr << "Invalid value for number of gridpoints, has to be >= 2";

        	if( iparse.Read_Var("grid/dimension",&dimension,0) )
                	printf("--> %-11s = %i\n","dimension",dimension);
        	if( dimension != 1 && dimension != 2 ) cerr << "Invalid value for dimension of domain, choose 1 or 2";

       		if( iparse.Read_Var("grid/length",&L,0.) )
                	printf("--> %-11s = %f\n","length",L);
		if( L <= 0.) cerr << "Invalid length of domain, has to be > 0";

        	if( iparse.Read_Var("solver/order",&order,0) )
                	printf("--> %-11s = %i\n","order",order);
		if( order != 2 && order != 4 ) cerr << "Invalid order of solver accuracy. Choose 2 or 4.";

	        if( iparse.Read_Var("solver/error_TOL",&TOL,0.) )
        	        printf("--> %-11s = %.17g\n","error_TOL",TOL);	

		if( iparse.Read_Var("solver/thermal_conductivity",&k_0,2.) )
                	printf("--> %-11s = %f\n","thermal_conductivity",k_0);
		if ( k_0 < 0. ) cerr << "Invalid value for thermal conductivity. Needs to be > 0";

		if( iparse.Read_Var("solver/max_iters",&MAX_ITERS,10000000) )
                	printf("--> %-11s = %i\n","max_iters",MAX_ITERS);
		if ( MAX_ITERS < 1 ) cerr << "Invalid number for maximum number of iterations. Needs to be >= 1";

		if( iparse.Read_Var("solver/solver_name",&solver) )
                	printf("--> %-11s = %s\n","solver",solver.c_str());

		std::string str2 ("jacobi"), str3 ("gauss");
		if ( solver.compare(str2) != 0 && solver.compare(str3) != 0 ) cerr << "Invalid solver name. Use either gauss or jacobi.";
		// nn is useful for 2D
		nn = n*n;
		dx = L/(n-1);
		gt.EndTimer(__func__);
}

