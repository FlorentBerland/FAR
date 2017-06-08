#include "../headers/ipipip.h"

/*int main(void)
{
	
	return 0;
}
*/


char* get_ip(void)
{
    char* IP = malloc(15*sizeof(char));
    FILE* fichier = NULL;

    fichier = fopen("bin/data/ipipip.txt", "r");

    if (fichier != NULL)
    {
        // On peut lire dans le fichier
    	fgets(IP, sizeof(IP), fichier);
    }
    else
    {
        // On affiche un message d'erreur
        printf("Impossible d'ouvrir le fichier ipipip.txt");
    }
    fclose(fichier);

    return IP;
}
