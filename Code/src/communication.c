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
	return pthread_init(&_com_reception, NULL, &_com_loop, NULL);
}

int com_arret()
{
	_com_continuer = false;
	return pthread_cancel(_com_reception);
}

void* _com_loop(void *args)
{
	while(_com_continuer)
	{
		// reception
	}
}

int com_envoyer(char *IPadr, char *donnees){
	// IP, ce qu'il faut envoyer
  int sock;
  struct sockaddr_in sin;

  /* Creation de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);
 
  /* Configuration de la connexion */
  sin.sin_addr.s_addr = inet_addr(IP);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
 
  /* Tentative de connexion au serveur */
  connect(sock, (struct sockaddr*)&sin, sizeof(sin));
  printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr),
         htons(sin.sin_port));

  /* Envoi de donnees au serveur */
  char buffer2[32] = donnees;
  send(sock, buffer2, 32, 0);

  /* Fermeture de la socket client */
  close(sock);

  return EXIT_SUCCESS;
}
