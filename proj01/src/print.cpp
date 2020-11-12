#include <cstring>
#include <iostream>
#include "global_variables.h" // To bring the same GRVY_Timer_Class object into all files
#include <grvy.h>
#include "solvers.h"
#include <fstream>

using namespace std;
using namespace GRVY;

//Print nxn matrix A
void print_matrix_A(double** A, int n){

	gt.BeginTimer(__func__);

	grvy_printf(GRVY_DEBUG, "\n");
        grvy_printf(GRVY_DEBUG, "DEBUG MODE - printing A in MATLAB compatible form\n");
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

// Print nx1 vector q
void print_vector_q(double* q, int n){

	gt.BeginTimer(__func__);
        grvy_printf(GRVY_DEBUG, "\n");
        grvy_printf(GRVY_DEBUG, "DEBUG MODE - printing q in MATLAB compatible form\n");
        grvy_printf(GRVY_DEBUG, "q = [");

        for(int i = 0; i < n; i++){
                        grvy_printf(GRVY_DEBUG, "%-2f\n", q[i]);

        }
        grvy_printf(GRVY_DEBUG, "]\n");
        gt.EndTimer(__func__);
}

// Print q, T_exact, T_computed side by side
void print_compare_q_Texact_Tcomputed(double* q, double* T_exact, double* T_computed, int n){

        gt.BeginTimer(__func__);
        
	grvy_printf(GRVY_DEBUG, "\n");
        grvy_printf(GRVY_DEBUG, "DEBUG MODE - Compare vector values\n");
        grvy_printf(GRVY_DEBUG, "%-11s    %-11s    %-11s\n", "q", "T_exact", "T_computed");

        for (int k = 0; k < n; k++){
                grvy_printf(GRVY_DEBUG, "%-11f    %-11f    %-11f\n", q[k], T_exact[k],T_computed[k]);
        }

        gt.EndTimer(__func__);
}

// Print L2 norm of delta_T in verification mode
void print_verification_mode(double* T_exact, double* T_computed, double* delta_T, int n, int verification_mode){

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

// Write output.log for results
void write_results_output_file(double dx, double* T_exact, double* T_computed, int n){

	gt.BeginTimer(__func__);

        ofstream myfile ("output.log");
        
        if (myfile.is_open()){
                myfile << "#x       " << std::fixed << "Exact    " << std::fixed << "Computed" << endl;
                for(int k = 0; k < n; k++){
                        myfile << k*dx << " " << std::fixed << T_exact[k] << " " << std::fixed << T_computed[k] << endl ;
                }
                myfile.close();
        }
        else cout << "Unable to open file";

	gt.EndTimer(__func__);

}
