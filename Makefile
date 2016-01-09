CXX = g++
CXXFLAGS = -Wall -g

main: main.o Axes.o Function.o Term.o
	$(CXX) $(CXXFLAGS) -o main main.o Axes.o Function.o Term.o

main.o: main.cpp Axes.h Function.h Term.h globals.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Axes.o: Axes.cpp Axes.h Function.h Term.h globals.h
	$(CXX) $(CXXFLAGS) -c Axes.cpp

Function.o: Function.cpp Function.h Term.h globals.h
	$(CXX) $(CXXFLAGS) -c Function.cpp

Term.o: Term.cpp Term.h
	$(CXX) $(CXXFLAGS) -c Term.cpp