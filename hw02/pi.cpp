#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <math.h>
// Actual value of PI
#define PI 3.14159265358979323846
using namespace std;

int main(int argc, char *argv[]) {
    // Input verification
    // atoi returns integer part of input and 0 if not a numeric input
    if (argc != 2 || atoi(argv[1]) <= 0) {
    	cerr << "ERROR: Give a positiver integer input for number of samples. " << endl;
    	return 1;
    }
	srand(time(NULL)); 
	int N = atoi(argv[1]);
	double x,y,d;
	//Counter for number of points inside circle. 
	int N_i = 0; 
	double piestimate,erel;

	N_i = 0;
	for (int j = 0;j < N; j++){
		// Generate x and y between 0 and 1
		x = double(rand())/double(RAND_MAX);
		y = double(rand())/double(RAND_MAX);
		d = x*x + y*y;
		// If inside circle, increase N_i
		if(d<=1.0){
			N_i++;
		}	
	//estimate of PI and erel
	piestimate = double(4*N_i)/double(N);
	erel = fabs(piestimate - PI)/PI;
	}
	//output in the required format
	cout<<N<<" "<<N_i<<" "<<N-N_i<<" "<<piestimate<<" "<<erel<<" ";
}
