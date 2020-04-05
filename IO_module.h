/**
 *  Bibliothèque assurant la gestion des accès aux fichiers.
 * 
 *  Lire, écrire et extraire des données depuis / vers des fichiers.
 *
 */


#ifndef IO_MODULE_H
#define IO_MODULE_H

#include <string>
#include <iostream>
#include <fstream>
#include "Fpin.h"

using std::string;
using std::endl;
using std::cout;
using std::ifstream;

string extract_header(Fpin& f_pin, const int offset, ifstream& f_phr);
void extract_sequences(ifstream& f_pro, string& pro_info, string& sequence);

#endif
