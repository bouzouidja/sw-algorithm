#include "Fpin.h"
#include "conversions.h"
#define BUFFER_SIZE 4

#include <iostream>
using std::cout;
using std::endl;

Fpin::Fpin(string filename)
{
	file = new ifstream(filename);
	
	if (!file->is_open()) {
		cout << "Merci de spécifier un nom de fichier valide." << endl;
		exit(1);
	}
	
	extract_pin();
}

void Fpin::extract_pin()
{
	char buffer[BUFFER_SIZE];
	
	file->read(buffer, BUFFER_SIZE);
	version = byte2int(buffer);
	
	file->read(buffer, BUFFER_SIZE);
	db_type = byte2int(buffer);
	
	file->read(buffer, BUFFER_SIZE);
	title_length = byte2int(buffer);
	
	title = new char[title_length + 1]; // +1 pour le caractère de fin de chaîne
	file->read(title, title_length);
	title[title_length] = '\0';
	
	file->read(buffer, BUFFER_SIZE);
	timestamp_length = byte2int(buffer);
	
	timestamp = new char[timestamp_length + 1]; // +1 pour le caractère de fin de chaîne
	file->read(timestamp, timestamp_length);
	timestamp[timestamp_length] = '\0';
	
	file->read(buffer, BUFFER_SIZE);
	n_seq = byte2int(buffer);
	
	// Le nb de residues est codé sur un Int64
	// Passons cette information pour le moment
	file->read(buffer, 2*BUFFER_SIZE);
	
	file->read(buffer, BUFFER_SIZE);
	max_seq = byte2int(buffer);
	
	pos_offset_hdr = file->tellg();
}


void Fpin::close()
{
	delete 		file;
	delete[]	title;
	delete[]	timestamp;
}

char* Fpin::getTitle()
{
	return title;
}

char* Fpin::getTimestamp()
{
	return timestamp;
}

string Fpin::getDbType()
{
	if (db_type == 0)
		return "DNA";
	else if (db_type == 1)
		return "Protein";
	else
		return "DB Type undefined";
}

int32_t Fpin::getVersion()
{
	return version;
}

// Renvoie la position de la "header offset table"
int Fpin::getOffsetHdr()
{
	return pos_offset_hdr;
}


// Renvoie la position de la "header offset table"
int Fpin::getOffsetSeq()
{
	return pos_offset_hdr + 4*(n_seq + 1);
}


void Fpin::seekg(int offset)
{
	file->seekg(offset);
}

void Fpin::read(char* buffer, int n)
{
	file->read(buffer, n);
}


int32_t Fpin::getNSeq()
{
	return n_seq;
}

int Fpin::tellg()
{
	return file->tellg();
}
