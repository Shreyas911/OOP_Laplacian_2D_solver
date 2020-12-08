#include <iostream>
#include "grvy.h"
#include "petsc.h"
#include "my_inputfile_parser.h"
#include "my_solver_class.h"

using namespace std;
using namespace GRVY;
GRVY_Timer_Class gt;

int main(int argc, char *argv[]) {

	gt.Init("GRVY Performance timing");
	gt.BeginTimer(__func__);

	my_inputfile_parser parser;
	parser.parse_input_file();
	my_solver_class Solver;

	Solver.assemble_linear_system(parser);
        
	#ifdef INCLUDE_PETSC
	Solver.petsc_assemble_linear_system(parser, argc, argv);
	//Solver.petsc_solve_linear_system(parser);
	#else        
	Solver.solve_linear_system(parser);
	
	#endif

	//Solver.print_and_write_all(parser);
	//Solver.deallocate_memory(parser);

	gt.EndTimer  (__func__);
	gt.Finalize();
	gt.Summarize();
}	
