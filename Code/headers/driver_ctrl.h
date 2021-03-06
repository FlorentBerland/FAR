#ifndef DRIVER_CONTROL
#define DRIVER_CONTROL

// L'unite de distance est le centimetre
// La vitesse est en unites par periode d'horloge

#define VITESSE_MIN .1 // Vitesse en dessous de laquelle le robot
// est considere immobile
#define RAPPORT_VITESSES_MIN .05 // Rapport de vitesse entre les
// deux roues pour considerer que le robot tourne
#define ESPACEMENT_ROUES 8 // Ecart entre les roues
#define DEPORT_ROUES 3.5 // Distance entre le centre et l'axe des roues
#define CTRL_INTERVALLE 500 // Pas du moteur physique en ms
#define CTRL_TEMPS_INFINI -1 // Pas de duree calculable
#define MIN(a, b) ((a < b) ? a : b) // Utiles pour le calcul de la vitesse
#define MAX(a, b) ((a > b) ? a : b)
#define ABS(a) ((a >= 0) ? a : -a)

#include <stdbool.h>
#include <pthread.h>
#include "rectangle.h"
#include "gopigo.h"
#include "liste.h"
#include "serveur_robot_ballon.h"

r_rect ctrl_terrain;
r_rect ctrl_robot;
r_rect ctrl_but;
r_rect ctrl_distributeur;
r_rect ctrl_depart;
r_rect ctrl_arrivee;

Liste* _ctrl_objectifs; // Objectifs a faire
pthread_t _ctrl_pilotage; // Thread principal du driver
int _ctrl_horloge; // Temps en ticks depuis le demarrage du driver
bool _ctrl_continuer; // Continuer le pilotage ou terminer les threads

float _ctrl_vit_gauche; // Vitesse de la roue gauche
float _ctrl_vit_droite; // Vitesse de la roue droite

// Vitesses donnees a chaque roues au driver du robot (entre 0 et 255)
int _ctrl_vit_gopigauche;
int _ctrl_vit_gopidroite;

// Initialiser le driver
int ctrl_init();

// Lancer le pilote de controle
int ctrl_demarrer();

// Arreter le driver
int ctrl_arret();

// Boucle de controle du driver
void* _ctrl_loop(void*);

// Vitesse du robot (unites par ticks)
float _ctrl_vitesse();

// Vitesse de rotation en radians/tick
double _ctrl_vit_rot();

// Determine a partir des vitesses des roues si le robot est en mouvement rectiligne
bool _ctrl_en_mouvement();

// Determine a partir des vitesses des roues si le robot est en virage
bool _ctrl_en_virage();

// Retourne la zone suivante a atteindre
r_rect _ctrl_objectif_suivant();

// Calcule la distance entre le centre instantane de
// rotation et le milieu de l'axe des roues
r_vecteur _ctrl_CIR();

// Indique si l'objectif suivant est atteint
bool ctrl_objectif_atteint();

// Obtient la trajectoire relative entre le robot et l'objectif
r_vecteur ctrl_trajectoire_objectif();

// Postions anticipee du robot dans n ticks (si la vitesse ne
// change pas entre temps)
r_rect ctrl_anticipation(int);

// Retourne l'angle de l'objectif suivant par rapport au robot
// entre -pi et pi, sens anti-trigonometrique
double _ctrl_angle_objectif();

// Distance entre le robot et l'objectif suivant
double _ctrl_dist_objectif();

// Temps en ticks avant d'atteindre l'objectif
int _ctrl_temps_obj_dist();

// Temps en ticks avant d'etre aligne sur l'objectif
int _ctrl_temps_obj_angle();

// Amorce un virage pour atteindre l'objectif
void _ctrl_virage(double);

// Arrete le virage sans arreter le mouvement
void _ctrl_arret_virage();

// Calcule les vitesses des roues en cm/tick
void _ctrl_calcul_vitesse(int *, int *);

// Ajoute a la liste l'objectif suivant lorsque celui en cours est atteint
void _ctrl_nouvel_objectif();

#endif
