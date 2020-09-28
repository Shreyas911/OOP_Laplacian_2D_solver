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
	int N;
	cin>>N;
	double x,y,d; 
	int counter = 0;
	double piestimate,erel;

	counter = 0;
	for (int j = 0;j < N; j++){
		// Generate x and y between 0 and 1
		x = double(rand())/double(RAND_MAX);
		y = double(rand())/double(RAND_MAX);
		d = x*x + y*y;
		// If inside circle, increase counter
		if(d<=1.0){
			counter++;
		}	
	//estimate of PI and erel
	piestimate = double(4*counter)/double(N);
	erel = fabs(piestimate - PI)/PI;
	}
	//output in the required format
	cout<<N<<" "<<counter<<" "<<N-counter<<" "<<piestimate<<" "<<erel<<" ";
}