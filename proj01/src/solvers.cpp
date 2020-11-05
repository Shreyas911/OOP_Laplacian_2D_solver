#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

double l2_norm(int n, double *x){

	double norm = 0;

	for(int i=0;i<n;i++){
		norm += pow(x[i], 2);
	}
	norm = pow(norm, 0.5);

	return norm;
}

double *jacobi(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS){

	unsigned int iters = 0;
	double error = 0.0;
    double* T = new double[n]; 
	double T_old[n];
	double delta_T[n];

	while (iters <  MAX_ITERS){

		memcpy(T_old, T, sizeof(T_old));

		for (int i = 0; i < n; i++){
			T[i] = q[i];
			
			double temp_sum = 0.;
			for (int j = 0; j < n; j++){
				temp_sum += A[i][j]*T_old[j];
			}

			temp_sum = temp_sum - A[i][i]*T_old[i];
			T[i] = T[i]-temp_sum;
			T[i] = T[i]/A[i][i];
			delta_T[i] = T[i] - T_old[i];
		}
		error = l2_norm(n,delta_T)/l2_norm(n,T);
		iters++;

		if (error < TOL){
			break;
		}
	}
	return T;
}

double *gauss(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS){

	unsigned int iters = 0;
	double error = 0.0;
    double* T = new double[n]; 
	double T_old[n];
	double delta_T[n];

	while (iters <  MAX_ITERS){

		memcpy(T_old, T, sizeof(T_old));

		for (int i = 0; i < n; i++){
			T[i] = q[i];
			for (int j = 0; j < i; j++){
				T[i] = T[i] - A[i][j]*T[j];
			}
			for (int j = i+1; j < n; j++){
				T[i] = T[i] - A[i][j]*T[j];
			}
			T[i] = T[i]/A[i][i];
			delta_T[i] = T[i] - T_old[i];
		}
		
		error = l2_norm(n,delta_T)/l2_norm(n,T);
		iters++;

		if (error < TOL){
			break;
		}
	}
	return T;
}

double *solve(const std::string& solver, int n, double** A, double *q, double TOL, unsigned int MAX_ITERS){
	std::string str1 ("jacobi");
	std::string str2 ("gauss");
	if(solver.compare(str1) == 0) return jacobi(n, A, q, TOL, MAX_ITERS);
	else if(solver.compare(str2) == 0) return gauss(n, A, q, TOL, MAX_ITERS);
	else return NULL;	
} 
