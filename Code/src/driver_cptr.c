#include "../headers/driver_cptr.h"

int cptr_init()
{
	_cptr_l = l_creer();
	_cptr_av_analyse = l_creer();
	_cptr_ap_analyse = l_creer();
	// On fournit une fonction de hachage a la table lors de sa creation
	// pour hacher la structure _cptr_def
	_cptr_tab_capt = th_creer(&_cptr_hach_cptr_def);
	_cptr_horloge = 0;
	return 0;
}

int cptr_demarrer()
{
	_cptr_continuer = true;
	return pthread_create(&_cptr_analyseur, NULL, &_cptr_loop, NULL);
}

int cptr_arret()
{
	_cptr_continuer = false;

	l_foreach(_cptr_l, &_cptr_detruire_l_th, NULL);
	l_detruire(_cptr_l);
	l_detruire(_cptr_av_analyse);
	l_detruire(_cptr_ap_analyse);

	return pthread_join(_cptr_analyseur, NULL);
}

void * _cptr_loop(void *args)
{
	while(_cptr_continuer)
	{
		// Analyse de l'etat des capteurs et comparaison avec l'etat precedente

		/* Procede :
			Une liste est etablie, contenant le numero de pin et le type (analogique/logique)
			de chaque pin utilisee et une liste des detecteurs sur ce capteur
			Pour chaque capteur reference :
			- la valeur precedement stockee devient valeur precedente
			- la valeur actuelle du capteur et stockee a la place de l'ancienne
			- parcourir la liste des detecteurs de ce capteur, et pour chaque detecteur :
				- s'il ne detecte rien, ne rien faire
				- s'il detecte, declencher l'appel de la fonction pointee
		*/

		// Les fonctions avant analyse sont executees
		l_foreach(_cptr_av_analyse, &_cptr_appel, &_cptr_horloge);

		// Mise a jour de tous les capteurs
		l_foreach(_cptr_l, &_cptr_maj_capt, NULL);

		// Iteration des cateurs pour verifier chaque detecteur associe
		l_foreach(_cptr_l, &_cptr_tests_capt, NULL); // Bug ici

		// Les fonctions apres analyse sont executees
		l_foreach(_cptr_ap_analyse, &_cptr_appel, &_cptr_horloge);

		_cptr_horloge++;

		usleep(CPTR_INTERVALLE_ANALYSE * 1000);
	}
	return NULL;
}

void cptr_ajbool_chgt_etat(int pin, void (*fct)(int, int))
{
	// Creation d'un capteur
	_cptr_def capt = { pin, LOGIQUE };

	// Creation du detecteur
	_cptr_detecteur* detecteur = (_cptr_detecteur*)malloc(sizeof(_cptr_detecteur));
	detecteur->param1 = 0;
	detecteur->param2 = 0;
	detecteur->cible = fct;
	detecteur->analyse = &_cptr_dtctbool_chgt_etat;

	_cptr_ajouter_detecteur(capt, detecteur);
}

void cptr_ajbool_dtct_etat(int pin, bool val, void (*fct)(int, int))
{
	// Creation d'un capteur
	_cptr_def capt = { pin, LOGIQUE };

	// Creation du detecteur
	_cptr_detecteur* detecteur = (_cptr_detecteur*)malloc(sizeof(_cptr_detecteur));
	detecteur->param1 = val;
	detecteur->param2 = 0;
	detecteur->cible = fct;
	detecteur->analyse = &_cptr_dtctbool_dtct_etat;

	_cptr_ajouter_detecteur(capt, detecteur);
}

void cptr_ajanalog_chgt_val(int pin, void (*fct)(int, int))
{
	// Creation d'un capteur
	_cptr_def capt = { pin, ANALOGIQUE };

	// Creation du detecteur
	_cptr_detecteur* detecteur = (_cptr_detecteur*)malloc(sizeof(_cptr_detecteur));
	detecteur->param1 = 0;
	detecteur->param2 = 0;
	detecteur->cible = fct;
	detecteur->analyse = &_cptr_dtctanalog_chgt_val;

	_cptr_ajouter_detecteur(capt, detecteur);
}

void cptr_ajanalog_seuil(int pin, int val, void (*fct)(int, int))
{
	// Creation d'un capteur
	_cptr_def capt = { pin, ANALOGIQUE };

	// Creation du detecteur
	_cptr_detecteur* detecteur = (_cptr_detecteur*)malloc(sizeof(_cptr_detecteur));
	detecteur->param1 = val;
	detecteur->param2 = 0;
	detecteur->cible = fct;
	detecteur->analyse = &_cptr_dtctanalog_seuil;

	_cptr_ajouter_detecteur(capt, detecteur);
}

