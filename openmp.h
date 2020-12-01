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

	cout << "	A " << best_A;
	cout << "	B " << best_B;
	cout << "	C " << best_C;
	cout << "	D " << best_D;
	cout << "	E " << best_E;
	cout << "	F " << best_F;
	cout << endl;

	if(best_dist>0.1){
		cout << "open_mp is wrong" << endl;
		exit(0);
	}
		
}