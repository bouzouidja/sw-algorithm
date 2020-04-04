/**
 * 		INFO-H-304 REMISE FINALE DU PROJET
 * 
 * 	  @authors   Ismail Dabach, Sid Ahmed Bouzouidja, Sacha Meurice
 * 	  @date      18-12-2019
 * 
 * 
 **/
#include "algo.h"
using namespace std;

Algo::Algo(int gap_extension, int gap_open, ifstream &blosum_file)
{
	this->gap_open = gap_open;
	this->gap_extension = gap_extension;
	FillBlosumMatrix(blosum_file);
}

int Algo::Score_algo(string const fasta_seq , string const  input_seq, int gap_open, int gap_extension){
	int n = fasta_seq.length()+1;
	int m = input_seq.length()+1;
	int Q = gap_open + gap_extension;
	int R = gap_extension;
	int fasta_seq_bin[n];
	int input_seq_bin[m];
	int* E= new int [m*n];
	int* F= new int [m*n];
	int* H= new int [m*n];
	int max_local=0;	
	int max_value = 0;
	for(int i=0;i<n;i++){
		F[i]=0;
		H[i]=0;
		string s1 = string(1,fasta_seq[i]);
		fasta_seq_bin[i]= CharToInt[s1];
	}
	for(int i=0;i<m;i++){
		E[(i*n)]=0;
		H[(i*n)]=0;
		string s2 = string(1,input_seq[i]);
		input_seq_bin[i]= CharToInt[s2];
	}
	
	for(int i = 1; i < m; i++){
		for( int j = 1; j < n; j++){
			E[(i*n)+j]= max({H[(i*n)+(j-1)]-Q, E[(i*n)+(j-1)]-R});
			F[(i*n)+j]= max({H[((i-1)*n)+j]-Q, F[((i-1)*n)+j]-R});
			H[(i*n)+j]= max({H[((i-1)*n)+(j-1)]+ blosumMatrix[input_seq_bin[i-1]][fasta_seq_bin[j-1]], E[(i*n)+j], F[(i*n)+j], 0});
			max_local= F[(i*n)+j];
			if(H[(i*n)+j]> max_local){
				max_local= H[(i*n)+j];			
			}
			if(E[(i*n)+j]> max_local){
				max_local= E[(i*n)+j];
			}
			if (max_local> max_value){
				max_value= max_local;
			}
		}
	}
	delete[] E;
	delete[] F;
	delete[] H;
	return max_value;
}

void Algo::FillBlosumMatrix(ifstream &blosum_file){
	
	for (int i=0; i < 6; i++){	
		getline(blosum_file,ligne);
	}
	blosum_file.ignore();
	
	for (int i=0; i < 24; i++){	
		blosum_file >> cle;
		cles.push_back(cle);
	}
	
	for (int i=0; i < 24; i++){ 				
		blosum_file >> pass;				
		for (int j=0; j < 24; j++){
			blosum_file >> donnee;			
			blosumMatrix[CharToInt[cles[i]]][CharToInt[cles[j]]] = donnee;  
		}
	}

	}


