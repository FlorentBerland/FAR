#ifndef DEF_CPTR
#define DEF_CPTR

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "liste.h"
#include "tablach.h"
#include "gopigo.h"

#define CPTR_INTERVALLE_ANALYSE 100 // Temps entre deux analyses en ms

typedef enum { LOGIQUE = 0,
				ANALOGIQUE = 1
			 } _cptr_type; // Type de capteur (on distingue le capteur 1
			 // logique du capteur 1 analogique)

typedef struct {int pin;
				_cptr_type type;
				} _cptr_def; // Un capteur est identifié par son type et sa broche

typedef struct {int param1;
				int param2;
				void (*cible)(int, int);
				bool (*analyse)(int, int, int, int);
				} _cptr_detecteur; // Detecteur (parametres de declenchement et fonctions associees(valeur, horloge))

typedef struct {int actuelle;
				int precedente;
				} _cptr_valeurs; // Etat d'un capteur

typedef struct {_cptr_def capteur;
				_cptr_valeurs valeurs;
				Liste* detecteurs;
				} _cptr_assoc; // Un capteur et la liste de ses detecteurs associes


pthread_t _cptr_analyseur; // Tache d'analyse deleguee a un autre thread
int _cptr_horloge; // Temps en ticks depuis le demarrage du pilote
bool _cptr_continuer; // Indique au thread d'analyse de continuer a fonctionner
Liste* _cptr_l; // Liste des capteurs et de leurs detecteurs associes
Liste* _cptr_av_analyse; // Fonctions a appeler avant chaque analyse
Liste* _cptr_ap_analyse; // Fonctions a appeler apres chaque analyse
Tablach* _cptr_tab_capt; // Table contenant les positions des capteurs dans la liste _cptr_l
/*
	_cptr_l contient des pointeurs sur des _cptr_assoc ( = capteur + valeurs captees + liste de detecteurs)
	_cptr_tab_capt contient aux cles (_cptr_def) l'indice de l'association de ce capteur
		et de ses detecteurs dans _cptr_l
*/

int cptr_init();

int cptr_demarrer();

int cptr_arret();

void * _cptr_loop(void *);

// Ajouter un detecteur de changement d'etat de capteur booleen
void cptr_ajbool_chgt_etat(int, void (*)(int, int));

// Ajouter un detecteur de passage a un certain etat d'un capteur booleen
void cptr_ajbool_dtct_etat(int, bool, void (*)(int, int));

// Ajouter un detecteur de changement de valeur pour un capteur analogique
void cptr_ajanalog_chgt_val(int, void (*)(int, int));

// Ajouter un detecteur de franchissement d'un seuil pour un capteur analogique
void cptr_ajanalog_seuil(int, int, void (*)(int, int));

// Ajouter un detecteur de depassement de seuil pour un capteur analogique
void cptr_ajanalog_dep_sup(int, int, void (*)(int, int));

// Ajouter un detecteur de passage inferieur au seuil pour un capteur analogique
void cptr_ajanalog_dep_inf(int, int, void (*)(int, int));

// Ajouter un detecteur d'entree dans un intervalle de valeurs d'un capteur analogique
void cptr_ajanalog_entr_interv(int, int, int, void (*)(int, int));

// Ajouter un deteteur de sortie d'un intervalle de valeurs d'un capteur analogique
void cptr_ajanalog_sort_interv(int, int, int, void (*)(int, int));

// Ajouter un detecteur de valeur nulle pour un capteur analogique
void cptr_ajanalog_nul(int, void (*)(int, int));

// Ajouter un detecteur de saturation d'un capteur analogique
void cptr_ajanalog_sat(int, void (*)(int, int));

// Lancement de la fonction cible avant chaque analyse des capteurs
void cptr_ajautre_avanal(void (*)(int, int));

// Lancement de la fonction cible apres chaque analyse des capteurs
void cptr_ajautre_apanal(void (*)(int, int));


// Fonctions qui selon les valeurs precedentes, actuelles et les parametres (seuils etc)
// determinent si la detection a reussi
bool _cptr_dtctbool_chgt_etat(int, int, int, int);

bool _cptr_dtctbool_dtct_etat(int, int, int, int);

bool _cptr_dtctanalog_chgt_val(int, int, int, int);

bool _cptr_dtctanalog_seuil(int, int, int, int);

bool _cptr_dtctanalog_dep_sup(int, int, int, int);

bool _cptr_dtctanalog_dep_inf(int, int, int, int);

bool _cptr_dtctanalog_entr_interv(int, int, int, int);

bool _cptr_dtctanalog_sort_interv(int, int, int, int);

bool _cptr_dtctanalog_nul(int, int, int, int);

bool _cptr_dtctanalog_sat(int, int, int, int);

// Appel itere des fonctions avant et apres analyse des capteurs
void _cptr_appel(int, void*, void*);

// Mise a jour iteree des capteurs
void _cptr_maj_capt(int, void*, void*);

// Lancement de la procedure de detection pour tous les
// detecteurs du capteur itere
void _cptr_tests_capt(int, void*, void*);

// Verification du detecteur itere et lancement de la fonction cible
void _cptr_lancer_detection(int, void*, void*);

// Fonction de hachage de la structure _cptr_def
int _cptr_hach_cptr_def(void*);

// Ajout d'un nouveau detecteur a sa place (ajout du capteur si necessaire)
void _cptr_ajouter_detecteur(_cptr_def, _cptr_detecteur*);

// Detruire le contenu de la liste de capteurs et de la table de hachage
void _cptr_detruire_l_th(int, void*, void*);

// Detruire chaque detecteur
void _cptr_detruire_detect(int, void*, void*);

/* Detecteurs :
	- capteurs booleens :
		- changement d'etat (pin)->(nouvel etat)
		- detecter un etat particulier (pin, etat)->()

	- capteurs analogiques :
		- franchissement de seuil (pin, seuil)->(valeur)
		- depassement superieur de seuil (pin, seuil)->(valeur)
		- depassement inferieur de seuil (pin, seuil)->(valeur)
		- entree dans un intervalle de valeurs (pin, min, max)->(valeur)
		- sortie d'intervalle de valeurs (pin, min, max)->(valeur)
		- signal nul (pin)->()
		- saturation (pin)->()

	- autres :
		- declenchement avant chaque analyse ()->()
		- declenchement apres chaque analyse ()->()
*/

#endif
