#include <iostream>
#include <vector>
#include <math.h> 
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <omp.h>

/*
  _____     ___        __  ___    _____                    
 / ___/__  / (_)__    /  |/  /___/ ___/__ _  _____ _______ 
/ /__/ _ \/ / / _ \  / /|_/ / __/ (_ / _ \ |/ / -_) __/ _ \
\___/\___/_/_/_//_/ /_/  /_/\__/\___/\___/___/\__/_/ /_//_/
                                                           
FEEL FREE TO COPY AND REUSE
*/

//TO COMPILE:  g++ main.cpp -std=c++11 -fopenmp
//TO RUN: ./a.out

#define MIN 0
#define MAX 1000
#define INC 1
#define VAR_MAX 6

using namespace std;

uint last_rand = 0;

void sequential(vector<double> points){

	double best_dist = DBL_MAX;
	double best_A = 0;
	double best_B = 0;
	double best_C = 0;
	double best_D = 0;
	double best_E = 0;
	double best_F = 0;

	for(int A=0;A<VAR_MAX;A++){
		for(int B=0;B<VAR_MAX;B++){
			for(int C=0;C<VAR_MAX;C++){
				for(int D=0;D<VAR_MAX;D++){
					for(int E=0;E<VAR_MAX;E++){
						for(int F=0;F<VAR_MAX;F++){

							vector<double> guess;
							
							for(double x=MIN;x<MAX;x+=INC){
								guess.push_back(sin(x*A)*B + sin(x*C)*D + sin(x*E)*F);
							}

							double dist = 0;
							for(uint i=0;i<points.size();i++){
								double to_add = guess[i]-points[i];
								if(to_add<0){
									to_add *= -1;
								}
								dist += to_add;
							}
							if(dist<best_dist){
								best_dist = dist;
								best_A = A;
								best_B = B;
								best_C = C;
								best_D = D;
								best_E = E;
								best_F = F;
							}
						}
					}
				}
			}
		}
	}

	if(best_dist>0.1){
		cout << "sequential is wrong" << endl;
		exit(0);
	}
		
}

void open_mp(vector<double> points){

	double best_dist = DBL_MAX;
	double best_A = 0;
	double best_B = 0;
	double best_C = 0;
	double best_D = 0;
	double best_E = 0;
	double best_F = 0;

	#pragma omp parallel for
	for(int A=0;A<VAR_MAX;A++){
		for(int B=0;B<VAR_MAX;B++){
			for(int C=0;C<VAR_MAX;C++){
				for(int D=0;D<VAR_MAX;D++){
					for(int E=0;E<VAR_MAX;E++){
						for(int F=0;F<VAR_MAX;F++){

							vector<double> guess;
							
							for(double x=MIN;x<MAX;x+=INC){
								guess.push_back(sin(x*A)*B + sin(x*C)*D + sin(x*E)*F);
							}

							double dist = 0;
							for(uint i=0;i<points.size();i++){
								double to_add = guess[i]-points[i];
								if(to_add<0){
									to_add *= -1;
								}
								dist += to_add;
							}
							if(dist<best_dist){
								best_dist = dist;
								best_A = A;
								best_B = B;
								best_C = C;
								best_D = D;
								best_E = E;
								best_F = F;
							}
						}
					}
				}
			}
		}
	}

	if(best_dist>0.1){
		cout << "sequential is wrong" << endl;
		exit(0);
	}
		
}

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

	auto start = std::chrono::system_clock::now();
	sequential(points);
	auto stop = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();
    cout << "Brute force sequential took " << double(duration)/1000000 << " seconds" << endl;

    start = std::chrono::system_clock::now();
    open_mp(points);
	stop = std::chrono::system_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();
    cout << "Brute force open mp took " << double(duration)/1000000 << " seconds" << endl;
	
    return 0;
}