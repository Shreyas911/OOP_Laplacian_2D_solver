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
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace MASA; 
using namespace GRVY;

GRVY_Timer_Class gt;
GRVY_Input_Class iparse;

int main(int argc, char *argv[]) {
	
	grvy_log_setlevel(GRVY_INFO);
	
	gt.Init("GRVY Performance timing");
	gt.BeginTimer(__func__);

	int n, dimension, accuracy, MAX_ITERS, order, nn, dim_system, verification_mode;
	double L, TOL, dx, k_0;
	double** A;
	double *q, *T_exact, *T_computed, *delta_T;
	std::string solver, mode;
	
	if(! iparse.Open("./input.dat"))
    		exit(1);

	if( iparse.Read_Var("verification_mode",&verification_mode) )
		printf("--> %-11s = %i\n","verification_mode",verification_mode);

	if( iparse.Read_Var("mode",&mode) )
                printf("--> %-11s = %s\n","solver",mode.c_str());

	std::string str1 ("debug");
	if(mode.compare(str1) == 0)
		grvy_log_setlevel(GRVY_DEBUG);
			
	if( iparse.Read_Var("grid/grid_points",&n,0) )
    		printf("--> %-11s = %i\n","n",n);

        if( iparse.Read_Var("grid/dimension",&dimension,0) )
                printf("--> %-11s = %i\n","dimension",dimension);

        if( iparse.Read_Var("grid/length",&L,0.) )
                printf("--> %-11s = %f\n","length",L);

        if( iparse.Read_Var("solver/order",&order,0) )
                printf("--> %-11s = %i\n","order",order);

        if( iparse.Read_Var("solver/error_TOL",&TOL,0.) )
                printf("--> %-11s = %f\n","error_TOL",TOL);

        if( iparse.Read_Var("solver/thermal_conductivity",&k_0,2.) )
                printf("--> %-11s = %f\n","thermal_conductivity",k_0);

        if( iparse.Read_Var("solver/max_iters",&MAX_ITERS,0) )
                printf("--> %-11s = %i\n","max_iters",MAX_ITERS);

	if( iparse.Read_Var("solver/solver_name",&solver) )
                printf("--> %-11s = %s\n","solver",solver.c_str());

	nn = n*n;
	dx = L/(n-1);
	
	A = assemble_A(n, order, dimension);
	q = assemble_q(n, order, dimension, L, k_0);
	T_exact = assemble_T_exact(n, order, dimension, L, k_0);
	
	// Since we don't know if the user chose 1D or 2D, the dimennsions could be n or nn
	
	if (dimension == 1) dim_system = n;
	else if (dimension == 2) dim_system = nn;
	else cout << "dimensions can only be 1 or 2." << endl;
	
	T_computed = solve(solver, dim_system, A, q, TOL, MAX_ITERS);

	//// VERIFICATION MODE
	
	print_verification_mode(T_exact, T_computed, delta_T, dim_system, verification_mode);

	//// Write results to output.log file

	write_results_output_file(dx, T_exact, T_computed, n);

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
