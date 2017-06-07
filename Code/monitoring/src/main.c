#include "main.h"


char adServeur [15] = "162.38.111.103"; // A completer avec votre ip

void proc_exit(int sig) {
  wait();
}

char * readFile(char * fileName){
	FILE * file;
	file = fopen( fileName , "r");
	char * res = malloc(12*sizeof(char));
	fscanf(file, "%s", res);
	
	return res;
}


int main(void) {

  /* Pour eviter les zombies */
  signal(SIGCHLD, proc_exit);

  /* Socket et contexte d'adressage du serveur */
  struct sockaddr_in sin;
  int sock;
  socklen_t recsize = sizeof(sin);
    
  /* Socket et contexte d'adressage du client */
  struct sockaddr_in csin;
  int csock;
  socklen_t crecsize = sizeof(csin);

  /* Pour forker le moment venu */
  pid_t pid;
 
  /* Creation d'une socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuration */
  sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
  sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
  sin.sin_port = htons(PORT);               /* Listage du port */
  bind(sock, (struct sockaddr*)&sin, recsize);

  /* Demarrage du listage (mode server) */
  listen(sock, 5);

  for(;;) {
    /* Attente d'une connexion client */
    csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
    printf("Demande du serveur de monitoring reçu.\n");

    pid = fork();

    if (pid == 0) {
      /* Envoi de donnees au client */
    	char * pos;
    	char * verfiedPos;

    	pos = readFile("../dataPosition/position.txt");
    	verfiedPos = readFile("../dataPosition/verifiedPosition.txt");

      	char buffer[50] = "";
		strcat(buffer,adServeur);
		strcat(buffer,"/");

		strcat(buffer,pos);

		strcat(buffer,"/");

		strcat(buffer,verfiedPos);

		send(csock, buffer,50 , 0);
		printf("Envoi de %s\n", buffer);

      for(;;) {
        /* Reception de donnees du client */
        int res = recv(csock, buffer, 32, 0);
        if (res == 0){
          exit(0);
        }
        printf("Recu de la socket %d de %s:%d : %s\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port), buffer);
      }

      /* Fermeture de la socket dans les deux sens */
      shutdown(csock, 2);

      /* Fermeture de la socket client */
      close(csock);
    }//if
  }//for

  /* Fermeture de la socket serveur */
  close(sock);

  return EXIT_SUCCESS;

}
