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
	int i; for(i=8;i>=1;i--)
	{
		printf("Demarrage dans %d secondes\n", i);
	}
	
	ctrl_robot = (r_rect){ 12.5, 12.5, 10, 20, 0 };
	ctrl_distributeur = (r_rect){ 12.5, 5*25+12.5, 25, 25, 0 };
	ctrl_but = (r_rect){ 100, 11*25+12.5, 200, 25, 0 };
	ctrl_terrain = (r_rect){ 100, 150, 200, 300, 0 };

	if(init())
	{
		printf("Erreur d'initialisation de gopigo\n");
		return 1;
	}
	if(ctrl_init())
	{
		printf("Erreur d'initialisation du driver de controle\n");
		return 1;
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
