#ifndef DEF_COMMUNICATION
#define DEF_COMMUNICATION

#include <stdbool>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "liste.h"

#define COM_TAILLE_BUFFER 64 // Nombre d'octets a envoyer et a recevoir

void (*_com_cible)(char *); // Fonction a appeler en cas de reception
bool _com_continuer; // Continuer la reception des messages
int _com_port; // Numero de port de reception
pthread_t _com_reception; // Thread de reception des messages

/* Initialise le systeme de communication entre les robots
	Parametres :
		int : numero du port d'ecoute
		void(*)(char*) : fonction a appeler en cas de reception
			char* : donnees recues
*/
int com_init(int, void (*)(char *));

// Demarre la reception des messages
int com_demarrer();

// Arreter le systeme
int com_arret();

// Fonction d'écoute en boucle
void* _com_loop(void *);

/* Envoyer des donnees a l'adresse ip indiquee
	Parametres :
		char* : ip de destination
		char* : donnees a envoyer
*/
int com_envoyer(char *, char *);

// Thread d'envoi des donnees
void* _com_envoi(void *);

#endif