all: align_algorithm.o get_residue.o main.cpp
	g++ align_algorithm.o get_residue.o main.cpp -o main
align_algorithm.o: align_algorithm.cpp
	g++ -c align_algorithm.cpp
get_residue.o: get_residue.cpp
	g++ -c get_residue.cpp
clean:
	rm *.o
