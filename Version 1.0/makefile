all: algo.o Fpin.o align_algorithm.o IO_module.o conversions.o main.cpp
	g++ algo.o Fpin.o align_algorithm.o IO_module.o conversions.o main.cpp -o main
align_algorithm.o: align_algorithm.cpp
	g++ -c align_algorithm.cpp
IO_module.o: IO_module.cpp
	g++ -c IO_module.cpp
conversions.o: conversions.cpp
	g++ -c conversions.cpp
Fpin.o: Fpin.cpp
	g++ -c Fpin.cpp
algo.o: algo.cpp
	g++ -c algo.cpp
clean:
	rm *.o
