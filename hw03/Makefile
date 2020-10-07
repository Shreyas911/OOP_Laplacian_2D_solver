CC := g++
CPPFLAGS := -O3 -g
EXEC := integrate
SRC  := $(wildcard *.cpp)
OBJ  := $(patsubst %.cpp,%.o,$(SRC))

$(EXEC): $(OBJ)
	$(CC) -o $@ $^
%.o: %.cpp %.h
	$(CC) $(CPPFLAGS) -c $< -o $@
