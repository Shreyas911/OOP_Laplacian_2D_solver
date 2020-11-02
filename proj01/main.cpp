#include <iostream>
#include "solvers.h"

using namespace std;

int main(int argc, char *argv[]) {

	const int n = 100;

	double** A = new double*[n]; // each element is a pointer to an array.
	double* q = new double[n];
	double* T = new double[n]; 

	for(int i = 0; i < n; i++){
	    A[i] = new double[n]; // build rows
	}

	for(int i = 0; i < n; i++){
	    q[i] = i;		
		for(int j = 0; j < n; j++){
			if (i<=j) A[i][j] = i+j+1;
			else A[i][j] = 0; 
	    }
	}

	T = jacobi(n, A, q, 0.001, 100);
	T = gauss(n, A, q, 0.001, 100);
	for(int i = 0; i < n; i++){
    	cout<<T[i]<<endl;
	}

delete[] A;
delete[] q;
delete[] T;
}	

