#include <cmath>
#include <cstring>
#include <masa.h>
#include <iostream>
using namespace std;

double * T_exact_order2_dim1(int n, double L, double k_0){
	masa_init("heat 1D exact order 2","heateq_1d_steady_const");
        masa_set_param("A_x",L);
        masa_set_param("k_0",k_0);
	double dx = L/(n-1);
	double k = k_0;

        double* T_exact = new double[n]{0.};
        for(int i = 0; i < n; i++){
		T_exact[i] = masa_eval_1d_exact_t(dx*i);		
	}
	
        return T_exact;	
	
}

double * T_exact_order4_dim1(int n, double L, double k_0){
        masa_init("heat 1D exact order 4","heateq_1d_steady_const");
        masa_set_param("A_x",L);
        masa_set_param("k_0",k_0);
        double dx = L/(n-1);
        double k = k_0;

        double* T_exact = new double[n]{0.};
        for(int i = 0; i < n; i++){
                T_exact[i] = masa_eval_1d_exact_t(dx*i);
        }

        return T_exact;       
        
}

double * T_exact_order2_dim2(int n, double L, double k_0){

        masa_init("heat 2D exact order 2","heateq_2d_steady_const");
        masa_set_param("A_x",L);
	masa_set_param("B_y",L);
        masa_set_param("k_0",k_0);
        double h = L/(n-1);
        double k = k_0;

	int nn = n*n;
        double* T_exact = new double[nn];

        for(int k = 0; k < nn; k++){

		int i = k % n;
		int j = k / n;
		T_exact[k] = masa_eval_2d_exact_t(i*h,j*h);			
        }
        return T_exact;
}

double * T_exact_order4_dim2(int n, double L, double k_0){
 
        masa_init("heat 2D exact order 2","heateq_2d_steady_const");
        masa_set_param("A_x",L);
	masa_set_param("B_y",L);
        masa_set_param("k_0",k_0);
        double h = L/(n-1);
        double k = k_0;

	int nn = n*n;
        double* T_exact = new double[nn];

        for(int k = 0; k < nn; k++){

		int i = k % n;
		int j = k / n;

		T_exact[k] = masa_eval_2d_exact_t(i*h,j*h);			
		
        }
        return T_exact;
}

double * assemble_T_exact(int n, int order, int dimension, double L, double k_0){
        if (order == 2 && dimension == 1) return T_exact_order2_dim1(n, L, k_0);
        else if (order == 4 && dimension == 1) return T_exact_order4_dim1(n, L, k_0);
        else if (order == 2 && dimension == 2) return T_exact_order2_dim2(n, L, k_0);
        else if (order == 4 && dimension == 2) return T_exact_order4_dim2(n, L, k_0);
        else return NULL;
}
