#ifndef DEF_RECTANGLE
#define DEF_RECTANGLE

/*
	Definitions utiles pour le document :
		relatif : coordonnees dans le repere propre d'un rectangle (toujours specifie)
		absolu : coordonnees par rapport a l'origine (rectangle toujours precise)
*/


#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define ORIGINE (r_point){ 0, 0 }
#define VECTEUR_NUL (r_vecteur){ 0, 0 }
#define REC_ORIGINE (r_rect){ 0, 0, 0, 0, 0 }

#define PI 3.14159265359

typedef struct {float x;
				float y;
				} r_point;

typedef r_point r_vecteur;

typedef struct {r_point p1; // Angle sup gauche
				r_point p2; // Angle inf droit
				} rectangle_p;

typedef struct {r_point centre;
				float l;
				float h;
				} rectangle_t;

typedef struct {rectangle_t rec;
				float angle; // Inclinaison du rectangle
				} r_rect;

// Obtention des coordonnees des points du rectangle
r_point r_sup_gauche(r_rect);
r_point r_sup_droit(r_rect);
r_point r_inf_gauche(r_rect);
r_point r_inf_droit(r_rect);
r_point r_centre(r_rect);
float r_angle(r_rect);

rectangle_p r_t_vers_p(rectangle_t);
rectangle_t r_p_vers_t(rectangle_p);
r_rect r_p_vers_rect(rectangle_p);
r_rect r_t_vers_rect(rectangle_t);

// Assignation d'un angle a un rectangle (autour de son centre)
r_rect r_orienter_abs(r_rect, float);

// Rotation d'un rectangle de n radians autour de son centre
// (incrementation de l'angle)
r_rect r_orienter_rel(r_rect, float);

// Rotation d'un rectangle autour d'un centre absolu
r_rect r_rotation_abs(r_rect, r_point, float);

// Rotation d'un rectangle autour d'un centre relatif
r_rect r_rotation_rel(r_rect, r_point, float);

// Translation absolue d'un rectangle d'un vecteur
r_rect r_translation_abs(r_rect, r_vecteur);

// Translation relative d'un rectangle d'un vecteur
r_rect r_translation_rel(r_rect, r_vecteur);

// Coordonnees d'un point relatif vers absolu
r_point r_point_vers_abs(r_point, r_rect);

// Coordonnees d'un point absolu vers relatif
r_point r_point_vers_rel(r_point, r_rect);

// Coordonnees d'un rectangle relatif r1 vers absolu
r_rect r_rect_vers_abs(r_rect, r_rect);

// Coordonnees d'un rectangle absolu r1 vers relatif
r_rect r_rect_vers_rel(r_rect, r_rect);

// Determine si un point est dans le rectangle
bool r_pt_dans_rec(r_rect, r_point);

// Determine si deux rectangles se superposent partiellement
bool r_croisent(r_rect, r_rect);

// Determine si un rectangle r1 en recouvre un autre r2
bool r_recouvre(r_rect, r_rect);

// Module d'un vecteur
float r_module(r_vecteur);

// Argument d'un vecteur, entre -pi et pi
float r_arg(r_vecteur);

// Conversion de degres en radians
float r_radians(float);

// Conversion de radians en degres
float r_degres(float);

// Retourne le vecteur entre p1 et p2
r_vecteur r_creer_vecteur(r_point, r_point);

// Affiche un rectangle
void r_afficher_rect(r_rect);

// Affiche un vecteur
void r_afficher_vect(r_vecteur);

// Affiche un point
void r_afficher_point(r_point);

// Determine si deux points sont egaux
bool r_points_egaux(r_point, r_point);

// Determine si deux rectangles sont egaux
bool r_t_egaux(rectangle_t, rectangle_t);

// Determine si deux rectangles sont egaux
bool r_rect_egaux(r_rect, r_rect);

#endif
