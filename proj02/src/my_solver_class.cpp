#include <iostream>
#include <cmath>
#include "solvers.h"
#include "matrix_assemble.h"
#include "q_assemble.h"
#include <masa.h>
#include <grvy.h>
#include <hdf5.h>

#ifdef INCLUDE_PETSC
#include <petsc.h>
#endif

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
	#ifdef INCLUDE_PETSC
	void petsc_assemble_linear_system(my_inputfile_parser&, int, char**);
	#endif
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

#ifdef INCLUDE_PETSC
void my_solver_class::petsc_assemble_linear_system(my_inputfile_parser& parser, int argc, char *argv[]){
        
	PetscErrorCode ierr;
        KSP petsc_solver; PC Prec; Mat A; Vec q, T_exact, T_computed, Res;
        PetscInt i_petsc; PetscReal norm;
	PetscScalar v;
        ierr = PetscInitialize(&argc,&argv,0,0); CHKERRV(ierr);
        
	ierr = MatCreate(PETSC_COMM_WORLD, &A); CHKERRV(ierr);
	ierr = VecCreate(PETSC_COMM_WORLD, &T_exact); CHKERRV(ierr);
	ierr = VecCreate(PETSC_COMM_WORLD, &T_computed); CHKERRV(ierr);
	ierr = VecCreate(PETSC_COMM_WORLD, &q); CHKERRV(ierr);
        ierr = MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, parser.dim_system, parser.dim_system); CHKERRV(ierr);
	ierr = VecSetSizes(T_exact, PETSC_DECIDE, parser.dim_system); CHKERRV(ierr);
	ierr = VecSetSizes(T_computed, PETSC_DECIDE, parser.dim_system); CHKERRV(ierr);
	ierr = VecSetSizes(q, PETSC_DECIDE, parser.dim_system); CHKERRV(ierr);
	ierr = MatSetUp(A); CHKERRV(ierr);
	ierr = VecSetUp(T_exact); CHKERRV(ierr);
	ierr = VecSetUp(T_computed); CHKERRV(ierr);
	ierr = VecSetUp(q); CHKERRV(ierr);

        for(int i=0; i < parser.dim_system;i++){
		v = (PetscScalar) parser.q[i];
		ierr = VecSetValues(q,1,&i,&v,INSERT_VALUES); CHKERRV(ierr);
		v = (PetscScalar) parser.T_exact[i];
                ierr = VecSetValues(T_exact,1,&i,&v,INSERT_VALUES); CHKERRV(ierr);
                v = (PetscScalar) parser.T_computed[i];
                ierr = VecSetValues(T_computed,1,&i,&v,INSERT_VALUES); CHKERRV(ierr);

		for(int j=0; j < parser.dim_system; j++){
			v = (PetscScalar) parser.A[i][j];
                	ierr = MatSetValues(A,1,&i,1,&j,&v,INSERT_VALUES); CHKERRV(ierr);
       		}
	}
        ierr = MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY); CHKERRV(ierr);
        ierr = MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY); CHKERRV(ierr);
       	ierr = VecAssemblyBegin(q); CHKERRV(ierr);
	ierr = VecAssemblyEnd(q); CHKERRV(ierr);
        ierr = VecAssemblyBegin(T_exact); CHKERRV(ierr);
        ierr = VecAssemblyEnd(T_exact); CHKERRV(ierr);
        ierr = VecAssemblyBegin(T_computed); CHKERRV(ierr);
        ierr = VecAssemblyEnd(T_computed); CHKERRV(ierr);

	ierr = KSPCreate(PETSC_COMM_WORLD,&petsc_solver); CHKERRV(ierr);
	ierr = KSPSetOperators(petsc_solver,A,A); CHKERRV(ierr);
	ierr = KSPSetType(petsc_solver,KSPGMRES); CHKERRV(ierr);
	//ierr = KSPGetPC(petsc_solver,&Prec); CHKERRV(ierr);
	//ierr = PCSetType(Prec,PCJACOBI); CHKERRV(ierr);
	ierr = KSPSetTolerances(petsc_solver,1.e-30,PETSC_DEFAULT, PETSC_DEFAULT, PETSC_DEFAULT);
	ierr = KSPSolve(petsc_solver,q,T_computed); CHKERRV(ierr);
	KSPConvergedReason reason;
	ierr = KSPGetConvergedReason(petsc_solver,&reason); CHKERRV(ierr);
	ierr = VecDuplicate(T_exact,&Res); CHKERRV(ierr);
	ierr = VecAXPY(Res,-1,T_computed); CHKERRV(ierr);
	ierr = VecNorm(Res,NORM_2,&norm); CHKERRV(ierr);
	norm = norm/PetscSqrtReal((PetscReal) parser.dim_system);
	ierr = PetscPrintf(MPI_COMM_WORLD,"residual norm: %e\n", norm);

	ierr = VecView(T_computed,0);
	ierr = VecView(T_exact,0);
	ierr = VecView(q,0);
	ierr = KSPDestroy(&petsc_solver); CHKERRV(ierr);
	ierr = VecDestroy(&q); CHKERRV(ierr);
	ierr = VecDestroy(&T_exact); CHKERRV(ierr);
	ierr = VecDestroy(&T_computed); CHKERRV(ierr);
	ierr = MatDestroy(&A); CHKERRV(ierr);
	ierr = PetscFinalize(); CHKERRV(ierr);
}
#endif
