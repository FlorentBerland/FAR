#include "../headers/communication.h"

int com_init(int port, void (*cible)(char *))
{
	_com_port = port;
	_com_cible = cible;
	return 0;
}

int com_demarrer()
{
	_com_continuer = true;
	return pthread_create(&_com_reception, NULL, &_com_loop, NULL);
}

int com_arret()
{
	_com_continuer = false;
	return pthread_cancel(_com_reception); // cancel plutot que join sinon il faudra recevoir un message pour terminer le thread
}

void* _com_loop(void *args)
{
	while(_com_continuer)
	{
		// reception
	}
	return NULL;
}

int com_envoyer(char *IPadr, char *donnees)
{
  return EXIT_SUCCESS;
}
