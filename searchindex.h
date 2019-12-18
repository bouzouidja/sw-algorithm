#ifndef SEARCHINDEX_H_INCLUDED
#define SEARCHINDEX_H_INCLUDED

#include <iostream>
#include <fstream>
using namespace std;

inline void BigtoLittleEndian (int &x);

int indexReader(ifstream& indexFile);

#endif
