double l2_norm(int n, double *x);
double *jacobi(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS);
double *gauss(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS);
double *solve(const std::string& solver, int n, double** A, double *q, double TOL, unsigned int MAX_ITERS);
#ifdef INCLUDE_PETSC
double * petsc(int n, double** A, double *q, double TOL, unsigned int MAX_ITERS);
#endif
