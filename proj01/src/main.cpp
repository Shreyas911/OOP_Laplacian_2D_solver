#include <iostream>
#include "solvers.h"
#include "matrix_assemble.h"
#include "q_assemble.h"
#include <masa.h>
#include <grvy.h>

using namespace std;
using namespace MASA; 
using namespace GRVY;

int main(int argc, char *argv[]) {
	
	GRVY_Input_Class iparse;
	int n, dimension, accuracy, MAX_ITERS, order, nn, q_dimensions;
	double L, TOL, dx;
	double** A;
	double *q, *T_exact, *T_computed;
	std::string solver;
	
	if(! iparse.Open("./input.dat"))
    		exit(1);
	
	if( iparse.Read_Var("grid/grid_points",&n,0) )
    		printf("--> %-11s = %i\n","n",n);

        if( iparse.Read_Var("grid/dimension",&dimension,0) )
                printf("--> %-11s = %i\n","dimension",dimension);

        if( iparse.Read_Var("grid/length",&L,0.) )
                printf("--> %-11s = %i\n","length",L);

        if( iparse.Read_Var("solver/order",&order,0) )
                printf("--> %-11s = %i\n","order",order);

        if( iparse.Read_Var("solver/error_TOL",&TOL,0.) )
                printf("--> %-11s = %f\n","error_TOL",TOL);

        if( iparse.Read_Var("solver/max_iters",&MAX_ITERS,0) )
                printf("--> %-11s = %i\n","max_iters",MAX_ITERS);

	if( iparse.Read_Var("solver/solver_name",&solver) )
                printf("--> %-11s = %s\n","solver",solver.c_str());

	nn = n*n;
	dx = L/(n-1);
	
	A = assemble_A(n, order, dimension);
	q = assemble_q(n, order, dimension);
	
	// Since we don't know if the user chose 1D or 2D, the dimennsions could be n or nn
	if (dimension == 1) q_dimensions = n;
	else if (dimension == 2) q_dimensions = nn;
	else cout << "dimensions can only be 1 or 2." << endl;
	
	cout << q_dimensions << endl;
	T_computed = solve(solver, q_dimensions, A, q, TOL, MAX_ITERS);
	T_exact = new double[q_dimensions];
	
	for(int k = 0; k < q_dimensions; k++){
		cout << T_computed[k] << endl;
	}
}	