void cptr_ajanalog_dep_sup(int pin, int val, void (*fct)(int, int))
{
	// Creation d'un capteur
	_cptr_def capt = { pin, ANALOGIQUE };

	// Creation du detecteur
	_cptr_detecteur* detecteur = (_cptr_detecteur*)malloc(sizeof(_cptr_detecteur));
	detecteur->param1 = val;
	detecteur->param2 = 0;
	detecteur->cible = fct;
	detecteur->analyse = &_cptr_dtctanalog_dep_sup;

	_cptr_ajouter_detecteur(capt, detecteur);
}

void cptr_ajanalog_dep_inf(int pin, int val, void (*fct)(int, int))
{
	// Creation d'un capteur
	_cptr_def capt = { pin, ANALOGIQUE };

	// Creation du detecteur
	_cptr_detecteur* detecteur = (_cptr_detecteur*)malloc(sizeof(_cptr_detecteur));
	detecteur->param1 = val;
	detecteur->param2 = 0;
	detecteur->cible = fct;
	detecteur->analyse = &_cptr_dtctanalog_dep_inf;

	_cptr_ajouter_detecteur(capt, detecteur);
}

void cptr_ajanalog_entr_interv(int pin, int min, int max, void (*fct)(int, int))
{
	// Creation d'un capteur
	_cptr_def capt = { pin, ANALOGIQUE };

	// Creation du detecteur
	_cptr_detecteur* detecteur = (_cptr_detecteur*)malloc(sizeof(_cptr_detecteur));
	detecteur->param1 = min;
	detecteur->param2 = max;
	detecteur->cible = fct;
	detecteur->analyse = &_cptr_dtctanalog_entr_interv;

	_cptr_ajouter_detecteur(capt, detecteur);
}

void cptr_ajanalog_sort_interv(int pin, int min, int max, void (*fct)(int, int))
{
	// Creation d'un capteur
	_cptr_def capt = { pin, ANALOGIQUE };

	// Creation du detecteur
	_cptr_detecteur* detecteur = (_cptr_detecteur*)malloc(sizeof(_cptr_detecteur));
	detecteur->param1 = min;
	detecteur->param2 = max;
	detecteur->cible = fct;
	detecteur->analyse = &_cptr_dtctanalog_sort_interv;

	_cptr_ajouter_detecteur(capt, detecteur);
}

void cptr_ajanalog_nul(int pin, void (*fct)(int, int))
{
	// Creation d'un capteur
	_cptr_def capt = { pin, ANALOGIQUE };

	// Creation du detecteur
	_cptr_detecteur* detecteur = (_cptr_detecteur*)malloc(sizeof(_cptr_detecteur));
	detecteur->param1 = 0;
	detecteur->param2 = 0;
	detecteur->cible = fct;
	detecteur->analyse = &_cptr_dtctanalog_nul;

	_cptr_ajouter_detecteur(capt, detecteur);
}

void cptr_ajanalog_sat(int pin, void (*fct)(int, int))
{
	// Creation d'un capteur
	_cptr_def capt = { pin, ANALOGIQUE };

	// Creation du detecteur
	_cptr_detecteur* detecteur = (_cptr_detecteur*)malloc(sizeof(_cptr_detecteur));
	detecteur->param1 = 0;
	detecteur->param2 = 0;
	detecteur->cible = fct;
	detecteur->analyse = &_cptr_dtctanalog_sat;

	_cptr_ajouter_detecteur(capt, detecteur);
}

void cptr_ajautre_avanal(void (*fct)(int, int))
{
	l_ajouter(_cptr_av_analyse, fct);
}

void cptr_ajautre_apanal(void (*fct)(int, int))
{
	l_ajouter(_cptr_ap_analyse, fct);
}




bool _cptr_dtctbool_chgt_etat(int val, int prec, int a, int b)
{
	return val != prec;
}

bool _cptr_dtctbool_dtct_etat(int val, int prec, int etat, int a)
{
	return val != prec && val == a;
}

bool _cptr_dtctanalog_chgt_val(int val, int prec, int a, int b)
{
	return val != prec;
}

bool _cptr_dtctanalog_seuil(int val, int prec, int seuil, int a)
{
	return _cptr_dtctanalog_dep_sup(val, prec, seuil, 0) ||
		_cptr_dtctanalog_dep_inf(val, prec, seuil, 0);
}

