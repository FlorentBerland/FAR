#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#define PORT 10000

int main(void);

/** 
* @brief Retourne la chaine de caractere lu dans le fichier passée en parametre
* @param fileName La nom du fichier a lire
* @return la chaine lu
*/ 
char * readFile(char * fileName);