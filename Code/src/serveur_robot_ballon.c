#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Appels et fonctions systeme */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Bibliothéques usuelles */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PORT 10002


char* server(){

  /******* retourne buffer du type :  "111221212212" ou "null"  *****/


  /* Socket et contexte d'adressage du serveur */
  struct sockaddr_in sin;
  int sock;
  socklen_t recsize = sizeof(sin);
  char* buffer = malloc(32*sizeof(char));


    
  /* Socket et contexte d'adressage du client */
  struct sockaddr_in csin;
  int csock;
  socklen_t crecsize = sizeof(csin);
 
  /* Creation d'une socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuration */
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  /* Adresse IP automatique */
  sin.sin_family = AF_INET;
  /* Protocole familial (IP) */
  sin.sin_port = htons(PORT);

  /* Listage du port */

  bind(sock, (struct sockaddr*)&sin, recsize);

  /* Demarrage du listage (mode server) */
  listen(sock, 5);

  /* Attente d'une connexion client */
  csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
  recv(csock, buffer, 32, 0);

  /* Fermeture de la socket serveur */
  close(sock);

  return buffer;

}

/*int main(){
  printf("%s\n",server());
  fflush(NULL);
  return 0;
}*/

