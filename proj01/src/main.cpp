#include <iostream>
#include "solvers.h"
#include "matrix_assemble.h"
#include "q_assemble.h"
#include <masa.h>

using namespace std;
using namespace MASA; 

int main(int argc, char *argv[]) {
	const int n = 11;
	const int nn = n*n;
	const int MAX_ITERS = 100000;
	const double TOL = 0.000000001;
	const double L = 1.;
	const double h = L/(n-1);
	double* q = q_order2_dim2(n);
	double** A = matrix_order2_dim2(n);
	double* T_gauss = new double[nn];
	double* T_jacobi = new double[nn];
	
	T_jacobi = jacobi(nn, A, q, TOL, MAX_ITERS);
	T_gauss = gauss(nn, A, q, TOL, MAX_ITERS);
	
	double* T_exact = new double[nn];
	
	for(int k = 0; k < nn; k++){
		int i = k % n;
		int j = k / n;
		T_exact[k] = masa_eval_2d_exact_t(i*h,j*h);
		cout << q[k] << " " << T_exact[k] << " " << T_jacobi[k] << " " << T_gauss[k] << endl;
	}

        cout << "[";	
/*
	for(int i = 0; i < nn; i++){
		for(int j = 0; j < nn; j++){
			cout << A[i][j] << " ";
		}
		cout << ";" << endl;
	}

*/	
	for(int i = 0; i < nn; i++){
		delete [] A[i];
	}

delete[] A;
A = 0;
delete[] q;
delete[] T_gauss;
delete[] T_jacobi;
delete[] T_exact;

}	

