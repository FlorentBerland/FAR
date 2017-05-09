#ifndef DEF_LISTE
#define DEF_LISTE

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>

typedef struct { bool est_tete; void* prec, *suiv; int taille; } Liste;
typedef struct { bool est_tete; void* prec, *suiv; void* valeur; } _l_contenu;


/*
	Cree une nouvelle liste vide et renvoie un pointeur sur
	cette liste
*/
Liste* l_creer();


/*
	Cree une nouvelle liste remplie avec des valeurs et renvoie
	un pointeur sur cette liste
	Parametres :
		int : nombre de valeurs transmises apres celle-ci
		... : pointeurs génériques (void*) sur les elements a stocker
*/
Liste* l_creer_args(int, ...);


/*
	Copie la liste transmise en parametre et retourne un pointeur
	sur la copie
	Parametres :
		Liste* : Liste a copier
*/
Liste* l_copier(Liste*);


/*
	Desaloue la memoire occupee par la liste, mais ne detruit
	pas les elements contenus. Liste vaut pointe sur un emplacement
	vide a la fin
	Parametres :
		Liste* : liste a detruire
*/
void l_detruire(Liste*);


/*
	Ajoute un element en fin de liste
	Parametres :
		Liste* : liste a modifier
		void* : element a ajouter
*/
void l_ajouter(Liste*, void *);


/*
	Insere un element a la position indiquee dans la liste
	Parametres :
		Liste* : liste a modifier
		int : position
		void* : element a ajouter
*/
void l_inserer(Liste*, int, void *);


/*
	Supprime l'element a la position indiquee dans la liste
	Parametres :
		Liste* : liste a modifier
		int : position de l'element a supprimer
*/
void l_supprimer(Liste*, int);


/*
	Modifie la valeur d'un element a la case donee
	Parametres :
		Liste* : liste a modifier
		int : case de l'element
		void* : nouvelle valeur
*/
void l_modifier(Liste*, int, void*);


/*
	Obtient la valeur stockee a la case donne
	Parametres :
		Liste* : liste concernee
		int : case de l'element a obtenir
*/
void* l_element_a(Liste*, int);

/*
	Vide la liste de tous ses elements
	Parametres :
		Liste* : liste a vider
*/
void l_vider(Liste*);


/*
	Inverse l'ordre des elements de la liste
	Parametres :
		Liste* : liste a inverser
*/
void l_inverser(Liste*);


/*
	Renvoie le nombre d'elements de la liste
	Parametres :
		Liste* : liste concernee
*/
int l_taille(Liste*);


/*
	Execute une procedure sur chaque element de la liste
	Parametres :
		Liste* : liste a iterer
		void(*)(int,void*,void**) : procedure a executer
		void* : parametres optionnels de l'appel de la procedure
	Parametres de la procedure :
		int : position de l'element itere dans la liste
		void* : element itere
		void* : parametres optionnels a recevoir
*/
void l_foreach(Liste*, void (*)(int, void*, void*), void*);


/* Indique si l'element est la tete de liste */
bool _l_est_tete(void *);
/* Retourne un pointeur sur la i-eme case */
void* _l_pointer(Liste*, int);
/* Appel recursif de la recherche du pointeur dans l'ordre */
void* _l_pointer_av(_l_contenu *, int);
/* Appel recursif de la recherche du pointeur dans l'ordre inverse*/
void* _l_pointer_ar(_l_contenu *, int);
/* Ajoute les elements iteres d'une liste vers sa copie */
void _l_ajout_it(int, void*, void*);

#endif