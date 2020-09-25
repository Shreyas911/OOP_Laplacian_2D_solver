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
	int N[3] = {100,1000,10000};
	double x,y,d; 
	int n = sizeof(N)/sizeof(N[0]);
	int counter = 0;
	double piestimate[n],erel[n];

	for (int i = 0;i < n; i++){
		counter = 0;
		for (int j = 0;j < N[i]; j++){
			x = double(rand()%32767)/double(32767);
			y = double(rand()%32767)/double(32767);
			d = x*x + y*y;
			if(d<=1.0){
				counter++;
			}	
		}
		piestimate[i] = double(4*counter)/double(N[i]);
		erel[i] = fabs(piestimate[i] - PI)/PI;
		cout<<piestimate[i]<<" "<<erel[i]<<endl;
	}
}