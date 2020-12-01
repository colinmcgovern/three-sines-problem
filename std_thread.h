mutex m;
struct std_thread_data_t{
	vector<double> points;
	double best_dist = DBL_MAX;
	double best_A = 0;
	double best_B = 0;
	double best_C = 0;
	double best_D = 0;
	double best_E = 0;
	double best_F = 0;
};
std_thread_data_t std_output;

void std_thread_help(int id){

	const auto processor_count = std::thread::hardware_concurrency();

	for(int A=0;A<VAR_MAX;A++){
		for(int B=0;B<VAR_MAX;B++){
			for(int C=0;C<VAR_MAX;C++){
				for(int D=0;D<VAR_MAX;D++){
					for(int E=0;E<VAR_MAX;E++){
						for(int F=0;F<VAR_MAX;F++){

							//Splitting the labor
							if(A%processor_count!=id){
								continue;
							}

							vector<double> guess;
							
							for(double x=MIN;x<MAX;x+=INC){
								guess.push_back(sin(x*A)*B + sin(x*C)*D + sin(x*E)*F);
							}

							double dist = 0;
							for(uint i=0;i<std_output.points.size();i++){
								double to_add = guess[i]-std_output.points[i];
								if(to_add<0){
									to_add *= -1;
								}
								dist += to_add;
							}
							if(dist<std_output.best_dist){
								lock_guard<std::mutex> g(m); 
								std_output.best_dist = dist;
								std_output.best_A = A;
								std_output.best_B = B;
								std_output.best_C = C;
								std_output.best_D = D;
								std_output.best_E = E;
								std_output.best_F = F;
							}
						}
					}
				}
			}
		}
	}
}

void std_thread(vector<double> points){
	const auto processor_count = std::thread::hardware_concurrency();
	cout << processor_count << endl;

	thread threads[processor_count];

	std_output.points = points;

	for(uint i=0;i<processor_count;i++){
		threads[i] = thread(std_thread_help,i);
	}

	for(uint i=0;i<processor_count;i++){
		threads[i].join();
	}

	cout << "	A " << std_output.best_A;
	cout << "	B " << std_output.best_B;
	cout << "	C " << std_output.best_C;
	cout << "	D " << std_output.best_D;
	cout << "	E " << std_output.best_E;
	cout << "	F " << std_output.best_F;
	cout << endl;

		
}