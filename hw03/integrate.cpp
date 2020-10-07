#include <iostream>
#include <cmath>
#include "trapezoidal.h"
#include "simpson.h"

#define erf_tab 0.84270079295

using namespace std;

int main(int argc, char *argv[]) {
	// Input verification
	// atoi returns integer part of input and 0 if not a numeric input
	if (argc != 3 || atoi(argv[2]) <= 0 || (atoi(argv[1]) != 1 & atoi(argv[1]) != 2)) {
		cerr << "ERROR: First input should be 1 or 2 for Trapezoidal and Simpson's rule respectively. The second input should be a positive integer for the number of points" << endl;
	return 1;
	}
	
	int N = atoi(argv[2]);

	if (atoi(argv[1]) == 1){

		double integral = integral_trapezoidal(1, N);
		double erel = abs(integral - erf_tab)/integral;

		cout << integral << " " << erel << endl;
	}       
	else{

                double integral = integral_simpson(1, N);
                double erel = abs(integral - erf_tab)/integral;

                cout << integral << " " << erel << endl;
        }                       
}
