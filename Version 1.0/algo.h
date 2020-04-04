#ifndef ALGO_H
#define ALGO_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <map>

using std::ios;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::max;

using namespace std;

class Algo
{
	map<string,int> CharToInt = {{"-", 0},{"A",1},{"B",2},{"C",3},{"D",4},{"E",5},{"F",6},{"G",7},{"H",8},{"I",9},{"J",27},{"K",10},{"L",11},{"M",12},{"N",13},{"O",26},{"P",14},{"Q",15},{"R",16},{"S",17},{"T",18},{"U",24},{"V",19},{"W",20},{"X",21},{"Y",22},{"Z",23},{"*",25}};
	string cle, ligne, pass;
	vector<string> cles;
	int donnee;
	int gap_open;
	int gap_extension;
	int blosumMatrix[28][28] = {0};
public:
	Algo(int gap_extension, int gap_open, ifstream &blosum_file);
	int Score_algo(string fasta_seq , string  input_seq, int gap_open, int gap_extension);
	void FillBlosumMatrix(ifstream &blosum_file);
	
};

#endif
