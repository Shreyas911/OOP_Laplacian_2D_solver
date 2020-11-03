#include <iostream>
#include "solvers.h"
#include "assemble.h"

using namespace std;

int main(int argc, char *argv[]) {

	const int n = 7;
	const int nn = n*n;
	const int MAX_ITERS = 100;
	const double TOL = 0.001;
	
	double** A = order4_dim2(n); // each element is a pointer to an array.
	double* q = new double[nn];
	double* T = new double[nn]; 

	for(int i = 0; i < nn; i++){
	    q[i] = i;
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

