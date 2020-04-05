#include "IO_module.h"
#include "conversions.h"



// A partir de l'offset d'une séquence trouvée dans le fichier .psq,
// la fonction retourne l'entête de la protéine (ex: sp|Q6GZX3|002L_FR...)
string extract_header(Fpin& f_pin, const int offset, ifstream& f_phr)
{
	char buffer[4];
	int n = 0;
	
	f_pin.seekg(f_pin.getOffsetSeq());
	f_pin.read(buffer, 4*sizeof(char));
	
	while (byte2int(buffer) - 1 != offset && n++ < f_pin.getNSeq())
	{
		f_pin.read(buffer, 4*sizeof(char));
		//cout << "byte : " << byte2int(buffer) << " offset(" << offset << ")" << " n : " << n << endl;
	}
	
	if (byte2int(buffer) - 1 == offset)
	{
		//cout << "n : " << n << " getNSeq(" << f_pin.getNSeq() << ")" << endl;
		
		f_pin.seekg(f_pin.tellg() - 4*(f_pin.getNSeq() + 3));
		f_pin.read(buffer, 4*sizeof(char));
		//cout << "res : " << byte2int(buffer) << endl;
	}
	
	f_phr.seekg(byte2int(buffer));
	char c = 0;
	
	while (c != 26)
		f_phr.read(&c, sizeof(char));
	
	//cout << "found : " << f_phr.tellg() << endl;
	
	f_phr.read(&c, sizeof(char));
	
	if (c < 0)
	{
		c -= 128;
		f_phr.seekg((int)f_phr.tellg() + (int)c);
	}
	
	int length = 80;
	
	char header[length + 1]; // +1 pour le caractère null
	
	f_phr.read(header, length * sizeof(char));
	header[length] = 0;
	
	//cout << "res2 : " << header << endl;
	
	string str(header);

	
	return str;
}





void extract_sequences(ifstream& f_pro, string& pro_info, string& sequence)
{
	string line;

	while (std::getline(f_pro, line))
	{
		if (line.find(">") == string::npos)
			sequence += line;
		else
			pro_info += line.substr(1, string::npos);
	}
}
