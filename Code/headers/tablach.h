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

/* Retourne un pointeur sur une nouvelle table, vide
		Parametre :
			int(*)(void*) : fonction de hachage pour les donnees stockees NULL
				pour utiliser des cles entieres
*/
Tablach* th_creer(int(*)(void*));

/* Retourne une copie de la table. Les objets pointes ne sont pas copies
(les adresses memoire sont copiees)
		Parametre :
			Tablach* : table a copier
*/
Tablach* th_copier(Tablach*);

/* Detruit completement la table, n'efface pas les valeurs contenues
		Parametre :
			Tablach* : table a detruire
*/
void th_detruire(Tablach*);

/* Vide la table de tous ses elements
		Parametre :
		Tablach* : Table a vider
*/
void th_vider(Tablach*);

/* Ajoute un element a la cle specifiee
		Parametres :
			Tablach* : table concernee
			int : cle (si la fonction de hachage est NULL)
			void* : donnee a stocker
*/
void th_ajouter(Tablach*, int, void*);

/* Ajoute un element a la cle specifiee
		Parametres :
			Tablach* : table concernee
			void* : cle
			void* : donnee a stocker
*/
void th_ajouter_h(Tablach*, void*, void*);

/* Modifie un element a la cle specifiee
		Parametres :
			Tablach* : table concernee
			int : cle (si la fonction de hachage est NULL)
			void* : nouvelle donnee (l'ancienne n'est pas detruite)
*/
void th_modifier(Tablach*, int, void*);

/* Modifie un element a la cle specifiee
		Parametres :
			Tablach* : table concernee
			void* : cle
			void* : nouvelle donnee (l'ancienne n'est pas detruite)
*/
void th_modifier_h(Tablach*, void*, void*);

/* Supprime un element a la cle specifiee
		Parametres :
			Tablach* : table concernee
			int : cle (si la fonction de hachage est NULL)
*/
void th_supprimer(Tablach*, int);

/* Supprime un element a la cle specifiee
		Parametres :
			Tablach* : table concernee
			void* : cle
*/
void th_supprimer_h(Tablach*, void*);

/* Obtient un element a la cle specifiee
		Parametres :
			Tablach* : table concernee
			int : cle (si la fonction de hachage est NULL)
*/
void* th_valeur(Tablach*, int);

/* Obtient un element a la cle specifiee
		Parametres :
			Tablach* : table concernee
			void* : cle
*/
void* th_valeur_h(Tablach*, void*);

/* Determine si une valeur est definie pour cette cle
		Parametres :
			Tablach* : table concernee
			int : cle a verifier (si la fonction de hachage est NULL)
*/
bool th_existe(Tablach*, int);

/* Determine si une valeur est definie pour cette cle
		Parametres :
			Tablach* : table concernee
			void* : cle a verifier
*/
bool th_existe_h(Tablach*, void*);

/* Determine si une valeur existe dans le tableau
		Parametres :
			Tablach* : table concernee
			void* : cle a verifier
*/
bool th_contient(Tablach*, void*);

/* Obtient le nombre d'elements de la table
		Parametre :
			Tablach* : table concernee
*/
int th_taille(Tablach*);




int _th_hachage(Tablach*, int); // Effectue seulement le modulo
int _th_sondage(Tablach*, int); // Recherche d'une case candidat
void _th_agrandir(Tablach*); // Agrandir la table si trop pleine
void _th_retrecir(Tablach*); // Retrecir la table si trop vide
int _th_atteindre(Tablach*, int); // Atteindre la case concernee par la cle
int _th_atteindre_h(Tablach*, void*); // Atteindre la case concernee par la cle
int _th_fct_hach(void*); // Fonction de hachage par defaut

#endif