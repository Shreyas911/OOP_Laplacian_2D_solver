#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;


double ** matrix_order2_dim1(int n){

	double** A = new double*[n];
	
	for(int i = 0; i < n; i++){
		
		A[i] = new double[n]{0.}; // build rows
	}	
	for(int j = 1; j < n-1; j++){
			
		A[j][j-1] = -1.;
  		A[j][j] = 2.;
		A[j][j+1] = -1.;	

	}

	A[0][0] = 1.;
	A[n-1][n-1] = 1.;

	return A; 
}

double ** matrix_order4_dim1(int n){

        double** A = new double*[n];

        for(int i = 0; i < n; i++){

                A[i] = new double[n]{0.}; // build rows
        }
        for(int j = 2; j < n-2; j++){
		A[j][j-2] = 1;
                A[j][j-1] = -16.;
                A[j][j] = 30.;
                A[j][j+1] = -16.;
		A[j][j+2] = 1;
        }
	
        A[0][0] = 1.;
	A[1][1] = 1.;
	A[n-2][n-2] = 1.;
        A[n-1][n-1] = 1.;

        return A;
}

double ** matrix_order2_dim2(int n){
	int nn = n*n;
        double** A = new double*[nn];

        for(int i = 0; i < nn; i++){

                A[i] = new double[nn]{0.}; // build rows
        }
        for(int i = 0; i < nn; i++){
        	
		if (i % n == 0 || i < n || i > nn - 1 - n || (i+1) % n == 0){
	                A[i][i] = 1.;
		}
		else{
			A[i][i] = 4.;
			A[i][i+1] = -1.;
			A[i][i-1] = -1.;
			A[i][i-n] = -1.;
			A[i][i+n] = -1.;
		}
        }
        return A;
}

double ** matrix_order4_dim2(int n){
        int nn = n*n;
        double** A = new double*[nn];

        for(int i = 0; i < nn; i++){
                A[i] = new double[nn]{0.}; // build rows
        }
        for(int i = 0; i < nn; i++){

                if (i % n == 0 || (i-1) % n == 0 || i < 2*n || i > nn - 1 - 2*n || (i+1) % n == 0 || (i+2) % n == 0){
                        A[i][i] = 1.;
                }
                else{
                        A[i][i] = 60.;
                        A[i][i+1] = -16.;
                        A[i][i-1] = -16.;
                        A[i][i-2] = 1.;
                        A[i][i+2] = 1.;
			A[i][i+n] = -16.;
			A[i][i-n] = -16.;
			A[i][i-2*n] = 1.;
			A[i][i+2*n] = 1.;
                }
        }
        return A;
}	
