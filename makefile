CC = gcc
AR = ar
FLAGS = -Wall -g 
OBJECTS = main.o nodes_funcs.o algorithms.o

algorithms.o: algorithms.c algorithms.h nodes_headers.h
	$(CC) $(FLAGS) -c algorithms.c

nodes_funcs.o: nodes_funcs.c nodes_headers.h 
	$(CC) $(FLAGS) -c nodes_funcs.c

main.o: main.c algorithms.h 
	$(CC) $(FLAGS) -c main.c

graph: $(OBJECTS) 
	$(CC) $(FLAGS) -o graph $(OBJECTS)

all: graph

.PHONY:
	all clean
clean:
	rm -f graph *.o
