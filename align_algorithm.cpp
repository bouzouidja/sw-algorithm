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
#include <algorithm>    // std::max
using std::ios;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::max;




int gap = -2 ,  match = 1 ,  mismatch = -1;


int alignment_method(string fasta_seq , string  input_seq){
	// 1- the first step is building a scoring matrix 
	// 2 - second you should find the most suitable value (MAX in the matrix)
	// 3- 
	int n = fasta_seq.length()+1;
	int m = input_seq.length() +1;
	
	int scoring_matrix[n][m];
	printf("taille des seqs N %d et M %d \n",n ,m );
	scoring_matrix[0][0] = 0 ; //initialize the first element of the matrix to 0
	int max_value = scoring_matrix[0][0] ;// the most suitable value for the trace back
	printf(" debut %d\t" ,scoring_matrix[0][0]);	
	for (int i=0 ; i<n ;i++)
		{	
			
			
			for(int j = 0 ; j<m ; j++)
				{
					
					
					if (i== 0 )
						{ 
							if (j==0)
								{
									scoring_matrix[i][j] =0 ;	// condition pour remplir la premiere ligne
								}
							else 
								{	
									
									//scoring_matrix[i][j] =scoring_matrix[i][j-1]  + gap ;
									scoring_matrix[i][j] =0 ;
									max_value = max(max_value , scoring_matrix[i][j]) ;//MAJ le maximum
									printf("la aleur ajoute est %d and The max is  %d\t" ,scoring_matrix[i][j] , max_value);
								}
							
							if (j+1 == m) 
								{
									printf("\n");
								}
						}
					else 

						{	

							printf(" apres la  ligne 0 \n" );
							if (j==0 )
								{		
										
										scoring_matrix[i][j] =0 ;// condition pour remplir la premiere colonne
										max_value = max(max_value , scoring_matrix[i][j]) ; //MAJ le maximum
										printf("Le I  %d  le J %d la premiere celule de la  %d la valeur %d \n",i,j,scoring_matrix[0][0], scoring_matrix[i][j]);
								}
			 
							
						 
							else 
								{

											printf(" Comparaison entre les car des 2 seqs: Lettre DB %c ave la Letrre seq Input:%c  \n",fasta_seq.at(i-1),input_seq.at(j-1) );		
											if (input_seq.at(j-1) == fasta_seq.at(i-1))
												{ // si il existe un match entre les 2 sequences
										
													scoring_matrix[i][j] = max(max(max(scoring_matrix[i][j-1] + gap ,scoring_matrix[i-1][j] + gap) , scoring_matrix[i-1][j-1] +match),0) ;
													printf("  Match trouver %d\n" ,scoring_matrix[i][j]);

												}
											else 
												{ // si il y a un mismatch
													scoring_matrix[i][j] = max(max(max(scoring_matrix[i][j-1] + gap ,scoring_matrix[i-1][j] +gap) , scoring_matrix[i-1][j-1] + mismatch),0) ;
													printf(" Y a pas de match !!!%d\n" ,scoring_matrix[i][j]);

												}

											max_value = max(max_value , scoring_matrix[i][j]) ;//MAJ le maximum

											if (j+1 == m) 
												{
													printf("\n");
												}
								}
									
						
						
								
						}
				}
	
		}




	printf("\n Printing a matrix scoring \n");
	for (int k=0 ; k<n ;k++)
		{

				for(int l = 0 ; l<m ; l++)
				{
					printf(" %d\t" ,scoring_matrix[k][l]);
					if (l+1 == m){
						printf("\n" );
					}
					
					
				}
		}
	

	return max_value;
}


int main()
{
	string input_seq 		= 	"CTCGCAGC";
	string database_seq 	= 	"CATTCAC";
	




	cout<< "beginning the algorithm" << endl ;
	int score = alignment_method( database_seq ,input_seq) ;
	
	printf("\nLe score de cette séquence %d\n",score);



	return 0;
}
