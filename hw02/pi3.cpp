#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <math.h>

#define PI 3.14159265358979323846

using namespace std;

int main ()
{
	srand(time(NULL)); 
	int N=20000000;
	double x,y,d; 
	int counter = 0;
	double piestimate,erel;

	counter = 0;
	for (int j = 0;j < N; j++){
		x = double(rand())/double(RAND_MAX);
		y = double(rand())/double(RAND_MAX);
		d = x*x + y*y;
		if(d<=1.0){
			counter++;
		}	
	piestimate = double(4*counter)/double(N);
	erel = fabs(piestimate - PI)/PI;
	}
	cout<<N<<" "<<counter<<" "<<N-counter<<" "<<piestimate<<" "<<erel<<" ";
}