struct pthread_data_t{
	int id;
	vector<double> points;
	double best_dist = DBL_MAX;
	double best_A = 0;
	double best_B = 0;
	double best_C = 0;
	double best_D = 0;
	double best_E = 0;
	double best_F = 0;
};

void* pthread_fun(void *input){

	const auto processor_count = std::thread::hardware_concurrency();

	pthread_data_t* my_data = (pthread_data_t*)input;
	int id = my_data->id;
	vector<double> points = my_data->points;

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
							for(uint i=0;i<points.size();i++){
								double to_add = guess[i]-points[i];
								if(to_add<0){
									to_add *= -1;
								}
								dist += to_add;
							}
							if(dist<my_data->best_dist){
								my_data->best_dist = dist;
								my_data->best_A = A;
								my_data->best_B = B;
								my_data->best_C = C;
								my_data->best_D = D;
								my_data->best_E = E;
								my_data->best_F = F;
							}
						}
					}
				}
			}
		}
	}
}

void pthread(vector<double> points){
	const auto processor_count = std::thread::hardware_concurrency();

	pthread_t threads[processor_count];
	pthread_data_t datas[processor_count];

	for(uint i=0;i<processor_count;i++){
		pthread_t thread_id; 
	    datas[i].id = i;
	    datas[i].points = points;
	    pthread_create(&thread_id, NULL, &pthread_fun, (void*)&datas[i]); 
	    threads[i] = thread_id;
	}

	double best_dist = DBL_MAX;
	double best_A = 0;
	double best_B = 0;
	double best_C = 0;
	double best_D = 0;
	double best_E = 0;
	double best_F = 0;

	for(uint i=0;i<processor_count;i++){
		pthread_join(threads[i], NULL); 
	    if(best_dist>datas[i].best_dist){
	    	best_dist = datas[i].best_dist;
			best_A = datas[i].best_A;
			best_B = datas[i].best_B;
			best_C = datas[i].best_C;
			best_D = datas[i].best_D;
			best_E = datas[i].best_E;
			best_F = datas[i].best_F;
	    }
	}

	cout << "	A " << best_A;
	cout << "	B " << best_B;
	cout << "	C " << best_C;
	cout << "	D " << best_D;
	cout << "	E " << best_E;
	cout << "	F " << best_F;
	cout << endl;
}