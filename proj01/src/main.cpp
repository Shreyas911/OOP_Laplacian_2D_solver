#include <iostream>
#include <fstream>
#include <cmath>
#include "solvers.h"
#include "matrix_assemble.h"
#include "q_assemble.h"
#include <masa.h>
#include <grvy.h>
#include "T_exact_assemble.h"
#include "global_variables.h"
#include "print.h"
//#include <boost/test/unit_test.hpp>

using namespace std;
using namespace MASA; 
using namespace GRVY;

GRVY_Timer_Class gt;
GRVY_Input_Class iparse;

int main(int argc, char *argv[]) {
	
	grvy_log_setlevel(GRVY_INFO);
	// Initialize timer function
	gt.Init("GRVY Performance timing");
	gt.BeginTimer(__func__);
	
	// Declare and read variables
	int n, dimension, accuracy, MAX_ITERS, order, nn, dim_system, verification_mode;
	double L, TOL, dx, k_0;
	double** A;
	double *q, *T_exact, *T_computed, *delta_T;
	std::string solver, mode;
	
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
	
	// Assemble the linear system
	A = assemble_A(n, order, dimension);
	q = assemble_q(n, order, dimension, L, k_0);
	T_exact = assemble_T_exact(n, order, dimension, L, k_0);

	// Defensive checks
	if(A == NULL) cerr << "The matrix A formation has an error, NULL pointer returned." << endl;
	if(q == NULL) cerr << "The vector q formation has an error, NULL pointer returned." << endl;
	if(T_exact == NULL) cerr << "The vector T_exact formation has an error, NULL pointer returned." << endl;
	// Since we don't know if the user chose 1D or 2D, the dimensions of the system could be n or nn
	
	if (dimension == 1) dim_system = n;
	else if (dimension == 2) dim_system = nn;
	else cout << "dimensions can only be 1 or 2." << endl;
	
	// Solve the linear system
	T_computed = solve(solver, dim_system, A, q, TOL, MAX_ITERS);
	if(T_computed == NULL) cerr << "The vector T_computed formation has an error, NULL pointer returned." << endl;
	//// VERIFICATION MODE
	
	print_verification_mode(T_exact, T_computed, delta_T, n, verification_mode, dimension);

	//// Write results to output.log file

	write_results_output_file(dx, T_exact, T_computed, n, dimension);

	//// DEBUG MODE
	
	print_matrix_A(A, dim_system);
	print_vector_q(q, dim_system);
	print_compare_q_Texact_Tcomputed(q, T_exact, T_computed, dim_system);
	
	//// DEALLOCATE MEMORY

	delete[] q;
	delete[] T_exact;
	delete[] T_computed;
	delete[] delta_T;
	for(int i = 0; i < dim_system; i++){
		delete[] A[i];
	}
	delete[] A;

	////End timers

	gt.EndTimer  (__func__);
	gt.Finalize();
	gt.Summarize();

	return 0;
}	
