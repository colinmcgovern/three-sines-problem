#include <iostream>
#include <vector>
#include <math.h> 
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <omp.h>
#include <thread>
#include <pthread.h> 
#include <mutex> 

using namespace std;

#define MIN 0
#define MAX 1000
#define INC 1
#define VAR_MAX 5
// #define VAR_MIN 3

#include "sequential.h"
#include "openmp.h"
#include "pthread.h"
#include "std_thread.h"
#include "fork.h"

/*
  _____     ___        __  ___    _____                    
 / ___/__  / (_)__    /  |/  /___/ ___/__ _  _____ _______ 
/ /__/ _ \/ / / _ \  / /|_/ / __/ (_ / _ \ |/ / -_) __/ _ \
\___/\___/_/_/_//_/ /_/  /_/\__/\___/\___/___/\__/_/ /_//_/
                                                           
FEEL FREE TO COPY AND REUSE
*/

//TO COMPILE: g++ main.cpp -std=c++11 -fopenmp -pthread
//TO RUN: ./a.out

uint last_rand = 0;

//MODEL: sin(x*A)*B + sin(x*C)*D + sin(x*E)*F
vector<double> generate_points(double A, double B, double C, double D, double E, double F){
	vector<double> output;
	for(double x=MIN;x<MAX;x+=INC){
		output.push_back(sin(x*A)*B + sin(x*C)*D + sin(x*E)*F);
	}
	return output;
}

vector<double> generate_random_points(){
	double A, B, C, D, E, F;
	srand(time(NULL)+last_rand);
	last_rand = rand();
	A = double(rand()%VAR_MAX);
	B = double(rand()%VAR_MAX);
	C = double(rand()%VAR_MAX);
	D = double(rand()%VAR_MAX);
	E = double(rand()%VAR_MAX);
	F = double(rand()%VAR_MAX);

	cout << "Generated: " << endl;
	cout << "	A " << A;
	cout << "	B " << B;
	cout << "	C " << C;
	cout << "	D " << D;
	cout << "	E " << E;
	cout << "	F " << F;
	cout << endl;

	return generate_points(A,B,C,D,E,F);
}

int main() {

	vector<double> points = generate_random_points();
	cout << endl;

	cout << "Sequential:" << endl;
	auto start = std::chrono::system_clock::now();
	sequential(points);
	auto stop = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();
    cout << "Time: " << double(duration)/1000000 << " seconds" << endl;
    cout << endl;

    cout << "Open MP:" << endl;
    start = std::chrono::system_clock::now();
    open_mp(points);
	stop = std::chrono::system_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();
    cout << "Time:" << double(duration)/1000000 << " seconds" << endl;
    cout << endl;

    cout << "POSIX Threads:" << endl;
    start = std::chrono::system_clock::now();
    pthread(points);
	stop = std::chrono::system_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();
    cout << "Time:" << double(duration)/1000000 << " seconds" << endl;
    cout << endl;

    cout << "STD Threads:" << endl;
    start = std::chrono::system_clock::now();
    std_thread(points);
	stop = std::chrono::system_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();
    cout << "Time:" << double(duration)/1000000 << " seconds" << endl;
    cout << endl;
	
    return 0;
}