/**
 * 		INFO-H-304 REMISE FINALE DU PROJET
 * 
 * 	  @authors   Ismail Dabach, Sid Ahmed Bouzouidja, Sacha Meurice
 * 	  @date      18-12-2019
 * 
 * 
 **/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using std::ios;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::max;






const char* blosum62[26][26] =
{{"0","A","R" ,"N" ,"D" ,"C","Q" ,"E" ,"G","H" ,"I" ,"L" ,"K" ,"M" ,"F" ,"P" ,"S","T","W","Y" ,"V" ,"B","J" ,"Z" ,"X" ,"*"},
 {"A","4","-1","-2","-2","0","-1","-1","0","-2","-1","-1","-1","-1","-2","-1","1","0","-3","-2","0","-2","-1","-1","-1","-4"},
 {"R","-1","5","0","-2","-3","1","0","-2","0","-3","-2","2","-1","-3","-2","-1","-1","-3","-2","-3","-1","-2","0","-1","-4"},
 {"N","-2","0","6","1","-3","0","0","0","1","-3","-3","0","-2","-3","-2","1","0","-4","-2","-3","4","-3","0","-1","-4" },
 {"D","-2","-2","1","6","-3","0","2","-1","-1","-3","-4","-1","-3","-3","-1","0","-1","-4","-3","-3","4","-3","1","-1","-4" },
 {"C","0","-3","-3","-3","9","-3","-4","-3","-3","-1","-1","-3","-1","-2","-3","-1","-1","-2","-2","-1","-3","-1","-3","-1","-4" },
 {"Q","-1","1","0","0","-3","5","2","-2","0","-3","-2","1","0","-3","-1","0","-1","-2","-1","-2","0","-2","4","-1","-4" },
 {"E","-1","0","0","2","-4","2","5","-2","0","-3","-3","1","-2","-3","-1","0","-1","-3","-2","-2","1","-3","4","-1","-4" },
 {"G","0","-2","0","-1","-3","-2","-2","6","-2","-4","-4","-2","-3","-3","-2","0","-2","-2","-3","-3","-1","-4 ","-2","-1","-4" },
 {"H","-2","0","1","-1","-3","0","0","-2","8","-3","-3","-1","-2","-1","-2","-1","-2","-2","2","-3","0","-3","0","-1","-4" },
 {"I","-1","-3","-3","-3","-1","-3","-3","-4","-3","4","2","-3","1","0","-3","-2","-1","-3","-1","3","-3","3","-3","-1","-4"},
 {"L","-1","-2","-3","-4","-1","-2","-3","-4","-3","2","4","-2","2","0","-3","-2","-1","-2","-1","1","-4","3","-3","-1","-4" },
 {"K","-1","2","0","-1","-3","1","1","-2","-1","-3","-2","5","-1","-3","-1","0","-1","-3","-2","-2","0","-3","1","-1","-4"},
 {"M","-1","-1","-2","-3","-1","0","-2","-3","-2","1","2","-1","5","0","-2","-1","-1","-1","-1","1","-3","2","-1","-1","-4" },
 {"F","-2","-3","-3","-3","-2","-3","-3","-3","-1","0","0","-3","0","6","-4","-2","-2","1","3","-1","-3","0","-3","-1","-4" },
 {"P","-1","-2","-2","-1","-3","-1","-1","-2","-2","-3","-3","-1","-2","-4","7","-1","-1","-4","-3","-2","-2","-3","-1","-1","-4" },
 {"S", "1","-1","1","0","-1","0","0","0","-1","-2","-2","0","-1","-2","-1","4","1","-3","-2","-2","0","-2","0","-1","-4" },
 {"T", "0","-1","0","-1","-1","-1","-1","-2","-2","-1","-1","-1","-1","-2","-1","1","5","-2","-2","0","-1","-1","-1","-1","-4" },
 {"W","-3","-3","-4","-4","-2","-2","-3","-2","-2","-3","-2","-3","-1","1","-4","-3","-2","11","2","-3","-4","-2","-2","-1","-4" },
 {"Y","-2","-2","-2","-3","-2","-1","-2","-3","2","-1","-1","-2","-1","3","-3","-2","-2","2","7","-1","-3","-1","-2","-1","-4" },
 {"V", "0","-3","-3","-3","-1","-2","-2","-3","-3","3","1","-2","1","-1","-2","-2","0","-3","-1","4","-3","2","-2","-1","-4" },
 {"B","-2","-1","4","4","-3","0","1","-1","0","-3","-4","0","-3","-3","-2","0","-1","-4","-3","-3","4","-3","0","-1","-4" },
 {"J","-1","-2","-3","-3","-1","-2","-3","-4","-3","3","3","-3","2","0","-3","-2","-1","-2","-1","2","-3","3","-3","-1","-4" },
 {"Z","-1","0","0","1","-3","4","4","-2","0","-3","-3","1","-1","-3","-1","0","-1","-2","-2","-2","0","-3","4","-1","-4" },
 {"X","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-4"},
 {"*","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","-4","1" } 

} ; 



