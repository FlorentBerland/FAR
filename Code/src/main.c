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
	init();

	ctrl_robot = REC_ORIGINE;
	ctrl_distributeur = (r_rect){ 50, 50, 10, 10, 0 };
	ctrl_but = (r_rect){ -50, 50, 10, 10, 0};

	ctrl_init();
	ctrl_demarrer();
	
	int i; for(i=1;i<=10;i++)
	{
		sleep(1);
		printf("\e[1;31m%d secondes ecoulees\e[0m\n", i);
	}

	ctrl_arret();
	stop();
}
