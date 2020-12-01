#include <cmath>
#include <cstring>
#include <iostream>
#include "global_variables.h" // To bring the same GRVY_Timer_Class object into all files

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

// This function is called in the main function, it just calls the right solver based on if statements.
double *solve(const std::string& solver, int n, double** A, double *q, double TOL, unsigned int MAX_ITERS){

	gt.BeginTimer(__func__);
	std::string str1 ("jacobi");
	std::string str2 ("gauss");
	
	if(solver.compare(str1) == 0){ 
		gt.EndTimer  (__func__);
		return jacobi(n, A, q, TOL, MAX_ITERS);
	}

	else if(solver.compare(str2) == 0){
		gt.EndTimer  (__func__);
		return gauss(n, A, q, TOL, MAX_ITERS);
	}
	else{
		gt.EndTimer  (__func__);
		return NULL;
	}
} 
