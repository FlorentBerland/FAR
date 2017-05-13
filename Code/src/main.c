#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../headers/driver_ctrl.h"
#include "../headers/driver_cptr.h"
#include "../headers/rectangle.h"
#include "../headers/gopigo.h"
//#include "../headers/com_interface.h"

//Test de l'infrarouge
#define pin_led 1
#define pin_capt 11

int main(int argc, char **argv)
{	
	/*
	init();
	pinMode(pin_led, "OUTPUT");
	analogWrite(pin_led, 255);
	pinMode(pin_capt, "INPUT");
	int i=0;
	for(;i<100;i++)
	{
		printf("%d\n", digitalRead(pin_capt));
		sleep(1);
	}
	*/

	init();	

	fwd();
	pi_sleep(5000);
	stop();
/*
	ctrl_robot = REC_ORIGINE;
	ctrl_distributeur = (r_rect){ 0, 100, 10, 10, 0 };

	ctrl_init();
	ctrl_demarrer();
	
	int i; for(i=1;i<=10;i++)
	{
		sleep(1);
		printf("\e[1;31m%d secondes ecoulees\e[0m\n", i);
	}

	ctrl_arret();*/
}
