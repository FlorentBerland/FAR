#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../headers/driver_ctrl.h"
#include "../headers/driver_cptr.h"
#include "../headers/rectangle.h"
//#include "../headers/com_interface.h"

//Test de l'infrarouge
define pin_led 1
define pin_capt 11

/*
void detecter_noir(int val, int horloge)
{
	stop();
}
*/

int main()
{	

	pinMode(pin_led, "OUTPUT");
	analogWrite(pin_led, 255);
	pinMode(pin_capt, "INPUT");

	while(true)
	{
		printf("%d\n", digitalRead(pin_capt));
		sleep(1);
	}

	return 0;

	/* Test de l'infrarouge
	// pas fait parce que le robot a des problemes d'i2c
	// c
	// 

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
