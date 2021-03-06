#include "../headers/driver_ctrl.h"

int ctrl_init()
{
	_ctrl_objectifs = l_creer_args(2, &ctrl_distributeur, &ctrl_arrivee);
	_ctrl_horloge = 0;
	return 0;
}

int ctrl_demarrer()
{
	_ctrl_continuer = true;
	return pthread_create(&_ctrl_pilotage, NULL, &_ctrl_loop, NULL);
}

int ctrl_arret()
{
	l_detruire(_ctrl_objectifs);
	_ctrl_continuer = false;
	return pthread_join(_ctrl_pilotage, NULL);
}

void* _ctrl_loop(void* args)
{
	int dst1 = enc_read(1);
	int dst2 = enc_read(2);

	while(_ctrl_continuer)
	{
		printf("\t\e[0;34m%d-ieme calcul de trajectoire : \e[0m\n", _ctrl_horloge + 1);

		_ctrl_calcul_vitesse(&dst1, &dst2);
		ctrl_robot = ctrl_anticipation(1);

		double angle = _ctrl_angle_objectif();
		double distance = _ctrl_dist_objectif();

		printf("\t\torientation du robot : %f\n\t\tangle robot-objectif : %f\n\t\tdistance robot-objectif : %f\n", r_degres(ctrl_robot.angle), r_degres(angle), distance);
		printf("\t\t\e[0;35mvitesse gauche : %f\n\t\tvitesse droite : %f\n\t\tvitesse de rotation : %f\n\e[0m", _ctrl_vit_gauche, _ctrl_vit_droite, r_degres(_ctrl_vit_rot()));

		if(distance>10)
		{
			if(angle>.5 || angle<-.5)
			{
				_ctrl_virage(angle);
			}
			else
			{
				_ctrl_vit_gopigauche = 150;
				_ctrl_vit_gopidroite = 150;
				motor2(1, _ctrl_vit_gopigauche);
				motor1(1, _ctrl_vit_gopidroite);
			}
		}
		else
		{
			_ctrl_vit_gopigauche = 0;
			_ctrl_vit_gopidroite = 0;
			stop();
			sleep(2);
			printf("\t\t\e[0;36mObjectif atteint !\e[0m\n");
			_ctrl_nouvel_objectif();
		}
		_ctrl_horloge++;

		usleep(CTRL_INTERVALLE * 1000);
	}
}

float _ctrl_vitesse()
{
	return (_ctrl_vit_gauche+_ctrl_vit_droite)/2;
}

double _ctrl_vit_rot()
{
	float cir = r_module(_ctrl_CIR());
	if(cir < .01)
	{
		return atan2(_ctrl_vit_gauche, ESPACEMENT_ROUES);
	}
	else if(cir >= 0)
	{
		return _ctrl_vitesse()/cir;
	}
	else
	{
		return 0;
	}
}

bool _ctrl_en_mouvement()
{
	return _ctrl_vitesse() >= VITESSE_MIN;
}

bool _ctrl_en_virage()
{
	if (!_ctrl_en_mouvement())
	{
		// Pas en mouvement rectiligne mais peut être en virage
		return _ctrl_vit_gauche>VITESSE_MIN || _ctrl_vit_droite>VITESSE_MIN;
	}
	float rapport = (_ctrl_vit_droite-_ctrl_vit_gauche)/_ctrl_vitesse();
	return rapport>=RAPPORT_VITESSES_MIN || rapport<=-RAPPORT_VITESSES_MIN;
}

r_vecteur _ctrl_CIR()
{
	float diff = _ctrl_vit_gauche-_ctrl_vit_droite;
	if(diff<.01 && diff>-.01)
	{
		return VECTEUR_NUL;
	}
	else
	{
		return (r_vecteur){ ESPACEMENT_ROUES*_ctrl_vit_droite/
			(_ctrl_vit_gauche-_ctrl_vit_droite) +
			ESPACEMENT_ROUES/2, 0 };
	}
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
	{
		if(!_ctrl_en_virage())
		{
			printf("\t\t\e[0;37mJe suis immobile !\e[0m\n");
			return ctrl_robot;
		}
		else
		{
			printf("\t\t\e[0;37mJe tourne sur moi-meme !\e[0m\n");
			return r_orienter_rel(ctrl_robot, _ctrl_vit_rot());
		}
	}
	else if(!_ctrl_en_virage())
	{ // En ligne droite
		printf("\t\t\e[0;37mJe suis en ligne droite !\e[0m\n");
		return r_translation_rel(ctrl_robot, (r_vecteur){ 0, _ctrl_vitesse()*ticks });
	}
	else
	{ // En virage
		printf("\t\t\e[0;37mJe suis en virage !\e[0m\n");
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


void _ctrl_virage(double angle)
{
	int vitesse = (_ctrl_vit_gopigauche+_ctrl_vit_gopidroite)/2;
	int increment = 50;
	if(!_ctrl_en_mouvement()) increment = 100;
	if(angle<0)
	{
		_ctrl_vit_gopigauche = vitesse+increment;
		_ctrl_vit_gopidroite = vitesse-increment;
	}
	else
	{
		_ctrl_vit_gopigauche = vitesse-increment;
		_ctrl_vit_gopidroite = vitesse+increment;
	}

	if(_ctrl_vit_gopigauche >= 0)
		motor2(1, MIN(_ctrl_vit_gopigauche,255));
	else
		motor2(0, MIN(-_ctrl_vit_gopigauche,255));

	if(_ctrl_vit_gopidroite >= 0)
		motor1(1, MIN(_ctrl_vit_gopidroite,255));
	else
		motor1(0, MIN(-_ctrl_vit_gopidroite,255));
}

void _ctrl_arret_virage()
{
	_ctrl_vit_gauche = _ctrl_vitesse();
	_ctrl_vit_droite = _ctrl_vit_gauche;
	motor2(1, _ctrl_vit_gauche);
	motor1(1, _ctrl_vit_droite);
}

void _ctrl_calcul_vitesse(int* dst1, int *dst2)
{
	int temp1 = enc_read(0);
	int temp2 = enc_read(1);

	_ctrl_vit_droite = (_ctrl_vit_gopidroite >= 0)?temp1-*dst1 : *dst1-temp1;
	*dst1 = temp1;
	_ctrl_vit_gauche = (_ctrl_vit_gopigauche >= 0)?temp2-*dst2 : *dst2-temp2;
	*dst2 = temp2;
}

void _ctrl_nouvel_objectif()
{
	r_rect obj_atteint = _ctrl_objectif_suivant();
	l_supprimer(_ctrl_objectifs, 0);
	if(r_rect_egaux(obj_atteint, ctrl_distributeur))
	{
		printf("\t\t\e[0;36mNouvel objectif : But\e[0m\n");
		l_inserer(_ctrl_objectifs, 0, &ctrl_but);
	}
	else
	{
		printf("\t\t\e[0;36mNouvel objectif : Distributeur\e[0m\n");
		l_inserer(_ctrl_objectifs, 0, &ctrl_distributeur);
	}
}
