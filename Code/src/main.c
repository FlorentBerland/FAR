#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../headers/driver_ctrl.h"
#include "../headers/driver_cptr.h"
#include "../headers/rectangle.h"
#include "../headers/gopigo.h"
#include "../headers/positionnement.h"
//#include "../headers/com_interface.h" // Non fonctionnel et inutile pour le moment

//Test de l'infrarouge
#define pin_led 1
#define pin_capt 11

// Indique le numero de la case dans laquelle se situe la position
// (pas de distinction x/y car les cases sont carrees)
int pos_en_case(float position)
{
	return ((int)position)/25; // Une case = 25cm
}

// Retourne le centre de la case en cm depuis l'origine, x/y confondus
// car cases carrees
float centre_case(int centre_case)
{
	return (float)centre_case*25 + 12.5;
}

// Convertit une case en rectangle (pour le robot virtuel)
r_rect case_en_rectangle(int x, int y)
{
	rectangle_t rec = (rectangle_t){ centre_case(x), centre_case(y), 25, 25 };
	return r_t_vers_rect(rec);
}

// Recupere les positions initiales du robot, du DB et du VB
int lire_positions()
{
	FILE *fichier = fopen("bin/data/zones","r");
	if(fichier != NULL)
	{
		int bs = 15;
		char buffer[bs];
		fgets(buffer, bs, fichier); // Robot:
		fgets(buffer, bs, fichier); // case X
		ctrl_robot.rec.centre.x = centre_case(atoi(buffer));
		fgets(buffer, bs, fichier); // case Y
		ctrl_robot.rec.centre.y = centre_case(atoi(buffer));
		fgets(buffer, bs, fichier); // largeur
		ctrl_robot.rec.l = atof(buffer);
		fgets(buffer, bs, fichier); // longueur
		ctrl_robot.rec.h = atof(buffer);
		fgets(buffer, bs, fichier); // angle
		ctrl_robot.angle = r_radians(atof(buffer));

		fgets(buffer, bs, fichier); // DB:
		fgets(buffer, bs, fichier); // case X
		ctrl_distributeur.rec.centre.x = centre_case(atoi(buffer));
		fgets(buffer, bs, fichier); // case Y
		ctrl_distributeur.rec.centre.y = centre_case(atoi(buffer));
		ctrl_distributeur.rec.l = 25;
		ctrl_distributeur.rec.h = 25;
		ctrl_distributeur.angle = 0;

		fgets(buffer, bs, fichier); // VB:
		fgets(buffer, bs, fichier); // cases Y
		ctrl_but = (r_rect){ ctrl_distributeur.rec.centre.x, centre_case(atoi(buffer)), 25, 25, 0 };

		fclose(fichier);
		return 0;
	}
	else
	{
		return 1;
	}
}

void tester_serveur_position()
{
	ctrl_robot.rec.centre.x = PositionX();
	ctrl_robot.rec.centre.y = PositionY();
	printf("Position du robot : ");
	r_afficher_point(ctrl_robot.rec.centre);
	printf("\n");
	sleep(1);
}

int main(int argc, char **argv)
{
	if(lire_positions())
	{
		printf("Erreur d'ouverture du fichier de zones\n");
		return 1;
	}

	if(init())
	{
		printf("Erreur d'initialisation de gopigo\n");
		//return 1;
	}

	stop();
	set_speed(150);

	if(ctrl_init())
	{
		printf("Erreur d'initialisation du driver de controle\n");
		return 1;
	}

	int i=10; for(;i>=1;i--)
	{
		printf("Demarrage dans %d secondes\n", i);
		sleep(1);
	}

	ctrl_demarrer();

	for(i=1;i<=60;i++)
	{
		sleep(1);
		printf("\e[1;31m%d secondes ecoulees\e[0m\n", i);
	}

	ctrl_arret();
	stop();
}
