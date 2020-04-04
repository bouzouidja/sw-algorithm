#ifndef FPIN_H
#define FPIN_H

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

/**
 * 
 * 		Cette classe représente un fichier binaire .pin
 */

class Fpin
{
	public:
	
	
	Fpin(string filename);
	void close();
	
	
	char* getTitle();
	char* getTimestamp();
	int getOffsetHdr();
	int getOffsetSeq();
	string getDbType();
	int32_t getVersion();
	void seekg(int offset);
	void read(char* buffer, int n);
	int tellg();
	int32_t getNSeq();
	
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
