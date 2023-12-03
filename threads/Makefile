CC = g++
CFLAGS = -std=c++11 -Wall $(shell pkg-config --cflags opencv4)
LIBS = $(shell pkg-config --libs opencv4)

all: threaded

threaded: threaded.cpp
	$(CC) $(CFLAGS) -o threaded threaded.cpp -lpthread $(LIBS)

clean:
	rm -f threaded