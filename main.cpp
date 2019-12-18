#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Le programme a besoin de deux arguments pour démarrer :"
			 << endl << "(1) Le fichier de la base de donnée, au format BLAST"
			 << endl << "(2) Le fichier de la protéine d'entrée, au format FASTA."
			 << endl;
		exit(1);
	}
	
	// Le fichier de la base de donnée doit exister au format BLAST
	// On vérifie que les fichiers .phr .pin et .psq existent

	ifstream f_phr(argv[1] + (string)".phr");
	ifstream f_pin(argv[1] + (string)".pin");
	ifstream f_psq(argv[1] + (string)".psq");
	
	ifstream f_pro(argv[2]);
	
	bool files_exists = f_phr.is_open() &&
						f_pin.is_open() &&
						f_psq.is_open() &&
						f_pro.is_open();
	
	if (!files_exists)
	{
		cout << "Merci de renseigner des fichiers valides." << endl;
		exit(1);
	}
	
	string line;
	string sequence;

	while (std::getline(f_pro, line))
	{
		if (line.find(">") == string::npos)
			sequence += line;
	}
	
	// Affiche la séquence contenue dans p.fasta
	// cout << sequence << endl;
	
	f_phr.close();
	f_pin.close();
	f_psq.close();
	f_pro.close();
	
	cout << "ok" << endl;
	
	return 0;
}
