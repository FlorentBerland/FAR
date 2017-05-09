#include "../headers/liste.h"

Liste* l_creer()
{
	Liste *retour = (Liste*)malloc(sizeof(Liste));
	retour->taille = 0;
	retour->prec = retour;
	retour->suiv = retour;
	retour->est_tete = true;
	return retour;
}

Liste* l_creer_args(int taille, ...)
{
	Liste* retour = l_creer();

	va_list ap;
	va_start(ap, taille);

	int i = 0;
	for(; i < taille; i++)
	{
		l_ajouter(retour, va_arg(ap, void *));
	}

	va_end(ap);

	return retour;
}

Liste* l_copier(Liste* l)
{
	Liste *retour = l_creer();
	l_foreach(l, &_l_ajout_it, retour);
	return retour;
}

void l_detruire(Liste* l)
{
	l_vider(l);
	free(l);
}

void l_ajouter(Liste *l, void *t)
{
	_l_contenu *nouv = (_l_contenu*)malloc(sizeof(_l_contenu));
	nouv->valeur = t;
	nouv->est_tete = false;
	nouv->prec = l->prec;
	nouv->suiv = l;
	((Liste*)nouv->prec)->suiv = nouv;
	((Liste*)nouv->suiv)->prec = nouv;
	l->taille++;
}

void l_inserer(Liste *l, int pos, void *t)
{
	void *cible = _l_pointer(l, pos);
	// La case cible devient suivante de celle inseree
	_l_contenu *nouv = (_l_contenu*)malloc(sizeof(_l_contenu));
	nouv->valeur = t;
	nouv->est_tete = false;
	nouv->prec = ((Liste*)cible)->prec;
	nouv->suiv = cible;
	((_l_contenu*)nouv->prec)->suiv = nouv;
	((_l_contenu*)nouv->suiv)->prec = nouv;
	l->taille++;
}

void l_supprimer(Liste *l, int pos)
{
	void *cible = _l_pointer(l, pos);
	((Liste*)((Liste*)cible)->prec)->suiv = ((Liste*)cible)->suiv;
	((Liste*)((Liste*)cible)->suiv)->prec = ((Liste*)cible)->prec;
	free(cible);
	cible = NULL;
	l->taille--;
}

void l_modifier(Liste *l, int pos, void *elt)
{
	void *cible = _l_pointer(l, pos);
	((_l_contenu*)cible)->valeur = elt;
}

void* l_element_a(Liste *l, int pos)
{
	void *cible = _l_pointer(l, pos);
	return ((_l_contenu*)cible)->valeur;
}

void l_vider(Liste *l)
{
	while(l->taille != 0)
	{
		l_supprimer(l, 0);
	}
}

void l_inverser(Liste *l)
{
	void *cible = l;
	do
	{
		void *temp = ((_l_contenu*)cible)->suiv;
		((_l_contenu*)cible)->suiv = ((_l_contenu*)cible)->prec;
		((_l_contenu*)cible)->prec = temp;
		cible = ((_l_contenu*)cible)->prec;
	}while(!_l_est_tete(cible));
}

int l_taille(Liste *l)
{
	return l->taille;
}

void l_foreach(Liste *l, void (*fct)(int, void*, void*), void* args)
{
	int position = 0;
	void *cible = l->suiv;
	while(!_l_est_tete(cible))
	{
		fct(position, ((_l_contenu*)cible)->valeur, args);
		cible = ((_l_contenu*)cible)->suiv;
		position++;
	}
}

bool _l_est_tete(void *l)
{
	if(l!=NULL)
	{
		return ((Liste*)l)->est_tete;
	}
	return false;
}

void* _l_pointer(Liste *l, int pos)
{
	if(pos < l->taille/2)
	{
		return _l_pointer_av(((_l_contenu*)l->suiv), pos);
	}
	else
	{
		return _l_pointer_ar(((_l_contenu*)l->prec), l->taille-pos-1);
	}
}

void* _l_pointer_av(_l_contenu *l, int pos)
{
	if(pos == 0)
	{
		return l;
	}
	else
	{
		return _l_pointer_av(((_l_contenu*)l->suiv), pos - 1);
	}
}

void* _l_pointer_ar(_l_contenu *l, int pos)
{
	if(pos == 0)
	{
		return l;
	}
	else
	{
		return _l_pointer_ar(((_l_contenu*)l->prec), pos - 1);
	}
}

void _l_ajout_it(int i, void *elt, void *args)
{
	l_ajouter(((Liste*)args), elt);
}
