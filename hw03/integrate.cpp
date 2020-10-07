#include <iostream>
#include <cmath>
#include "trapezoidal.h"
#include "simpson.h"

using namespace std;

int main(){
	cout << integral_trapezoidal(1,100000) << endl;
	cout << integral_simpson(1,100000) << endl;
}
