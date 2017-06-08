#ifndef DEF_BALLON
#define DEF_BALLON

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

char* server();
void chargerBallon(char*);

#endif
