AM_CXXFLAGS = $(GRVY_CFLAGS) $(MASA_CXXFLAGS) $(HDF5_CFLAGS)
LIBS = $(GRVY_LIBS) $(MASA_LIBS) $(HDF5_LIBS)

if PETSC_ENABLED
include $(PETSC_DIR)/lib/petsc/conf/variables
AM_CXXFLAGS   += -DINCLUDE_PETSC $(PETSC_CC_INCLUDES)
endif

bin_PROGRAMS = heat_solve
heat_solve_SOURCES = main.cpp matrix_assemble.cpp q_assemble.cpp solvers.cpp T_exact_assemble.cpp print.cpp global_variables.h my_inputfile_parser.cpp my_solver_class.cpp

if PETSC_ENABLED
LIBS  += ${PETSC_LIB}
endif
