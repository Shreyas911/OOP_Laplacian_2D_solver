#include <cmath>
#include <cstring>
#include <iostream>
#include "global_variables.h" // To bring the same GRVY_Timer_Class object into all files

using namespace std;

//Assembles the matrix for order 2 and dim 1
double ** matrix_order2_dim1(int n){

	gt.BeginTimer(__func__);

	double** A = new double*[n];
	
	for(int i = 0; i < n; i++){
		
		A[i] = new double[n]{0.}; // build rows
	}	
	// Points in the interior
	for(int j = 1; j < n-1; j++){
			
		A[j][j-1] = -1.;
  		A[j][j] = 2.;
		A[j][j+1] = -1.;	

	}
	// Points at boundaries
	A[0][0] = 1.;
	A[n-1][n-1] = 1.;

	gt.EndTimer(__func__);

	return A; 
}

//Assembles the matrix for order 4 and dim 1
double ** matrix_order4_dim1(int n){

	gt.BeginTimer(__func__);

        double** A = new double*[n];

        for(int i = 0; i < n; i++){

                A[i] = new double[n]{0.}; // build rows
        }
	// Points in the interior
        for(int j = 2; j < n-2; j++){
		A[j][j-2] = 1;
                A[j][j-1] = -16.;
                A[j][j] = 30.;
                A[j][j+1] = -16.;
		A[j][j+2] = 1;
        }
	// Points at the boundaries and adjacent to the boundaries
        A[0][0] = 1.;
	A[1][1] = 1.;
	A[n-2][n-2] = 1.;
        A[n-1][n-1] = 1.;

	gt.EndTimer(__func__);

        return A;
}

//Assembles the matrix for order 2 and dim 2
double ** matrix_order2_dim2(int n){

        gt.BeginTimer(__func__);

	int nn = n*n;
        double** A = new double*[nn];

        for(int i = 0; i < nn; i++){

                A[i] = new double[nn]{0.}; // build rows
        }
        for(int i = 0; i < nn; i++){
        	
		// Points at the boundaries
		if (i % n == 0 || i < n || i > nn - 1 - n || (i+1) % n == 0){
	                A[i][i] = 1.;
		}
		// Points in the interior
		else{
			A[i][i] = 4.;
			A[i][i+1] = -1.;
			A[i][i-1] = -1.;
			A[i][i-n] = -1.;
			A[i][i+n] = -1.;
		}
        }

        gt.EndTimer(__func__);

        return A;
}

//Assembles the matrix for order 4 and dim 2
double ** matrix_order4_dim2(int n){

        gt.BeginTimer(__func__);

        int nn = n*n;
        double** A = new double*[nn];

        for(int i = 0; i < nn; i++){
                A[i] = new double[nn]{0.}; // build rows
        }
        for(int i = 0; i < nn; i++){
		
		// Points at the boundaries and adjacent to the boundaries
                if (i % n == 0 || (i-1) % n == 0 || i < 2*n || i > nn - 1 - 2*n || (i+1) % n == 0 || (i+2) % n == 0){
                        A[i][i] = 1.;
                }
		// Points in the interior
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

	gt.EndTimer(__func__);

        return A;
}	

// This functionn is called in the main function. It basically assembles the correct matrix with a bunch of if statements.
double ** assemble_A(int n, int order, int dimension){

	gt.BeginTimer(__func__);

        if (order == 2 && dimension == 1){
		gt.EndTimer(__func__);
		return matrix_order2_dim1(n);
	}
        else if (order == 4 && dimension == 1){
		gt.EndTimer(__func__);
		return matrix_order4_dim1(n);
	}
        else if (order == 2 && dimension == 2){
		gt.EndTimer(__func__);
		return matrix_order2_dim2(n);
	}
        else if (order == 4 && dimension == 2){
		gt.EndTimer(__func__);
		return matrix_order4_dim2(n);
	}
        else {
		gt.EndTimer(__func__);
		return NULL;
	}

}
