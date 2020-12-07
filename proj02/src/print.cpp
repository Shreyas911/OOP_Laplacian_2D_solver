#include <cstring>
#include <iostream>
#include "global_variables.h" // To bring the same GRVY_Timer_Class object into all files
#include <grvy.h>
#include <hdf5.h>
#include "solvers.h"
#include <fstream>
#include <cmath>
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

                        grvy_printf(GRVY_DEBUG, "%.0f  ", A[i][j]);

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
                        grvy_printf(GRVY_DEBUG, "%.17g\n", q[i]);

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
void print_verification_mode(double* T_exact, double* T_computed, double* delta_T, int n, int verification_mode, int dimension){

	gt.BeginTimer(__func__);
	int n_one_direction = n;
	if(dimension == 2) {
		n = n*n;
	}
        delta_T = new double[n];
        for(int i = 0; i < n; i++){
                delta_T[i] = T_exact[i] - T_computed[i];
        }

        if(verification_mode == 1){

		// BE WARNED - Post-processing scripts grep and awk for certain strings to parse std::out properly, change prinnt statements after careful consideration
		printf("\nVERIFICATION MODE -\n");
                printf("%-20s %-4i %-4s %.17g\n","L2 norm of error for n", n_one_direction, "is", l2_norm(n, delta_T));
        }

	delete[] delta_T;
	gt.EndTimer(__func__);

}




//// Write results in hdf5 format

void write_to_hdf5(int dimension, int n, int dim_system, double dx, double* T_exact, double* T_computed){

	hid_t group_temperature, group_coordinates, file, numerical_T_data, analytical_T_data, x_data, y_data, dataspace; /* file and dataset handles */
	hsize_t dimsf[1]; /* dataset dimensions */
	herr_t status[2 + dim_system];
	double x[dim_system], y[dim_system];
	
	// create arrays for x and y co-ordinates depending on dimension
	if (dimension == 1){
		for(int k = 0; k < dim_system; k++) x[k] = k*dx;
	}
	else if (dimension == 2){
		for(int k = 0; k < dim_system; k++){
			int i = k % n;
			int j = k / n;
			x[k] = i*dx;
			y[k] = j*dx;
		}
	}
	else{
		cout << "Invalid dimensions, should be 1 or 2" << endl;
	}

	// Create a new HDF5 file with default properties

	file = H5Fcreate("data.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
	group_coordinates = H5Gcreate(file, "/coordinates", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
   	group_temperature = H5Gcreate(file, "/temperature", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	// create dataspace for fixed size dataset

	dimsf[0] = dim_system;
	dataspace = H5Screate_simple(1, dimsf, NULL);

	// create dataset using defined dataspace
	numerical_T_data = H5Dcreate2(group_temperature, "Numerical Temperature", H5T_NATIVE_DOUBLE, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	analytical_T_data = H5Dcreate2(group_temperature, "Analytical Temperature", H5T_NATIVE_DOUBLE, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	x_data = H5Dcreate(group_coordinates, "x data", H5T_NATIVE_DOUBLE, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	if(dimension == 2) y_data = H5Dcreate(group_coordinates, "y data", H5T_NATIVE_DOUBLE, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	// Write the data to the dataset using default transfer properties.
	status[0] = H5Dwrite(numerical_T_data, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, T_computed);
	status[1] = H5Dwrite(analytical_T_data, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, T_exact);
	status[2] = H5Dwrite(x_data, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, x);
	if(dimension == 2) status[3] = H5Dwrite(y_data, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, y);

	// Close/release resources.

	H5Dclose(numerical_T_data);
	H5Dclose(analytical_T_data);
	H5Dclose(x_data);
	if(dimension == 2) H5Dclose(y_data);
	H5Gclose(group_coordinates);
	H5Gclose(group_temperature);
	H5Sclose(dataspace);
	H5Fclose(file);
}
