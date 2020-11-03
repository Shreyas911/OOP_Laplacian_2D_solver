CC := g++
CPPFLAGS := -O3 -g -Wall
EXEC := heat_solve
SRC  := $(wildcard *.cpp)
OBJ  := $(patsubst %.cpp,%.o,$(SRC))

$(EXEC): $(OBJ)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

main.o: solvers.h solvers.o assemble.h assemble.o
solvers.o: solvers.h
assemble.o: assemble.h
# Useful phony targets
clean:
	$(RM) $(OBJ) $(EXEC)
