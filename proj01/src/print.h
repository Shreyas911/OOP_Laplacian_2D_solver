void print_matrix_A(double** A, int n);
void print_vector_q(double* q, int n);
void print_compare_q_Texact_Tcomputed(double* q, double* T_exact, double* T_computed, int n);
double * print_verification_mode(double* T_exact, double* T_computed, double* delta_T, int n, int verification_mode);
void write_results_output_file(double dx, double* T_exact, double* T_computed, int n, int dim);
