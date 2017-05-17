#ifndef DEF_COM_INTERFACE
#define DEF_COM_INTERFACE

#include "communication.h"
#include "liste.h"

#define CINT_TAILLE_BUFFER_DONNEES 48
#define CINT_TAILLE_TYPE_INTEGRAL 8

typedef union {	char octets[CINT_TAILLE_TYPE_INTEGRAL];
				// 8 octets
				long l;
				double d;
				char chaine[CINT_TAILLE_TYPE_INTEGRAL];
				// 4 octets
				int i;
				float f;
				// 2 octets
				short s;
				// 1 octet
				char c;
				bool b;
}_cint_cast_donnees;

typedef enum {	POSITION,
				TEXTE,
				VRAC,
				PAS_DE_DONNEES
}cint_type_transfert;

// Donnees pretes a caster pour l'envoi
typedef struct {char id_robot;
		cint_type_transfert type;
		char donnees[CINT_TAILLE_BUFFER_DONNEES/CINT_TAILLE_TYPE_INTEGRAL][CINT_TAILLE_TYPE_INTEGRAL];
}_cint_donnees_brutes;

// Caster toutes les donnees a envoyer en buffer d'octets
typedef union {	char octets[COM_TAILLE_BUFFER];
				_cint_donnees_brutes donnees;
}_cint_cast_envoi;

void** _cint_fonctions_cibles; // Tableau contenant les fonctions a appeler en cas de reception de donnees
int _cint_port; // Port du robot
char _cint_id_robot; // Identifiant du robot




/* Initialiser l'interface
		Parametres :
			char : id du robot
			int : port
			void(*)(...) : fonctions inutiles pour bourrer
*/
int cint_init(char, int, void(*)(char, double, double, double),
	void(*)(char, char, char *), void(*)(char, char, int));

// Demarre l'interface (lance la reception)
int cint_demarrer();

// Arrete l'interface (interrompt la reception)
int cint_arret();

/* Envoi des donnees a un equipier
		Parametres :
			char* : ip du destinataire
			cint_type_transfert : type d'infos a envoyer
			... : donnees a transmettre
*/
int cint_envoyer(char*, cint_type_transfert, ...);

/* Envoi à tous les partenaires
		Parametres :
			Liste* : liste des partenaires
			cint_type_transfert : type d'infos a envoyer
			... : donnees a transmettre
*/
int cint_envoyer_m(Liste*, cint_type_transfert, ...);

// Traduit les octets recus en donnees exploitables
void _cint_traiter_reception(char*);

// Copie c2 dans c1 avec une taille de tableau
void _cint_copier_tableau(char*, char*, int);

#endif