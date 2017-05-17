#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../headers/driver_ctrl.h"
#include "../headers/driver_cptr.h"
#include "../headers/rectangle.h"
#include "../headers/com_interface.h"

/* Test de l'infrarouge
#define pin_led 1
#define pin_capt 11

void detecter_noir(int val, int horloge)
{
	stop();
}
*/

int main()
{	

	ctrl_init();
	ctrl_demarrer();
	int i=1;
	for(;i<=10;i++)
	{
		sleep(1);
		printf("%d secondes ecoulees\n", i);
	}
	ctrl_arret();

	/* Test de l'infrarouge
	// pas fait parce que le robot a des problemes d'i2c
	// et qu'il faut toujours une heure pour obtenir la moindre
	// aide les rares fois ou on est encadres.

	init();

	pinMode(pin_led, "OUTPUT");
	analogWrite(pin_led, 255);

	cptr_init();
	cptr_ajbool_dtct_etat(pin_capt, false, &detecter_noir);
	cptr_demarrer();


	fwd();
	sleep(5);
	printf("%s\n", "temps ecoule");
	stop();
	cptr_arret(); */
}
