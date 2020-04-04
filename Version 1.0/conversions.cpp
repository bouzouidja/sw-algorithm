/**
 * 
 * conversions.cpp
 * 
 * Bibliothèque de fonctions utiles pour convertir différentes données.
 *
 **/

#include "conversions.h"

// Implémentation du tableau pour le fichier .psq
// Convertit les valeurs encodées (byte) en acide aminé (char)
char get_residue(char byte)
{
	if (byte == 0)
		return '\0';
	
	if (byte <= 9)
		return 'A' + byte - 1;
	
	if (byte == 27)
		return 'J';
	
	if (byte <= 13)
		return 'K' + byte - 10;
	
	if (byte == 26)
		return 'O';
	
	if (byte <= 18)
		return 'P' + byte - 14;
	
	if (byte == 24)
		return 'U';
	
	if (byte <= 23)
		return 'V' + byte - 19;
	
	if (byte == 25)
		return '*';
	
	// Aucune correspondance
	return '\0';
}


int32_t byte2int(const char* buffer)
{
    int32_t add = 0;
    
    if (buffer[3] < 0)
        add += 256;
    
    if (buffer[2] < 0)
        add += 256*256;
    
    if (buffer[1] < 0)
        add += 256*256*256;
    
    if (buffer[0] < 0)
        add += 256*256*256*256;
    
    return    buffer[3]
            + buffer[2]*256
            + buffer[1]*256*256
            + buffer[0]*256*256*256
            + add;
}
