/**
 * 		INFO-H-304 REMISE FINALE DU PROJET
 * 
 * 	  @authors   Ismail Dabach, Sid Ahmed Bouzouidja, Sacha Meurice
 * 	  @date      18-12-2019
 * 
 * 
 **/


// Pour compiler :
// ./main data/sdb.fasta data/p.fasta > result.txt

#define  BUFFER_SIZE 4
#define N_PROT 10// Nombre de protéines à afficher sur l'output
#include <iostream>
#include <ctime>
#include <iomanip> // Pour la fonction std::put_time
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

#include "conversions.h"
#include "IO_module.h"
#include "Fpin.h"
#include "algo.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ios;
using std::vector;


typedef struct proteine
{
	int score;
	int offset;
} Proteine;


int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout 	<< "Le programme a besoin de deux arguments pour démarrer :"
				<< endl << "(1) Le fichier de la protéine d'entrée, au format FASTA."
				<< endl << "(2) Le fichier de la base de donnée, au format BLAST"
				<< endl;
		exit(1);
	}
	
	// Le fichier de la base de donnée doit exister au format BLAST
	// On vérifie que les fichiers .phr .pin et .psq existent

	ifstream f_phr(argv[2] + (string)".phr", ios::binary);
	ifstream f_psq(argv[2] + (string)".psq", ios::binary);
	
	ifstream f_pro(argv[1]);
	
	bool files_exists = f_phr.is_open() &&
						f_psq.is_open() &&
						f_pro.is_open();
	
	if (!files_exists)
	{
		cout << "Merci de renseigner des fichiers valides." << endl;
		cout 	<< "Le programme a besoin de deux arguments pour démarrer :"
				<< endl << "(1) Le fichier de la protéine d'entrée, au format FASTA."
				<< endl << "(2) Le fichier de la base de donnée, au format BLAST"
				<< endl;
		exit(1);
	}
	
	// Le fichier .pin est géré à part
	Fpin f_pin(argv[2] + (string)".pin");
	
	
	
	
	// --- Gestion des paramètres optionnels ---
	//
	// ATTENTION A FERMER LES FICHIERS
	//
	
	ifstream blosum_file;
	
	if (argc > 3)
	{
		blosum_file.open(argv[1]);
		
		if (!blosum_file.is_open())
		{
			cout << "Le fichier BLOSUM spécifié n'a pas pu être ouvert. Le fichier par défaut est utilisé à la place" << endl;
		}
		
		blosum_file.open("BLOSUM32");
		
		if (!blosum_file.is_open())
		{
			cout << "Impossible d'ouvrir le fichier BLOSUM32." << endl;
			return EXIT_FAILURE;
		}
	}
	else
	{
		blosum_file.open("BLOSUM32");
		
		if (!blosum_file.is_open())
		{
			cout << "Impossible d'ouvrir le fichier BLOSUM32." << endl;
			return EXIT_FAILURE;
		}
	}
	
	
	
	int gap_open = 11;
	
	if (argc > 4)
	{
		gap_open = strtol(argv[3], NULL, 10);
	}
	
	
	
	
	int gap_extension = 1;
	
	if (argc > 5)
	{
		gap_extension = strtol(argv[4], NULL, 10);
	}
	
	

	Algo algo(gap_extension, gap_open, blosum_file );

	// --- Lecture du fichier p.fasta ---
	
	// On isole la séquence contenue dans le fichier
	// à l'intérieur de la variable 'sequence' (string)
	// Et on stocke les infos de la protéine dans la 
	// variable 'pro_info' (string)
	
	string sequence;
	string pro_info;
	extract_sequences(f_pro, pro_info, sequence);

	
	
	
	
	
	
	
	
	// On calcule la taille du fichier f_psq
	int length_psq;
	
	f_psq.seekg (0, f_psq.end);
    length_psq = f_psq.tellg();
    f_psq.seekg (0, f_psq.beg);
	
	
	// On parcourt toutes les séquences du fichier f_psq
	// Pour chaque séquence, on associe un score de Smith
	char cara;
	string cmp_seq = "";
	
	// On retient le tout dans un tableau de structures
	Proteine* tab_scores[N_PROT];
	
	// initialiser ce tableau avec des protéines de score nul
	Proteine pn;
	pn.score = 0;
	pn.offset = 0;
	
	for (int k = 0; k < N_PROT; ++k) {
		tab_scores[k] = &pn;
	}
	
	// Le premier caractère étant NULL, on le passe
	f_psq.read(&cara, sizeof(char));
	
	for (int i = 0; i < length_psq; ++i)
	{
		f_psq.read((char*) &cara, sizeof(char));
		
		if (cara == 0) // Les séquences sont séparées par le caractère '\0'
		{
			// Quelle séquence est traitée :
			//cout << "Séquence courante : " << cmp_seq << endl;
			
			int score_smith = algo.Score_algo(cmp_seq, sequence,gap_open,gap_extension);// = alignment_method(cmp_seq, sequence);
			
			/*if (cmp_seq == sequence)
				score_smith = 100;
			else
				score_smith = rand() %100;*/

			Proteine* p = new Proteine();
			p->offset = i+1;
			p->score = score_smith;
			
			for (int l = N_PROT - 1; l > -1; --l)
			{
				//cout 	<< "ROUND N°" << l 
				//		<< " score_smith(" << score_smith << ") tab[l](" << tab_scores[l]->score << ")" << endl;
				if (score_smith > tab_scores[l]->score)
				{
					
					if (l == N_PROT - 1)
					{
						//delete tab_scores[l];
						tab_scores[l] = p;
					}
					else
					{
						tab_scores[l+1] = tab_scores[l];
						tab_scores[l] = p;
					}
				}
				else
				{
					if (l == N_PROT - 1)
					{
						delete p;
					}
					break;
				}
			}
			
			
			
			cmp_seq = "";
		}
		else
		{
			// Ajoute un caractère en fin de chaîne
			cmp_seq.push_back(get_residue(cara));
		}
	}
	
	//**/
	
	
	
	
	// --- OUTPUT du programme ---
	

	// Permet d'afficher la date d'exécution du programme
	std::time_t   current_time   =   std::time(nullptr);
    std::tm*      UTC_time       =   gmtime(&current_time);
    
	
	cout 	<< "SW-algorithm program [" << std::put_time(UTC_time, "%a, %e %b %Y %T UTC") << "]" << endl
			<< endl
			
			<< "Database file:          " << f_pin.getTitle()		<< endl
			<< "Database version        " << f_pin.getVersion()		<< endl
			<< "Database type:	        " << f_pin.getDbType()		<< endl
			<< "Query file name:        " << argv[1]				<< endl
			<< "Query description:      " << pro_info				<< endl
			<< "Score matrix:           " << ""						<< endl //blosum_file
			<< "Gap open penalty:       " << gap_open				<< endl
			<< "Gap extension penalty:  " << gap_extension			<< endl
	    	<< endl << endl << endl
	
			<< "Sequences producing significant alignments:"
			<< "                                                 Score "
			<< endl
			<< endl
			
			;
			
			for (int t = 0; t <10; ++t)
			{
				cout 	<< extract_header(f_pin, tab_scores[t]->offset, f_phr)
						<< "...         " << tab_scores[t]->score << endl;//*/
			}

	
	f_phr.close();
	f_pin.close(); // OK car défini dans la classe Fpin
	f_psq.close();
	f_pro.close();


	return 0;
}
