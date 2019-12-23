/**
 * 		INFO-H-304 REMISE FINALE DU PROJET
 * 
 * 	  @authors   Ismail Dabach, Sid Ahmed Bouzouidja, Sacha Meurice
 * 	  @date      18-12-2019
 * 
 * 
 **/

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
