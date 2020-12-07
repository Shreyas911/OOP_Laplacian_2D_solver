class my_inputfile_parser{

public:
	int n, dimension, accuracy, MAX_ITERS, order, nn, dim_system, verification_mode;
	double L, TOL, dx, k_0;
	double** A;
	double *q, *T_exact, *T_computed, *delta_T;
	std::string solver, mode;
	
	void parse_input_file();


};
