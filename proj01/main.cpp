#include <iostream>
#include "solvers.h"
#include "assemble.h"
#include <masa.h>

using namespace std;
using namespace MASA; 

int main(int argc, char *argv[]) {

	masa_init("laplace 2D exact","laplace_2d");
	masa_display_param();
	masa_set_param("Lx",1.);
	masa_set_param("Ly",masa_get_param("Lx"));

	const int n = 7;
	const int nn = n*n;
	const int MAX_ITERS = 100;
	const double TOL = 0.001;
	const double L = masa_get_param("Lx");
	const double h = L/(n-1);
	double** A = matrix_order4_dim2(n); // each element is a pointer to an array.
	double* q = new double[nn];
	double* T = new double[nn];
	double* T_exact = new double[nn];
	
	for(int k = 0; k < nn; k++){
		int i = k % n;
		int j = k / n;
		q[k] = masa_eval_2d_source_f(i*h,j*h);
		T_exact[k] = masa_eval_2d_exact_phi(i*h,j*h);
	}

	T = jacobi(n, A, q, TOL, MAX_ITERS);
	T = gauss(n, A, q, TOL, MAX_ITERS);

	for(int i = 0; i < nn; i++){
		delete [] A[i];
	}

delete[] A;
A = 0;
delete[] q;
delete[] T;

}	

