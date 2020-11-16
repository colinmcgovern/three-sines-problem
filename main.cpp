#include <iostream>
#include <vector>
#include <math.h> 
#include <chrono>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//#include "sequential.h"

using namespace std;

uint last_rand = 0;

//MODEL: sin(x*A)*B + sin(x*C)*D + sin(x*E)*F
vector<double> generate_points(double A, double B, double C, double D, double E, double F){
	vector<double> output;
	for(double x=0;x<1000;x++){
		output.push_back(sin(x*A)*B + sin(x*C)*D + sin(x*E)*F);
	}
	return output;
}

vector<double> generate_random_points(){
	double A, B, C, D, E, F;
	srand(time(NULL)+last_rand);
	last_rand = rand();
	A = double(rand()%1000);
	B = double(rand()%1000);
	C = double(rand()%1000);
	D = double(rand()%1000);
	E = double(rand()%1000);
	F = double(rand()%1000);

	cout << A << endl;
	cout << B << endl;
	cout << C << endl;
	cout << D << endl;
	cout << E << endl;
	cout << F << endl;
	cout << endl;

	return generate_points(A,B,C,D,E,F);
}

int main() {
	

	vector<double> points = generate_random_points();

	const auto start = std::chrono::system_clock::now();
	//sequential()
	const auto stop = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();
    qDebug() << "Brute force sequential took " << double(duration)/1000000 << " seconds";
	
    std::cout << "Hello World!";
    return 0;
}