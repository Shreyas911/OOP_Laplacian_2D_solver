#include <cmath>
#include "func.h"

double integral_simpson(double x, int n){

        double integral = 0;
        double dt = x/(n-1);
	
	integral += dt/3 * func(0);
        for(int i = 1; i<(n-1);i++){
		if(i%2 == 1){
                	integral += dt/3 * 4 * func(i*dt);
		}
		else{
			integral += dt/3 * 2 * func(i*dt);
		}
        }
	integral += dt/3 * func(1);
        return integral;
}

