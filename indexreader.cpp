#include "searchindex.h"


inline void BigtoLittleEndian (int &x) {
   x = ((x >> 24) & 0xffL) | ((x >> 8) & 0xff00L) | ((x << 8) & 0xff0000L)
   | ((x << 24) & 0xff000000L);
}
int indexReader(ifstream& indexFile){
	int version,dtype,len,tlen,nSeq,lenSMax=0;
	int64_t residue= 0;
	
	indexFile.read((char*) &version, sizeof(version));
	BigtoLittleEndian(version);
	cout<< "Version"<< version << endl;
	indexFile.read((char*) &dtype, sizeof(dtype));
	BigtoLittleEndian(dtype);
	cout<< "Type"<< dtype << endl;
	indexFile.read((char*) &len, sizeof(len));
	BigtoLittleEndian(len);
	indexFile.read((char*) &tlen, sizeof(tlen));
	BigtoLittleEndian(tlen);
	
	
	char Title[tlen];
	indexFile.read((char*) &Title, len*sizeof(char));
	cout<< "Title"<< Title << endl;
	
	indexFile.read((char*) &tlen, sizeof(len));
	BigtoLittleEndian(tlen);
	
	char Timestamp[tlen];
	indexFile.read((char*) &Timestamp,tlen*sizeof(char));
	cout<< "Timestamp"<< Timestamp << endl;
	indexFile.read((char*) &nSeq, sizeof(nSeq));
	BigtoLittleEndian(nSeq);
	cout<< "Number of Sequence"<< nSeq << endl;
	indexFile.read((char*) &residue,sizeof(residue));
	cout<< "Residu count"<< residue << endl;
	indexFile.read((char*) &lenSMax,sizeof(lenSMax));
	BigtoLittleEndian(lenSMax);
	cout<< "Sequence max"<< lenSMax << endl;
	
	int Offheader[nSeq+1];
	for(int i=0;i< (nSeq+1);i++){
		indexFile.read((char*)&Offheader[i], sizeof(int));
		BigtoLittleEndian(Offheader[i]);
	}	
	int OffSeq[nSeq+1];
		for(int i=0;i< (nSeq+1);i++){
		indexFile.read((char*)&OffSeq[i], sizeof(int));
		BigtoLittleEndian(OffSeq[i]);
	}
	
	return 0;
}


