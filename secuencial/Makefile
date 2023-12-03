CC = g++
CFLAGS = -std=c++11 -Wall $(shell pkg-config --cflags opencv4)
LIBS = $(shell pkg-config --libs opencv4)

all: sequential threaded openmp

sequential: sequential.cpp
	$(CC) $(CFLAGS) -o sequential sequential.cpp $(LIBS)

threaded: threaded.cpp
	$(CC) $(CFLAGS) -o threaded threaded.cpp -lpthread $(LIBS)

openmp: openmp.cpp
	$(CC) $(CFLAGS) -o openmp openmp.cpp -fopenmp $(LIBS)

clean:
	rm -f sequential threaded openmp