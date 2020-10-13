EXEC := tardis
SRC  := $(wildcard *.c)
OBJ  := $(patsubst %.c, %.o, $(SRC))

# Options

CC	:= gcc
CFLAGS  := -O0 -g
GSL	:= $(TACC_GSL_DIR)
LDFLAGS := -L$(GSL)/lib
LDLIBS  := -lgsl -lgslcblas
CINC	:= -I$(GSL)/include

# Rules

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) $(CINC) -c $<
mytools.o main.o: mytools.h

# Useful phony targets

.PHONY: clean

clean:
	$(RM) $(EXEC) $(OBJ)
