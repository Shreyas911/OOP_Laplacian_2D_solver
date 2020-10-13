#include <cmath>
#include "func.h"

// Integrate function defined in func.h by trapezoidal method. x is limit of integra
// tion i.e. the interval [0,x] and n is the number of points used.
double integral_trapezoidal(double x, int n){
	
	double integral = 0;
	double dt = x/(n-1);
	
	for(int i = 0; i<(n-1);i++){
		integral += dt*(func(i*dt)+func((i+1)*dt))/2;	
	}  		

	return integral;
}
