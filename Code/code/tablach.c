#include "../headers/tablach.h"

Tablach* th_creer(int (*fct_hach)(void*))
{
	Tablach* retour = (Tablach*)malloc(sizeof(Tablach));
	retour->taille_tab = _TH_TAILLE_INIT;
	retour->tab = (_th_alv**)calloc(_TH_TAILLE_INIT, sizeof(_th_alv*));
	retour->nb_elt = 0;
	
	retour->fct_hach = (fct_hach!=NULL) ? fct_hach : &_th_fct_hach;

	return retour;
}

void th_detruire(Tablach* t)
{
	th_vider(t);
	free(t->tab);
	free(t);
}

void th_vider(Tablach* t)
{
	int i = 0;
	for(; i<t->taille_tab; i++)
	{
		if(t->tab[i] != NULL)
		{
			free(t->tab[i]);
			t->tab[i] = NULL;
		}
	}
	free(t->tab);
	t->tab = (_th_alv**)calloc(_TH_TAILLE_INIT, sizeof(_th_alv*));
	t->taille_tab = _TH_TAILLE_INIT;
	t->nb_elt = 0;
}

void th_ajouter(Tablach* t, int cle, void* elt)
{
	int pos = _th_hachage(t, cle);
	int col = pos;
	while(t->tab[pos] != NULL)
	{
		if(t->tab[pos]->col == col)
		{
			col = pos;
		}
		pos = _th_sondage(t, pos);
	}
	_th_alv* alv = (_th_alv*)malloc(sizeof(_th_alv));
	alv->valeur = elt;
	alv->cle = (int*)malloc(sizeof(int));
	*((int*)alv->cle) = cle;
	alv->col = col;

	t->tab[pos] = alv;
	t->nb_elt++;

	if(_TH_DENSITE(t)>_TH_DENSITE_MAX)
	{
		_th_agrandir(t);
	}
}

void th_ajouter_h(Tablach* t, void* cle, void* elt)
{
	int pos = _th_hachage(t, t->fct_hach(cle));
	int col = pos;
	while(t->tab[pos] != NULL)
	{
		if(t->tab[pos]->col == col)
		{
			col = pos;
		}
		pos = _th_sondage(t, pos);
	}
	_th_alv* alv = (_th_alv*)malloc(sizeof(_th_alv));
	alv->valeur = elt;
	alv->cle = cle;
	alv->col = col;

	t->tab[pos] = alv;
	t->nb_elt++;

	if(_TH_DENSITE(t)>_TH_DENSITE_MAX)
	{
		_th_agrandir(t);
	}
}

void th_modifier(Tablach* t, int cle, void* elt)
{
	int pos = _th_atteindre(t, cle);
	if(t->tab[pos]!=NULL)
	{
		t->tab[pos]->valeur = elt;
	}
}

void th_modifier_h(Tablach* t, void* cle, void* elt)
{
	int pos = _th_atteindre_h(t, cle);
	if(t->tab[pos]!=NULL)
	{
		t->tab[pos]->valeur = elt;
	}
}

void th_supprimer(Tablach* t, int cle)
{
	int pos = _th_atteindre(t, cle);
	if(t->tab[pos] != NULL)
	{
		free(t->tab[pos]);
		t->tab[pos] = NULL;
	}
	int suiv = _th_sondage(t, pos);
	int mem_col = pos;
	do
	{
		/*
			Cas possibles :
			1) suiv est NULL : fin (rien a faire)
			2) suiv non collisionne : rien a faire
			3) suiv est collisionne avec NULL : deplacer suiv sur sa case de collision
				et permuter la memoire de collision avec suiv->col
			- suiv n'est pas collisionne avec NULL :
				4) pos est NULL : pos prend la valeur de suiv
				5) pos n'est pas NULL : rien a faire
		*/
		if(t->tab[suiv]!=NULL && t->tab[suiv]->col!=suiv)
		{
			if(t->tab[t->tab[suiv]->col] == NULL) // 3)
			{
				t->tab[t->tab[suiv]->col] = t->tab[suiv];
				int temp = mem_col;
				mem_col = t->tab[suiv]->col;
				t->tab[suiv]->col = temp;
				t->tab[suiv] = NULL;
			}
			else if (t->tab[pos] == NULL) // 4)
			{
				t->tab[pos] = t->tab[suiv];
				t->tab[suiv] = NULL;
			}
			// else : 5)
		}
		// else : 1) et 2)
		pos = suiv;
		suiv = _th_sondage(t, suiv);
	} while(t->tab[suiv] != NULL);

	if(_TH_DENSITE(t)<_TH_DENSITE_MIN)
	{
		_th_retrecir(t);
	}
}

