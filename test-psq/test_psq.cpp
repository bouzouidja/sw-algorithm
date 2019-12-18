/**
 * 	test_psq.cpp
 * 
 * Objectif : 	À partir d'une séquence donnée en entrée (seq_in),
 * 				trouver l'offset (la position) de cette séquence
 * 				dans le fichier de la base de donnée small-db.fasta.psq
 * 
 * small-db.fasta.psq est une version raccourcie de la base de donnée uniprot_sprot.fasta.psq.
 * 
 * 
 * Commande pour compiler ce programme :
 * 		g++  -Wall -Wextra -std=c++11  -o "test_psq" "test_psq.cpp"
 * 
 * Commande pour exécuter ce programme :
 * 		./test_psq small-db.fasta
 * 
 * 
 * La protéine d'entrée seq_in est :
 * 		MNAKYDTDQGVGRMLFLGTIGLAVVVGGLMAYGYYYDGKTPSSGTSFHTASPSFSSRYRY
 * 
 * 
 * L'offset de sortie si tout se passe bien :
 * 		1695
 * 
 **/

#include <iostream>
#include <string>
#include <fstream>

using std::ios;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;



// Implémentation du tableau pour le fichier .psq
// Convertit les valeurs encodées (byte) en acide aminé (char)
char get_residue(char byte)
{
	if (byte == 0)
		return '\0';
	
	if (byte <= 9)
		return 'A' + byte - 1;
	
	if (byte == 27)
		return 'J';
	
	if (byte <= 13)
		return 'K' + byte - 10;
	
	if (byte == 26)
		return 'O';
	
	if (byte <= 18)
		return 'P' + byte - 14;
	
	if (byte == 24)
		return 'U';
	
	if (byte <= 23)
		return 'V' + byte - 19;
	
	if (byte == 25)
		return '*';
	
	// Aucune correspondance
	return '\0';
}





int main(int argc, char* argv[])
{
	string seq_in = "MNAKYDTDQGVGRMLFLGTIGLAVVVGGLMAYGYYYDGKTPSSGTSFHTASPSFSSRYRY";
	
	if (argc != 2)
	{
		cout << "Le programme a besoin d'un argument pour démarrer :"
			 << endl << "(1) Un fichier binaire sans extension au format BLAST"
			 << endl;
		exit(1);
	}
	
	// Ouverture du fichier
	ifstream monfichier (argv[1] + (string)".psq", ios::in | ios::binary);
	
	if (!monfichier.is_open())
	{
		cout << "le fichier n'a pas pu etre ouvert !" << endl;
		return 1;
	}
	
	int offset = 0;
	char cara;
	
	string cmp_seq = "nope";
	
	bool found = false; // Vaut true si la protéine a été trouvée
	
	while (!found)
	{
		monfichier.read((char*) &cara, sizeof(char)); // On lit un caractère
		
		if (cara == 0) // Les séquences sont séparées par le caractère '\0'
		{
			
			// Quelle séquence est traitée :
			// cout << "Sequence courante : " << cmp_seq << endl;
			
			
			// Si la séquence d'entrée est trouvée
			if (cmp_seq == seq_in)
			{
				found = true;
				cout << "Séquence trouvée : " << cmp_seq << endl;
			}
			
			cmp_seq = "";
		}
		else
		{
			// Ajoute un caractère en fin de chaîne
			cmp_seq.push_back(get_residue(cara));
		}

		++offset;
	}
	
	cout << "La protéine a été trouvée : " << found << endl;
	cout << "offset : " << offset << endl;
	
	monfichier.close();
	cout << "Fin du programme." << endl;
	
	return 0;
}
