CC := g++
CPPFLAGS := -O3 -g
EXEC := heat_solve
SRC  := $(wildcard *.cpp)
OBJ  := $(patsubst %.cpp,%.o,$(SRC))

$(EXEC): $(OBJ)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

main.o: solvers.h solvers.o
solvers.o: solvers.h

# Useful phony targets
clean:
	$(RM) $(OBJ) $(EXEC)
