#include <iostream>
#include <fstream>
#include <cmath>
#include "solvers.h"
#include "matrix_assemble.h"
#include "q_assemble.h"
#include <masa.h>
#include <grvy.h>
#include <hdf5.h>
#include "T_exact_assemble.h"
#include "global_variables.h"
#include "print.h"
#include "my_inputfile_parser.h"
#include "my_solver_class.h"
//#include <boost/test/unit_test.hpp>

using namespace std;
using namespace MASA; 
using namespace GRVY;

GRVY_Timer_Class gt;

int main(int argc, char *argv[]) {
	
	gt.Init("GRVY Performance timing");
	gt.BeginTimer(__func__);

	my_inputfile_parser parser;
	parser.parse_input_file();
	my_solver_class X;
	X.assemble_linear_system(parser);	
        X.solve_linear_system(parser);
        X.print_and_write_all(parser);
	X.deallocate_memory(parser);
	gt.EndTimer  (__func__);
	gt.Finalize();
	gt.Summarize();
}	
