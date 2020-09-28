#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <math.h>

// Actual value of PI
#define PI 3.14159265358979323846

using namespace std;

int main ()
{
	srand(time(NULL)); 
	int N=20000000; // this is equal to (960000000/48)
	double x,y,d; 
	int N_i = 0; //Number of points inside the circle
	double piestimate,erel;

	for (int j = 0;j < N; j++){
		// Find x and y randomly between 0 and 1
		x = double(rand())/double(RAND_MAX);
		y = double(rand())/double(RAND_MAX);
		d = x*x + y*y;
		if(d<=1.0){
			N_i++;
		}	
	piestimate = double(4*N_i)/double(N);
	//relative error in the estimate
	erel = fabs(piestimate - PI)/PI;
	}
	//output to temp.log for aggregation
	cout<<N<<" "<<N_i<<" "<<N-N_i<<" "<<piestimate<<" "<<erel<<endl;
}