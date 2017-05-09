#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "headers/driver_ctrl.h"
#include "headers/driver_cptr.h"
#include "headers/rectangle.h"

void initialiser_rectangle(r_rect* r, char texte[])
{
	const int taille_max = 50;
	char input[taille_max];
	char* stop;

	printf("%s :\n", texte);

	printf("centre.x :\t");
	fgets(input, taille_max, stdin);
	stop = strchr(input, '\n');
	*stop = '\0';
	r->rec.centre.x = atof(input);

	printf("centre.y :\t");
	fgets(input, taille_max, stdin);
	stop = strchr(input, '\n');
	*stop = '\0';
	r->rec.centre.y = atof(input);

	printf("largeur :\t");
	fgets(input, taille_max, stdin);
	stop = strchr(input, '\n');
	*stop = '\0';
	r->rec.l = atof(input);

	printf("hauteur :\t");
	fgets(input, taille_max, stdin);
	stop = strchr(input, '\n');
	*stop = '\0';
	r->rec.h = atof(input);

	printf("angle :\t\t");
	fgets(input, taille_max, stdin);
	stop = strchr(input, '\n');
	*stop = '\0';
	r->angle = atof(input);

	printf("\n");
}

int main()
{	
	initialiser_rectangle(&ctrl_terrain, "terrain");
	initialiser_rectangle(&ctrl_but, "but");
	initialiser_rectangle(&ctrl_distributeur, "distributeur");
	initialiser_rectangle(&ctrl_depart, "depart");
	initialiser_rectangle(&ctrl_arrivee, "arrivee");
	initialiser_rectangle(&ctrl_robot, "robot");

	printf("%s\n", "Initalisation...");
	ctrl_init();
	printf("%s\n", "Demarrage...");
	ctrl_demarrer();
	printf("%s\n", "Attente...");
	sleep(5);
	printf("%s\nResultat : %d\n", "Arret...", ctrl_arret());
	return 0;
}
