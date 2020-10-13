#include <cmath>
#include "func.h"

double integral_trapezoidal(double x, int n){
	
	double integral = 0;
	double dt = x/(n-1);
	
	for(int i = 0; i<(n-1);i++){
		integral += dt*(func(i*dt)+func((i+1)*dt))/2;	
	}  		

	return integral;
}
