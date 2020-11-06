#include <iostream>
#include <fstream>
#include <cmath>
#include "solvers.h"
#include "matrix_assemble.h"
#include "q_assemble.h"
#include <masa.h>
#include <grvy.h>
#include "T_exact_assemble.h"

using namespace std;
using namespace MASA; 
using namespace GRVY;

int main(int argc, char *argv[]) {
	
	GRVY_Input_Class iparse;
	int n, dimension, accuracy, MAX_ITERS, order, nn, q_dimensions;
	double L, TOL, dx, k_0;
	double** A;
	double *q, *T_exact, *T_computed, *delta_T;
	std::string solver;
	
	if(! iparse.Open("./input.dat"))
    		exit(1);
	
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

	// Since we don't know if the user chose 1D or 2D, the dimennsions could be n or nn
	if (dimension == 1) q_dimensions = n;
	else if (dimension == 2) q_dimensions = nn;
	else cout << "dimensions can only be 1 or 2." << endl;
	
	T_computed = solve(solver, q_dimensions, A, q, TOL, MAX_ITERS);
	T_exact = assemble_T_exact(n, order, dimension, L, k_0);
	delta_T = new double[q_dimensions];

/*	cout << endl;
	printf("%-11s    %-11s    %-11s\n", "q", "MASA", "Computed");
	for (int k = 0; k < q_dimensions; k++){
		delta_T[k] = T_exact[k] - T_computed[k];
		printf("%-11f    %-11f    %-11f\n",q[k], T_exact[k],T_computed[k]);
	}
	printf("%-20s    %-11f\n","L2 norm of error", l2_norm(q_dimensions, delta_T));
*/	

	ofstream myfile ("output.log");
	
	if (myfile.is_open()){
		myfile << "#x  Exact  Computed" << endl;
    		for(int k = 0; k < q_dimensions; k++){
        		myfile << k*dx << "  " << T_exact[k] << "  " << T_computed[k] << endl ;
  	  	}
    		myfile.close();
	}
  	else cout << "Unable to open file";

/*	cout << "[";
	for(int i = 0; i < q_dimensions; i++){
		for(int j = 0; j < q_dimensions; j++){
			cout << A[i][j]<<" ";		
		}
		cout << ";" << endl;
	}
*/	
  return 0;
}	
