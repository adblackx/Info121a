CFLAGS = -Wall -g -std=c++11 #definition de variable

all : tri

liste: header.hpp liste.cpp
	g++ $(CFLAGS) -c liste.cpp

tri: tri.cpp liste
	g++ $(CFLAGS) tri.cpp liste.o -o tri

clean:
	rm -f tri liste.o