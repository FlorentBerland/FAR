#ifndef DEF_TABLACH
#define DEF_TABLACH

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

#define _TH_TAILLE_INIT 4
#define _TH_COEF_AGRANDISSEMENT 4
#define _TH_DENSITE_MAX .75
#define _TH_DENSITE_MIN .08
#define _TH_DENSITE(t) ((double)t->nb_elt)/((double)t->taille_tab)

typedef struct { void* valeur; // Adresse de la valeur stockee
				void* cle; // Cle d'acces a cette valeur
				int col; // Case de la collision precedente
			} _th_alv;

typedef struct { _th_alv **tab; // Tableau de pointeur sur les alveoles
				int taille_tab; // Taille du tableau
				int nb_elt; // Remplissage du tableau
				int (*fct_hach)(void*); // Fonction de hachage
			} Tablach;

Tablach* th_creer(int(*)(void*));
Tablach* th_copier(Tablach*);
void th_detruire(Tablach*);
void th_vider(Tablach*);

void th_ajouter(Tablach*, int, void*);
void th_ajouter_h(Tablach*, void*, void*);

void th_modifier(Tablach*, int, void*);
void th_modifier_h(Tablach*, void*, void*);

void th_supprimer(Tablach*, int);
void th_supprimer_h(Tablach*, void*);

void* th_valeur(Tablach*, int);
void* th_valeur_h(Tablach*, void*);

bool th_existe(Tablach*, int);
bool th_existe_h(Tablach*, void*);

bool th_contient(Tablach*, void*);
int th_taille(Tablach*);




int _th_hachage(Tablach*, int); // Effectue seulement le modulo
int _th_sondage(Tablach*, int); // Recherche d'une case candidat
void _th_agrandir(Tablach*); // Agrandir la table si trop pleine
void _th_retrecir(Tablach*); // Retrecir la table si trop vide
int _th_atteindre(Tablach*, int); // Atteindre la case concernee par la cle
int _th_atteindre_h(Tablach*, void*); // Atteindre la case concernee par la cle
int _th_fct_hach(void*); // Fonction de hachage par defaut

#endif