void printmatrix(){

for (int i = 0; i< 26 ; i++){
	for (int j =0 ; j<26; j++ )
		printf("|%s",blosum62[i][j] );
	printf(" .\n");
	}
}

int get_similarity(char* residusQuery , char* residusDB){

int score = 0;
int i = 1;
int j = 1;
while ( j < 26)
	if ( *residusQuery == *blosum62[0][j])	
			break;
	else 
		j++ ;

while( i <26)
	if( *residusDB  == *blosum62[i][0])
		break;
	else 
		i++;

score = atoi(blosum62[i][j]);	
return score;
}



const int gap = -4 ;

int alignment_method(string fasta_seq , string  input_seq){
	// 1- the first step is building a scoring matrix 
	// 2 - second you should find the most suitable value (MAX in the matrix)
	
	int n = fasta_seq.length()+1;
	int m = input_seq.length() +1;
	
	std::vector< std::vector<int> > scoring_matrix;
	scoring_matrix.resize(n) ;
	for (int index =0 ; index< n ;++index )
		scoring_matrix[index].resize(m);
	scoring_matrix[0][0] = 0 ; //initialize the first element of the matrix to 0
	int max_value = scoring_matrix[0][0] ;// the most suitable value for the trace back
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
									scoring_matrix[i][j] =0 ;
									max_value = max(max_value , scoring_matrix[i][j]) ;//MAJ le maximum
									 
								}	
						}
					else 
						{	
							if (j==0 )
								{		
										
										scoring_matrix[i][j] =0 ;// condition pour remplir la premiere colonne
										max_value = max(max_value , scoring_matrix[i][j]) ; //MAJ le maximum
								}
							else 
								{		
											if (input_seq.at(j-1) == fasta_seq.at(i-1))
												{ // si il existe un match entre les 2 sequences
										
													scoring_matrix[i][j] = max(max(max(scoring_matrix[i][j-1] + gap ,scoring_matrix[i-1][j] + gap) , scoring_matrix[i-1][j-1] + get_similarity( &input_seq.at(j-1) , &fasta_seq.at(i-1)) ),0) ;
													// au lieu de mettre match, faut chercher la similarité dans la matrice blosum62 entre les 2 résédus
												}
											else 
												{ // si il y a un mismatch
													scoring_matrix[i][j] = max(max(max(scoring_matrix[i][j-1] + gap ,scoring_matrix[i-1][j] +gap) , scoring_matrix[i-1][j-1] + get_similarity( &input_seq.at(j-1) , &fasta_seq.at(i-1))),0) ;
													// au lieu de mettre mismatch, faut chercher la similarité dans la matrice blosum62 entre les 2 résédus
												}
											max_value = max(max_value , scoring_matrix[i][j]) ;//MAJ le maximum
								}			
					}
				}
		}	
	return max_value;
}


