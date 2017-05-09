#include "../headers/driver_ctrl.h"

int ctrl_init()
{
	_ctrl_objectifs = l_creer_args(1, &ctrl_distributeur);
	_ctrl_horloge_vitesse = 0;
	_ctrl_horloge = 0;
	return 0;
}

int ctrl_demarrer()
{
	_ctrl_continuer = true;
	return pthread_create(&_ctrl_analyse_vitesse, NULL, &_ctrl_loop_vitesse, NULL) ||
		pthread_create(&_ctrl_pilotage, NULL, &_ctrl_loop, NULL);
}

int ctrl_arret()
{
	l_detruire(_ctrl_objectifs);
	_ctrl_continuer = false;
	return pthread_join(_ctrl_pilotage, NULL) ||
		pthread_join(_ctrl_analyse_vitesse, NULL);
}

void* _ctrl_loop_vitesse(void* args)
{
	while(_ctrl_continuer)
	{
		printf("Vitesse : %d\n", _ctrl_horloge_vitesse);
		// Trouver un truc pour mesurer la vitesse de chaque roue


		// Et vite parce que c'est indispensable !!!
		_ctrl_horloge_vitesse++;

		usleep(CTRL_INTERVALLE_ANALYSE * 1000);
	}
	return NULL;
}

void* _ctrl_loop(void* args)
{
	while(_ctrl_continuer)
	{
		printf("Pilote : %d\n", _ctrl_horloge);
		// Faire le (sale) boulot



		_ctrl_horloge++;

		usleep(CTRL_INTERVALLE * 1000);
	}
}

float _ctrl_vitesse()
{
	return (_ctrl_vit_gauche+_ctrl_vit_droite)/2;
}

bool _ctrl_en_mouvement()
{
	return _ctrl_vitesse() >= VITESSE_MIN;
}

bool _ctrl_en_virage()
{
	if (!_ctrl_en_mouvement())
	{
		return false;
	}
	float rapport = (_ctrl_vit_droite-_ctrl_vit_gauche)/_ctrl_vitesse();
	return rapport>=RAPPORT_VITESSES_MIN || rapport<=-RAPPORT_VITESSES_MIN;
}

r_vecteur _ctrl_CIR()
{
	return (r_vecteur){ ESPACEMENT_ROUES*_ctrl_vit_droite/
	(_ctrl_vit_gauche-_ctrl_vit_droite) +
	ESPACEMENT_ROUES/2, DEPORT_ROUES };
}

r_rect _ctrl_objectif_suivant()
{
	return *(r_rect*)l_element_a(_ctrl_objectifs, 0);
}

bool ctrl_objectif_atteint()
{
	return r_recouvre(_ctrl_objectif_suivant(), ctrl_robot);
}

r_vecteur ctrl_trajectoire_objectif()
{
	return (r_vecteur)r_point_vers_rel((r_point)r_creer_vecteur(r_centre(_ctrl_objectif_suivant()),
		r_centre(ctrl_robot)), ctrl_robot);
}

r_rect ctrl_anticipation(int ticks)
{
	if(!_ctrl_en_mouvement())
	{ // Cas immobile
		return ctrl_robot;
	}
	else if(!_ctrl_en_virage())
	{ // En ligne droite
		return r_translation_rel(ctrl_robot, (r_vecteur){ 0, _ctrl_vitesse()*ticks });
	}
	else
	{ // En virage
		return r_rotation_rel(ctrl_robot, _ctrl_CIR(), _ctrl_vitesse()*ticks/_ctrl_CIR().x);
	}
}

double _ctrl_angle_objectif()
{
	return r_arg(r_creer_vecteur(ORIGINE,
		r_point_vers_rel(r_centre(_ctrl_objectif_suivant()),
		ctrl_robot)));
}

double _ctrl_dist_objectif()
{
	return r_module(r_creer_vecteur(r_centre(ctrl_robot),
		r_centre(_ctrl_objectif_suivant())));
}

double _ctrl_vit_rot()
{
	return _ctrl_vitesse()/r_module(_ctrl_CIR());
}

int _ctrl_temps_obj_dist()
{
	if(!_ctrl_en_mouvement())
	{
		return CTRL_TEMPS_INFINI;
	}
	else
	{
		return (int)(_ctrl_dist_objectif()/_ctrl_vitesse());
	}
}

int _ctrl_temps_obj_angle()
{
	if(!_ctrl_en_virage())
	{
		return CTRL_TEMPS_INFINI;
	}
	else
	{
		return (int)(_ctrl_angle_objectif()/_ctrl_vit_rot());
	}
}