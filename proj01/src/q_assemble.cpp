#include <cmath>
#include <cstring>
#include <masa.h>
#include <iostream>
using namespace std;

double * q_order2_dim1(int n){
	masa_init("heat 1D exact order 2","heateq_1d_steady_const");
        masa_set_param("A_x",1.);
        masa_set_param("k_0",1.);
	double dx = masa_get_param("A_x")/(n-1);
	double k = masa_get_param("k_0");
	double L = masa_get_param("A_x");

        double* q = new double[n]{0.};
        for(int i = 1; i < n-1; i++){
		q[i] = masa_eval_1d_source_t(dx*i);
		q[i] *= dx*dx/k;  		
	}
	q[0] = masa_eval_1d_exact_t(0);
	q[n-1] = masa_eval_1d_exact_t(L);
	
        return q;	
	
}

double * q_order4_dim1(int n){
        masa_init("heat 1D exact order 4","heateq_1d_steady_const");
        masa_set_param("A_x",1.);
        masa_set_param("k_0",1.);
        double dx = masa_get_param("A_x")/(n-1);
        double k = masa_get_param("k_0");
	double L = masa_get_param("A_x");

        double* q = new double[n]{0.};
        for(int i = 2; i < n-2; i++){
                q[i] = masa_eval_1d_source_t(dx*i);
                q[i] *= dx*dx/k;
        }
        q[0] = masa_eval_1d_exact_t(0);
	q[1] = masa_eval_1d_exact_t(dx);
	q[n-2] = masa_eval_1d_exact_t(L-dx);
        q[n-1] = masa_eval_1d_exact_t(L);

        return q;       
        
}

double * q_order2_dim2(int n){

        masa_init("heat 2D exact order 2","heateq_2d_steady_const");
        masa_set_param("A_x",1.);
	masa_set_param("B_y",masa_get_param("A_x"));
        masa_set_param("k_0",1.);
        double h = masa_get_param("A_x")/(n-1);
        double k = masa_get_param("k_0");
        double L = masa_get_param("A_x");

	int nn = n*n;
        double* q = new double[nn];

        for(int k = 0; k < nn; k++){

		int i = k % n;
		int j = k / n;

		if (k % n == 0 || k < n || k > nn - 1 - n || (k+1) % n == 0){
			q[k] = masa_eval_2d_exact_t(i*h,j*h);			
		}
		else{
			q[k] = masa_eval_2d_source_t(i*h,j*h);
			q[k] *= h*h/k;
		}
        }
        return q;
}

double * q_order4_dim2(int n){
 
        masa_init("heat 2D exact order 2","heateq_2d_steady_const");
        masa_set_param("A_x",1.);
	masa_set_param("B_y",masa_get_param("A_x"));
        masa_set_param("k_0",1.);
        double h = masa_get_param("A_x")/(n-1);
        double k = masa_get_param("k_0");
        double L = masa_get_param("A_x");

	int nn = n*n;
        double* q = new double[nn];

        for(int k = 0; k < nn; k++){

		int i = k % n;
		int j = k / n;

		if (k % n == 0 || (k-1) % n == 0 || k < 2*n || k > nn - 1 - 2*n || (k+1) % n == 0 || (k+2) % n == 0){
			q[k] = masa_eval_2d_exact_t(i*h,j*h);			
		}
		else{
			q[k] = masa_eval_2d_source_t(i*h,j*h);
			q[k] *= h*h/k;
		}
        }
        return q;
}

double * assemble_q(int n, int order, int dimension){
        if (order == 2 && dimension == 1) return q_order2_dim1(n);
        else if (order == 4 && dimension == 1) return q_order4_dim1(n);
        else if (order == 2 && dimension == 2) return q_order2_dim2(n);
        else if (order == 4 && dimension == 2) return q_order4_dim2(n);
        else return NULL;
}