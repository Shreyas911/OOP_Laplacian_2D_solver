class my_solver_class{

public:
        void assemble_linear_system(my_inputfile_parser&);
        void solve_linear_system(my_inputfile_parser&);
        void print_and_write_all(my_inputfile_parser&);
        void deallocate_memory(my_inputfile_parser&);

	#ifdef INCLUDE_PETSC
        void petsc_assemble_linear_system(my_inputfile_parser&, int, char**);
        #endif
};