void th_supprimer_h(Tablach* t, void* cle)
{
	int pos = _th_atteindre_h(t, cle);
	if(t->tab[pos] != NULL)
	{
		free(t->tab[pos]);
		t->tab[pos] = NULL;
	}
	int suiv = _th_sondage(t, pos);
	int mem_col = pos;
	do
	{
		/*
			Cas possibles :
			1) suiv est NULL : fin (rien a faire)
			2) suiv non collisionne : rien a faire
			3) suiv est collisionne avec NULL : deplacer suiv sur sa case de collision
				et permuter la memoire de collision avec suiv->col
			- suiv n'est pas collisionne avec NULL :
				4) pos est NULL : pos prend la valeur de suiv
				5) pos n'est pas NULL : rien a faire
		*/
		if(t->tab[suiv]!=NULL && t->tab[suiv]->col!=suiv)
		{
			if(t->tab[t->tab[suiv]->col] == NULL) // 3)
			{
				t->tab[t->tab[suiv]->col] = t->tab[suiv];
				int temp = mem_col;
				mem_col = t->tab[suiv]->col;
				t->tab[suiv]->col = temp;
				t->tab[suiv] = NULL;
			}
			else if (t->tab[pos] == NULL) // 4)
			{
				t->tab[pos] = t->tab[suiv];
				t->tab[suiv] = NULL;
			}
			// else : 5)
		}
		// else : 1) et 2)
		pos = suiv;
		suiv = _th_sondage(t, suiv);
	} while(t->tab[suiv] != NULL);

	if(_TH_DENSITE(t)<_TH_DENSITE_MIN)
	{
		_th_retrecir(t);
	}
}

void* th_valeur(Tablach *t, int cle)
{
	int pos = _th_atteindre(t, cle);
	if(t->tab[pos] == NULL)
	{
		return NULL;
	}
	else
	{
		return t->tab[pos]->valeur;
	}
}

void* th_valeur_h(Tablach *t, void *cle)
{
	int pos = _th_atteindre_h(t, cle);
	if(t->tab[pos] == NULL)
	{
		return NULL;
	}
	else
	{
		return t->tab[pos]->valeur;
	}
}

bool th_existe(Tablach* t, int cle)
{
	int pos = _th_atteindre(t, cle);
	return t->tab[pos] != NULL;
}

bool th_existe_h(Tablach* t, void* cle)
{
	int pos = _th_atteindre_h(t, cle);
	return t->tab[pos] != NULL;
}

bool th_contient(Tablach* t, void* elt)
{
	bool retour = false;
	int i = 0;
	for(; i<t->taille_tab; i++)
	{
		if(t->tab[i] != NULL || t->tab[i]->valeur == elt)
		{
			retour = true;
		}
	}
	return retour;
}

int th_taille(Tablach* t)
{
	return t->nb_elt;
}

int _th_hachage(Tablach* t, int i)
{
	i %= t->taille_tab;
	if(i < 0) i += t->taille_tab;
	return i;
}

int _th_sondage(Tablach* t, int i)
{
	return _th_hachage(t, i+1);
}

void _th_agrandir(Tablach* t)
{
	_th_alv** sauv = t->tab;
	int taille_sauv = t->taille_tab;

	t->taille_tab *= _TH_COEF_AGRANDISSEMENT;
	t->tab = (_th_alv**)calloc(t->taille_tab, sizeof(_th_alv*));
	t->nb_elt = 0;

	int i = 0;
	for(; i<taille_sauv; i++)
	{
		if(sauv[i] != NULL)
		{
			if(t->fct_hach == NULL)
			{
				th_ajouter(t, *(int*)sauv[i]->cle, sauv[i]->valeur);
			}
			else
			{
				th_ajouter_h(t, sauv[i]->cle, sauv[i]->valeur);
			}
			free(sauv[i]);
		}
	}
	free(sauv);
}

void _th_retrecir(Tablach* t)
{
	_th_alv** sauv = t->tab;
	int taille_sauv = t->taille_tab;

	t->taille_tab /= _TH_COEF_AGRANDISSEMENT;
	t->tab = (_th_alv**)calloc(t->taille_tab, sizeof(_th_alv*));
	t->nb_elt = 0;

	int i = 0;
	for(; i<taille_sauv; i++)
	{
		if(sauv[i] != NULL)
		{
			if(t->fct_hach == NULL)
			{
				th_ajouter(t, *(int*)sauv[i]->cle, sauv[i]->valeur);
			}
			else
			{
				th_ajouter_h(t, sauv[i]->cle, sauv[i]->valeur);
			}
			free(sauv[i]);
		}
	}
	free(sauv);
}

int _th_atteindre(Tablach* t, int cle)
{
	int pos = _th_hachage(t, cle);
	while(t->tab[pos]!=NULL && *((int*)t->tab[pos]->cle)!=cle)
	{
		pos = _th_sondage(t, pos);
	}
	return pos;
}

int _th_atteindre_h(Tablach* t, void* cle)
{
	int pos = _th_hachage(t, t->fct_hach(cle));
	while(t->tab[pos]!=NULL && t->fct_hach(t->tab[pos]->cle)!=t->fct_hach(cle))
	{
		pos = _th_sondage(t, pos);
	}
	return pos;
}

int _th_fct_hach(void* cle)
{
	return (int)(long)cle;
}
