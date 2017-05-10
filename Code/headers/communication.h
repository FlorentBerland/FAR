#ifndef DEF_COMMUNICATION
#define DEF_COMMUNICATION

#include <stdbool>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "liste.h"

char _com_id_robot; // Numero de robot
void (*_com_cible)(char *, int, char); // Fonction a appeler en cas de reception
bool _com_continuer; // Continuer la reception des messages
int _com_port; // Numero de port de reception
int _com_taille_buffer; // Nombre d'octets a envoyer et a recevoir

/* Initialise le systeme de communication entre les robots
	Parametres :
		char : numero du robot
		int : numero du port d'ecoute
		int : nombre d'octets a envoyer et a recevoir
		void(*)(char*,char) : fonction a appeler en cas de reception
			char* : donnees recues
			int : nombre d'octets de message
			char : numero du robot
*/
int com_init(char, int, int, void (*)(char *, int, char));

// Demarre la reception des messages
int com_demarrer();

// Arreter le systeme
int com_arret();

// Fonction d'écoute en boucle
void* _com_loop(void *);

/* Envoyer des donnees a l'adresse ip indiquee
	Parametres :
		char* : donnees a envoyer
		int : nombre d'octets a envoyer
		char* : ip de destination
*/
int com_envoyer(char *, int, char *);

/* Envoyer des donnees a des destinataires multiples
	Parametres :
		char* : donnees a envoyer
		int : nombre d'octets a envoyer (au maximum _com_taille_buffer)
		Liste* : liste des ip de destination
*/
int com_envoyer_m(char *, int, Liste *);


// Thread d'envoi des donnees
void* _com_envoi(void *);

#endif