#include <iostream>
#include <cmath>
#include "solvers.h"
#include "matrix_assemble.h"
#include "q_assemble.h"
#include <masa.h>
#include <grvy.h>
#include <hdf5.h>
#include "T_exact_assemble.h"
#include "global_variables.h"
#include "print.h"
#include "my_inputfile_parser.h"

using namespace std;
using namespace MASA;
using namespace GRVY;

class my_solver_class{

public:
	void assemble_linear_system(my_inputfile_parser&);
	void solve_linear_system(my_inputfile_parser&);
	void print_and_write_all(my_inputfile_parser&);
	void deallocate_memory(my_inputfile_parser&);

};

void my_solver_class::assemble_linear_system(my_inputfile_parser& parser){

	gt.BeginTimer(__func__);
	parser.A = assemble_A(parser.n, parser.order, parser.dimension);
	parser.q = assemble_q(parser.n, parser.order, parser.dimension, parser.L, parser.k_0);
	parser.T_exact = assemble_T_exact(parser.n, parser.order, parser.dimension, parser.L, parser.k_0);

	// Defensive checks
	if(parser.A == NULL) cerr << "The matrix A formation has an error, NULL pointer returned." << endl;
	if(parser.q == NULL) cerr << "The vector q formation has an error, NULL pointer returned." << endl;
	if(parser.T_exact == NULL) cerr << "The vector T_exact formation has an error, NULL pointer returned." << endl;

	// Since we don't know if the user chose 1D or 2D, the dimensions of the system could be n or nn

	if (parser.dimension == 1) parser.dim_system = parser.n;
	else if (parser.dimension == 2) parser.dim_system = parser.nn;
	else cout << "dimensions can only be 1 or 2." << endl;

	gt.EndTimer(__func__);
}

void my_solver_class::solve_linear_system(my_inputfile_parser& parser){
	
	gt.BeginTimer(__func__);
	parser.T_computed = solve(parser.solver, parser.dim_system, parser.A, parser.q, parser.TOL, parser.MAX_ITERS);
	if(parser.T_computed == NULL) cerr << "The vector T_computed formation has an error, NULL pointer returned." << endl;
	gt.EndTimer(__func__);
}

void my_solver_class::print_and_write_all(my_inputfile_parser& parser){

	gt.BeginTimer(__func__);	
	//// VERIFICATION MODE
	print_verification_mode(parser.T_exact, parser.T_computed, parser.delta_T, parser.n, parser.verification_mode, parser.dimension);

	//// Write results in hdf5 format

	write_to_hdf5(parser.dimension, parser.n, parser.dim_system, parser.dx, parser.T_exact, parser.T_computed);

	//// DEBUG MODE						
	print_matrix_A(parser.A, parser.dim_system);
	print_vector_q(parser.q, parser.dim_system);
	print_compare_q_Texact_Tcomputed(parser.q, parser.T_exact, parser.T_computed, parser.dim_system);

	gt.EndTimer(__func__);
}

void my_solver_class::deallocate_memory(my_inputfile_parser& parser){
	
	gt.BeginTimer(__func__);
	
	//DEALLOCATE MEMORY

	delete[] parser.q;
	delete[] parser.T_exact;
	delete[] parser.T_computed;

	for(int i = 0; i < parser.dim_system; i++){
		delete[] parser.A[i];
	}	
	delete[] parser.A;

	gt.EndTimer(__func__);
}
