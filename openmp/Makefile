CC = g++
CFLAGS = -std=c++11 -Wall -fopenmp $(shell pkg-config --cflags opencv4)
LIBS = $(shell pkg-config --libs opencv4)

all: openmp

openmp: openmp.cpp
	$(CC) $(CFLAGS) -o openmp openmp.cpp $(LIBS)

clean:
	rm -f openmp