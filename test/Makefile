# set the compiler
CC := g++

# set the compiler flags
CPPFLAGS := -std=c++11 -Wall `sdl2-config --cflags --libs` -lSDL2_image -lm #-I include/

# add source files here
SRCS := waves.cpp

# generate names of object files
OBJS := $(SRCS:.cpp=.o)

# name of executable
EXEC := waves

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) Makefile 
	$(CC) -o $@ $(OBJS) $(CPPFLAGS)

# recipe to clean the workspace
clean:
	rm -f *.o $(EXEC) 