bool _cptr_dtctanalog_dep_sup(int val, int prec, int seuil, int a)
{
	return val >= seuil && prec < seuil;
}

bool _cptr_dtctanalog_dep_inf(int val, int prec, int seuil, int a)
{
	return val < seuil && prec >= seuil;
}

bool _cptr_dtctanalog_entr_interv(int val, int prec, int inf, int sup)
{
	return _cptr_dtctanalog_dep_inf(val, prec, sup, 0) &&
		_cptr_dtctanalog_dep_sup(val, prec, inf, 0);
}

bool _cptr_dtctanalog_sort_interv(int val, int prec, int inf, int sup)
{
	return _cptr_dtctanalog_dep_inf(val, prec, inf, 0) ||
		_cptr_dtctanalog_dep_sup(val, prec, sup, 0);
}

bool _cptr_dtctanalog_nul(int val, int a, int b, int c)
{
	return val == 0;
}

bool _cptr_dtctanalog_sat(int val, int a, int b, int c)
{
	return val == 255;
}



void _cptr_appel(int it, void* l_val, void* args)
{
	void(*fct)(int, int) = l_val;
	fct(0, *(int*)args);
}

void _cptr_maj_capt(int it, void* l_val, void* args)
{
	_cptr_assoc* capt = (_cptr_assoc*)l_val;
	if(capt->capteur.type == LOGIQUE)
	{
		capt->valeurs.actuelle = capt->valeurs.precedente;
		capt->valeurs.actuelle = 0; // Remplacer par digitalread()
	}
	else
	{
		capt->valeurs.actuelle = capt->valeurs.precedente;
		capt->valeurs.actuelle = 0; // Remplacer par analogread()
	}
}

void _cptr_tests_capt(int it, void* l_val, void* args)
{
	_cptr_assoc* capt = (_cptr_assoc*)l_val;
	l_foreach(capt->detecteurs, &_cptr_lancer_detection, &(capt->valeurs));
}

void _cptr_lancer_detection(int it, void* l_val, void* args)
{
	_cptr_detecteur* detecteur = (_cptr_detecteur*)l_val;
	_cptr_valeurs* valeurs = (_cptr_valeurs*)args;

	if(detecteur->analyse(valeurs->actuelle, valeurs->precedente,
		detecteur->param1, detecteur->param2))
	{
		detecteur->cible(valeurs->actuelle, _cptr_horloge);
	}
}

int _cptr_hach_cptr_def(void* cle)
{
	return 2 * ((_cptr_def*)cle)->pin + ((_cptr_def*)cle)->type;
}

void _cptr_ajouter_detecteur(_cptr_def capt, _cptr_detecteur* detecteur)
{
	if(th_existe_h(_cptr_tab_capt, &capt))
	{
		// indice = valeur contenue dans la table a la cle (capt)
		int indice = *(int*)th_valeur_h(_cptr_tab_capt, &capt);
		// l_detect est le indice-eme element de _cptr_l
		Liste* l_detect = ((_cptr_assoc*)l_element_a(_cptr_l, indice))->detecteurs;
		l_ajouter(l_detect, detecteur);
	}
	else
	{
		// Le capteur n'est pas encore enregistre dans la liste
		// Il faut donc creer une association capteur-detecteurs
		// et l'ajouter a la liste, puis mettre son indice dans
		// la table
		_cptr_assoc* assoc = (_cptr_assoc*)malloc(sizeof(_cptr_assoc));
		assoc->capteur = capt;
		assoc->valeurs = (_cptr_valeurs){ 0, 0 };
		assoc->detecteurs = l_creer_args(1, detecteur);

		l_ajouter(_cptr_l, assoc);
		int *indice = (int*)malloc(sizeof(int));
		*indice = l_taille(_cptr_l) - 1; // Dernier element a taille-1
		th_ajouter_h(_cptr_tab_capt, &capt, indice);
	}
}

void _cptr_detruire_l_th(int it, void* l_val, void* args)
{
	_cptr_assoc* capt = (_cptr_assoc*)l_val;

	// Destruction de l'entier dans la table de hachage
	free((int*)th_valeur_h(_cptr_tab_capt, &(capt->capteur)));

	// Destruction de chaque detecteur associe au capteur
	l_foreach(capt->detecteurs, &_cptr_detruire_detect, NULL);

	// Destruction de l'association
	free(capt);
}

void _cptr_detruire_detect(int it, void* l_val, void* args)
{
	// Destruction du detcteur itere
	free((_cptr_detecteur*)l_val);
}