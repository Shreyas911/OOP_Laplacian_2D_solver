#include <cmath>
#include <cstring>
#include <iostream>
#include "global_variables.h" // To bring the same GRVY_Timer_Class object into all files
#ifdef INCLUDE_PETSC
#include <petsc.h>
#endif

using namespace std;

// Finds root mean square norm of a vector
double l2_norm(int n, double *x){

	gt.BeginTimer(__func__);

	double norm = 0;

	for(int i=0;i<n;i++){
		norm += pow(x[i], 2);
	}
	norm = norm/n;
	norm = pow(norm, 0.5);

	gt.EndTimer(__func__);

	return norm;
}

// Solves linear system AT=q using jacobi method
double *jacobi(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS){

	gt.BeginTimer(__func__);

	unsigned int iters = 0;
	double error = 0.0;
        
	double* T = new double[n]{0.}; 
	double T_old[n];
	double delta_T[n];

	while (iters <  MAX_ITERS){
		
		// Set T_old equal to T from previous iteration
		for (int i = 0; i < n; i++){
			T_old[i] = T[i];
		}

		for (int i = 0; i < n; i++){
			T[i] = q[i];
			
			double temp_sum = 0.;

			for (int j = 0; j < n; j++){

				// Notice that T_old has been used for this step
				temp_sum += A[i][j]*T_old[j];

			}
			
			temp_sum = temp_sum - A[i][i]*T_old[i]; 
			T[i] = T[i]-temp_sum;
			T[i] = T[i]/A[i][i];
			delta_T[i] = T[i] - T_old[i];
		}

		error = l2_norm(n,delta_T);
		iters++;

		if (error < TOL){
			break;
		}
	}

	gt.EndTimer(__func__);

	return T;
}

// Solves linear system AT=q using gauss seidel method
double *gauss(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS){

	gt.BeginTimer(__func__);

	unsigned int iters = 0;
	double error = 0.0;
	double* T = new double[n]{0.}; 
	double T_old[n];
	double delta_T[n];

	while (iters <  MAX_ITERS){
		
		// Set T_old equal to T from previous iteration
                for (int i = 0; i < n; i++){
                        T_old[i] = T[i];
                }

		for (int i = 0; i < n; i++){
			T[i] = q[i];
			double temp_sum = 0.;

			// Notice that T has been used for this step
			
			for (int j = 0; j < i; j++){
				temp_sum += A[i][j]*T[j];
			}
		
			for (int j = i+1; j < n; j++){
				temp_sum += A[i][j]*T[j];
			}

			T[i] = T[i] - temp_sum; 
			T[i] = T[i]/A[i][i];
			delta_T[i] = T[i] - T_old[i];

		}
		
		error = l2_norm(n,delta_T);
		iters++;

		if (error < TOL){
			break;	
		}
	}

	gt.EndTimer(__func__);

	return T;
}

#ifdef INCLUDE_PETSC

double * petsc(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS){

	gt.BeginTimer(__func__);

	double* T = new double[n]{0.};
	PetscErrorCode ierr;
        KSP petsc_solver; PC Prec; Mat petsc_A; Vec petsc_q, petsc_T;
        PetscInt max_its = (PetscInt) MAX_ITERS;
	PetscScalar v; PetscReal tol = (PetscReal) TOL;
	KSPConvergedReason reason;
 
	ierr = MatCreate(PETSC_COMM_WORLD, &petsc_A); 
	ierr = VecCreate(PETSC_COMM_WORLD, &petsc_T); 
	ierr = VecCreate(PETSC_COMM_WORLD, &petsc_q); 
	ierr = MatSetSizes(petsc_A, PETSC_DECIDE, PETSC_DECIDE, n, n); 
	ierr = VecSetSizes(petsc_T, PETSC_DECIDE, n); 
	ierr = VecSetSizes(petsc_q, PETSC_DECIDE, n); 
	ierr = MatSetUp(petsc_A); 
	ierr = VecSetUp(petsc_T); 
	ierr = VecSetUp(petsc_q); 

        for(int i=0; i < n;i++){
		
		v = (PetscScalar) q[i];
		ierr = VecSetValues(petsc_q,1,&i,&v,INSERT_VALUES); 
                ierr = VecSetValues(petsc_T,1,&i,&v,INSERT_VALUES); 

		for(int j=0; j < n; j++){
			v = (PetscScalar) A[i][j];
                	ierr = MatSetValues(petsc_A,1,&i,1,&j,&v,INSERT_VALUES); 
       		}
	}
        ierr = MatAssemblyBegin(petsc_A,MAT_FINAL_ASSEMBLY); 
        ierr = MatAssemblyEnd(petsc_A,MAT_FINAL_ASSEMBLY); 
       	ierr = VecAssemblyBegin(petsc_q); 
	ierr = VecAssemblyEnd(petsc_q); 
        ierr = VecAssemblyBegin(petsc_T); 
        ierr = VecAssemblyEnd(petsc_T); 
	
	ierr = KSPCreate(PETSC_COMM_WORLD,&petsc_solver); 
	ierr = KSPSetOperators(petsc_solver,petsc_A,petsc_A); 
	ierr = KSPSetType(petsc_solver,KSPGMRES); 
	ierr = KSPGetPC(petsc_solver,&Prec); 
	ierr = PCSetType(Prec,PCJACOBI); 
	ierr = KSPSetTolerances(petsc_solver, tol, tol, PETSC_DEFAULT, max_its);
	ierr = KSPSolve(petsc_solver,petsc_q,petsc_T); 
	ierr = KSPGetConvergedReason(petsc_solver,&reason); 

	for(int i = 0; i < n; i++){
		ierr = VecGetValues(petsc_T,1,&i,&v); 
		T[i] = (double) v;
	}
	ierr = KSPDestroy(&petsc_solver); 
	ierr = VecDestroy(&petsc_q); 
	ierr = VecDestroy(&petsc_T); 
	ierr = MatDestroy(&petsc_A); 
	ierr = PetscFinalize(); 

	
	
	
	
	cout << "Hey man, I ran to completion" << endl;
	
	gt.EndTimer(__func__);
	return T;
}

#endif
// This function is called in the main function, it just calls the right solver based on if statements.
double *solve(const std::string& solver, int n, double** A, double *q, double TOL, unsigned int MAX_ITERS){

	gt.BeginTimer(__func__);
	std::string str1 ("jacobi");
	std::string str2 ("gauss");
	std::string str3 ("petsc");
	
	if(solver.compare(str1) == 0){ 
		gt.EndTimer  (__func__);
		return jacobi(n, A, q, TOL, MAX_ITERS);
	}

	else if(solver.compare(str2) == 0){
		gt.EndTimer  (__func__);
		return gauss(n, A, q, TOL, MAX_ITERS);
	}
	#ifdef INCLUDE_PETSC
	else if(solver.compare(str3) == 0){
                gt.EndTimer  (__func__);
                return petsc(n, A, q, TOL, MAX_ITERS);
        }
	#endif
	else{
		gt.EndTimer  (__func__);
		return NULL;
	}
} 

