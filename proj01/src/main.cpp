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

using namespace std;
using namespace MASA; 
using namespace GRVY;

GRVY_Timer_Class gt;

int main(int argc, char *argv[]) {
	grvy_log_setlevel(GRVY_INFO);
	
	GRVY_Input_Class iparse;
	gt.Init("GRVY Performance timing");
	gt.BeginTimer(__func__);

	int n, dimension, accuracy, MAX_ITERS, order, nn, dim_system;
	double L, TOL, dx, k_0;
	double** A;
	double *q, *T_exact, *T_computed, *delta_T;
	std::string solver, mode;
	
	if(! iparse.Open("./input.dat"))
    		exit(1);

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
	delta_T = new double[dim_system];
	
	//// DEBUG MODE	
	grvy_printf(GRVY_DEBUG, "\n");
	grvy_printf(GRVY_DEBUG, "DEBUG MODE - Compare vector values\n");
	grvy_printf(GRVY_DEBUG, "%-11s    %-11s    %-11s\n", "q", "MASA", "Computed");
	
	for (int k = 0; k < dim_system; k++){
	
		delta_T[k] = T_exact[k] - T_computed[k];
		grvy_printf(GRVY_DEBUG, "%-11f    %-11f    %-11f\n", q[k], T_exact[k],T_computed[k]);
	
	}
	//// END DEBUG MODE
	
	printf("%-20s    %-11f\n","L2 norm of error", l2_norm(dim_system, delta_T));

	ofstream myfile ("output.log");
	
	if (myfile.is_open()){
		myfile << "#x       " << std::fixed << "Exact    " << std::fixed << "Computed" << endl;
    		for(int k = 0; k < dim_system; k++){
        		myfile << k*dx << " " << std::fixed << T_exact[k] << " " << std::fixed << T_computed[k] << endl ;
  	  	}
    		myfile.close();
	}
  	else cout << "Unable to open file";

	//// DEBUG MODE
        grvy_printf(GRVY_DEBUG, "\n");
        grvy_printf(GRVY_DEBUG, "DEBUG MODE - printing A and q in MATLAB compatible forms\n");
	grvy_printf(GRVY_DEBUG, "A = [");
	for(int i = 0; i < dim_system; i++){
		for(int j = 0; j < dim_system; j++){

			grvy_printf(GRVY_DEBUG, "%.2f  ", A[i][j]);		

		}
		grvy_printf(GRVY_DEBUG, ";\n"); 
	}
	grvy_printf(GRVY_DEBUG, "]\n");

        grvy_printf(GRVY_DEBUG, "q = [");
        for(int i = 0; i < dim_system; i++){
                        grvy_printf(GRVY_DEBUG, "%-2f\n", q[i]); 
                
        }              
        grvy_printf(GRVY_DEBUG, "]\n");      
	//// END DEBUG MODE
	
	gt.EndTimer  (__func__);
	gt.Finalize();
	gt.Summarize();

	return 0;
}	
