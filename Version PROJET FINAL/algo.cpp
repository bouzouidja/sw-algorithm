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
	int m = input_seq.length() +1;
	int Q = gap_open + gap_extension;
	int R = gap_extension;
	int fasta_seq_bin[n];
	int input_seq_bin[m];
	int E[m][n];
	int F[m][n];
	int H[m][n];
	int max_local=0;	
	int max_value = 0;
	
	for(int i=0;i<n;i++){
		E[0][i]=0;
		F[0][i]=0;
		H[0][i]=0;
		string s1 = string(1,fasta_seq[i]);
		fasta_seq_bin[i]= CharToInt[s1];
	}
	for(int i=0;i<m;i++){
		F[i][0]=0;
		E[i][0]=0;
		H[i][0]=0;
		string s2 = string(1,input_seq[i]);
		input_seq_bin[i]= CharToInt[s2];
	}
	
	for(int i = 1; i < m; i++){
		for( int j = 1; j < n; j++){
			E[i][j]= max({H[i][j-1]-Q, E[i][j-1]-R});
			F[i][j]= max({H[i-1][j]-Q, F[i-1][j]-R});
			H[i][j]= max({H[i-1][j-1]+ blosumMatrix[input_seq_bin[i]][fasta_seq_bin[j]], E[i][j], F[i][j], 0});
			//cout << blosumMatrix[fasta_seq_bin[j]][input_seq_bin[i]] << endl;
			max_local=F[i][j];
			if(H[i][j]> max_local){
				max_local= H[i][j];			
			}
			if(E[i][j]> max_local){
				max_local= E[i][j];
			}
			if (max_local> max_value){
				max_value= max_local;
			}
		}
	}
	//cout << "queryy" << fasta_seq << endl;
	//cout << " prot" << input_seq << endl;
	cout << max_value << endl;
	//cout << "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS" << endl;
	return max_value;
}

void Algo::FillBlosumMatrix(ifstream &blosum_file){
	
	for (int i=0; i < 6; i++){	
		getline(blosum_file,ligne);
		//cout << ligne << endl;
	}
	blosum_file.ignore();
	
	for (int i=0; i < 24; i++){				//put the keys into a vector
		blosum_file >> cle;
		cles.push_back(cle);
	}
	
	for (int i=0; i < 24; i++){ 				//fill the new blosum matrix with the values of the blosum matrix file
		blosum_file >> pass;				//pass the first element
		for (int j=0; j < 24; j++){
			blosum_file >> donnee;			//extract data from blosum matrix file
			blosumMatrix[CharToInt[cles[i]]][CharToInt[cles[j]]] = donnee;  //fill new blosum matrix with right values
		}
	}
	for(int i=0;i<28;i++){
		for(int j=0;j<28;j++){
		cout << blosumMatrix[i][j] +1-1 << endl;
	}
	}
	}


