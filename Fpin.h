/**
 * 
 * 		Cette classe représente un fichier binaire .pin
 */


#ifndef FPIN_H
#define FPIN_H

#include <string>
#include <fstream>
using std::ifstream;
using std::string;



class Fpin
{
	public:
	
	
	Fpin(string filename);
	void close();
	
	char* getTitle();
	char* getTimestamp();
	string getDbType();
	
	int getOffsetHdr();
	int getOffsetSeq();
	int32_t getVersion();
	int32_t getNSeq();
	
	
	void seekg(int offset);
	void read(char* buffer, int n);
	int tellg();
	
	
	private:

	void extract_pin();

	ifstream* 	file;
	
	int32_t 	version,
				db_type,
				title_length,
				timestamp_length,
				n_seq,
				max_seq;
	
	char*		title;
	char*		timestamp;
	
	// Position de la "header offset table"
	int			pos_offset_hdr;
};

#endif
