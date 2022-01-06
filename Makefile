#
# Makefile for CS 70 treestringset Assignment
#

all: treestringset-test

treestringset-test: treestringset-test.o treestringset.o
	clang++ -o treestringset-test treestringset-test.o treestringset.o -L/usr/lib/cs70lib -l testinglogger

treestringset.o: treestringset.cpp treestringset.hpp
	clang++ -c -g -std=c++17 -Wall -Wextra -pedantic treestringset.cpp


treestringset-test.o: treestringset-test.cpp treestringset.hpp
	clang++ -c -g -std=c++17 -Wall -Wextra -pedantic treestringset-test.cpp

clean:
	rm -rf treestringset-test *.o *.dSYM
