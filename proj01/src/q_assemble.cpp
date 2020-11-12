#include <cmath>
#include <cstring>
#include <masa.h>
#include <iostream>
#include "global_variables.h" // To bring the same GRVY_Timer_Class object into all files

using namespace std;

//Assembles q matrix as shown in model document using MASA for order 2 dim 1 system
double * q_order2_dim1(int n, double L, double k_0){
	
	gt.BeginTimer(__func__);

	masa_init("heat 1D exact order 2","heateq_1d_steady_const");
        masa_set_param("A_x",atan(1)*8/L);
        masa_set_param("k_0",k_0);
	double dx = L/(n-1);
	double k = k_0;

        double* q = new double[n]{0.};
        for(int i = 1; i < n-1; i++){
		q[i] = masa_eval_1d_source_t(dx*i);
		q[i] *= pow(dx,2)/k;  		
	}
	q[0] = masa_eval_1d_exact_t(0);
	q[n-1] = masa_eval_1d_exact_t(L);
	
	gt.EndTimer(__func__);

        return q;	
	
}

//Assembles q matrix as shown in model document using MASA for order 4 dim 1 system
double * q_order4_dim1(int n, double L, double k_0){

	gt.BeginTimer(__func__);

        masa_init("heat 1D exact order 4","heateq_1d_steady_const");
        masa_set_param("A_x",atan(1)*8/L);
        masa_set_param("k_0",k_0);
        double dx = L/(n-1);
        double k = k_0;

        double* q = new double[n]{0.};
        for(int i = 2; i < n-2; i++){
                q[i] = masa_eval_1d_source_t(dx*i);
                q[i] *= 12.0*pow(dx,2)/k;
        }

        q[0] = masa_eval_1d_exact_t(0);
	q[1] = masa_eval_1d_exact_t(dx);
	q[n-2] = masa_eval_1d_exact_t(L-dx);
        q[n-1] = masa_eval_1d_exact_t(L);

        gt.EndTimer(__func__);

        return q;       
        
}

//Assembles q matrix as shown in model document using MASA for order 2 dim 2 system
double * q_order2_dim2(int n, double L, double k_0){

	gt.BeginTimer(__func__);

        masa_init("heat 2D exact order 2","heateq_2d_steady_const");
        masa_set_param("A_x",atan(1)*8/L);
	masa_set_param("B_y",atan(1)*8/L);
        masa_set_param("k_0",k_0);
        double h = L/(n-1);

	int nn = n*n;
        double* q = new double[nn];

        for(int k = 0; k < nn; k++){

		int i = k % n;
		int j = k / n;
		
		//Dirichlet condditions on the boundary
		if (k % n == 0 || k < n || k > nn - 1 - n || (k+1) % n == 0){
			q[k] = masa_eval_2d_exact_t(i*h,j*h);			
		}

		//Source terms in the interior
		else{
			q[k] = masa_eval_2d_source_t(i*h,j*h);
			q[k] *= pow(h,2)/k_0;
		}
        }

	gt.EndTimer(__func__);

        return q;
}

//Assembles q matrix as shown in model document using MASA for order 4 dim 2 system
double * q_order4_dim2(int n, double L, double k_0){

        gt.BeginTimer(__func__);
 
        masa_init("heat 2D exact order 2","heateq_2d_steady_const");
        masa_set_param("A_x",atan(1)*8/L);
	masa_set_param("B_y",atan(1)*8/L);
        masa_set_param("k_0",k_0);
        double h = L/(n-1);

	int nn = n*n;
        double* q = new double[nn];

        for(int k = 0; k < nn; k++){

		int i = k % n;
		int j = k / n;

		//Dirichlet conditions on the boundary
		if (k % n == 0 || (k-1) % n == 0 || k < 2*n || k > nn - 1 - 2*n || (k+1) % n == 0 || (k+2) % n == 0){
			q[k] = masa_eval_2d_exact_t(i*h,j*h);			
		}

		//Source terms in the interior
		else{
			q[k] = masa_eval_2d_source_t(i*h,j*h);
			q[k] *= 12.0*pow(h,2)/k_0;
		}
        }

        gt.EndTimer(__func__);

        return q;
}

//Called in the main function, uses a bunch of if statements to assemble q correctly
double * assemble_q(int n, int order, int dimension, double L, double k_0){

        gt.BeginTimer(__func__);

        if (order == 2 && dimension == 1){
		gt.EndTimer(__func__);
		return q_order2_dim1(n, L, k_0);
	}
        else if (order == 4 && dimension == 1){
                gt.EndTimer(__func__);
		return q_order4_dim1(n, L, k_0);
	}
        else if (order == 2 && dimension == 2){
                gt.EndTimer(__func__);
		return q_order2_dim2(n, L, k_0);
	}
        else if (order == 4 && dimension == 2){
                gt.EndTimer(__func__);
		return q_order4_dim2(n, L, k_0);
	}
        else{
		return NULL;
	}
}
