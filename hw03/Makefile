CC := g++
CPPFLAGS := -O3 -g
EXEC := integrate
SRC  := $(wildcard *.cpp)
OBJ  := $(patsubst %.cpp,%.o,$(SRC))

$(EXEC): $(OBJ)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

integrate.o trapezoidal.o: trapezoidal.h
integrate.o simpson.o: simpson.h

# Useful phony targets
clean:
	$(RM) $(OBJ) $(EXEC)
