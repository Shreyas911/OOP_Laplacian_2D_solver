#include <cstring>
#include <iostream>
#include "global_variables.h" // To bring the same GRVY_Timer_Class object into all files
#include <grvy.h>
#include "solvers.h"

using namespace std;
using namespace GRVY;

//Print a nxn matrix
void print_matrix_A(double** A, int n){

	gt.BeginTimer(__func__);

	grvy_printf(GRVY_DEBUG, "\n");
        grvy_printf(GRVY_DEBUG, "DEBUG MODE - printing A in MATLAB compatible forms\n");
        grvy_printf(GRVY_DEBUG, "A = [");

        for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){

                        grvy_printf(GRVY_DEBUG, "%.2f  ", A[i][j]);

                }
                grvy_printf(GRVY_DEBUG, ";\n");
        }

        grvy_printf(GRVY_DEBUG, "]\n");
	gt.EndTimer(__func__);

}

void print_vector_q(double* q, int n){

	gt.BeginTimer(__func__);
        grvy_printf(GRVY_DEBUG, "\n");
        grvy_printf(GRVY_DEBUG, "DEBUG MODE - printing q in MATLAB compatible forms\n");
        grvy_printf(GRVY_DEBUG, "q = [");

        for(int i = 0; i < n; i++){
                        grvy_printf(GRVY_DEBUG, "%-2f\n", q[i]);

        }
        grvy_printf(GRVY_DEBUG, "]\n");
        gt.EndTimer(__func__);
}

void print_compare_q_Texact_Tcomputed(double* q, double* T_exact, double* T_computed, int n){

        gt.BeginTimer(__func__);
        
	grvy_printf(GRVY_DEBUG, "\n");
        grvy_printf(GRVY_DEBUG, "DEBUG MODE - Compare vector values\n");
        grvy_printf(GRVY_DEBUG, "%-11s    %-11s    %-11s\n", "q", "MASA", "Computed");

        for (int k = 0; k < n; k++){
                grvy_printf(GRVY_DEBUG, "%-11f    %-11f    %-11f\n", q[k], T_exact[k],T_computed[k]);
        }

        gt.EndTimer(__func__);
}

void * print_verification_mode(double* T_exact, double* T_computed, double* delta_T, int n, int verification_mode){

	gt.BeginTimer(__func__);

        delta_T = new double[n];
        for(int i = 0; i < n; i++){
                delta_T[i] = T_exact[i] - T_computed[i];
        }

        if(verification_mode == 1){
		printf("\nVERIFICATION MODE -\n");
                printf("%-20s    %-11f\n","L2 norm of error", l2_norm(n, delta_T));
        }

	gt.EndTimer(__func__);

}
