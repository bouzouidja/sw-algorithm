all: algo.o get_residue.o main.cpp
	g++ algo.o get_residue.o main.cpp -o main
align_algorithm.o: algo.cpp
	g++ -c algo.cpp
get_residue.o: get_residue.cpp
	g++ -c get_residue.cpp
clean:
	rm *.o
