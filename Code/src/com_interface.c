#include <stdarg.h>
#include "../headers/com_interface.h"

int cint_init(char id, int port, void(*f0)(double, double, double),
	void(*f1)(char, char *), void(*f2)(char, int))
{
	_cint_fonctions_cibles = calloc(PAS_DE_DONNEES, sizeof(void*));
	_cint_fonctions_cibles[0] = f0;
	_cint_fonctions_cibles[1] = f1;
	_cint_fonctions_cibles[2] = f2;

	_cint_port = port;

	int i=0;
	while(i!=PAS_DE_DONNEES && _cint_fonctions_cibles[i]!=NULL)
	{
		i++;
	}
	if(i != PAS_DE_DONNEES)
	{
		return 1;
	}
	else
	{
		return com_init(id, port, &_cint_traiter_reception);
	}
}

int cint_demarrer()
{
	return com_demarrer();
}

int cint_arret()
{
	return com_arret();
}

int cint_envoyer(char* ip, cint_type_transfert type, ...)
{
	_cint_donnees_brutes donnees;
	donnees.id_robot = _cint_id_robot;
	donnees.type = type;

	va_list ap;
	va_start(ap, type);
	_cint_cast_donnees casteur;
	switch(type)
	{
		case POSITION:
		{
			casteur.d = va_arg(ap, double);
			donnees.donnees[0] = casteur.octets;
			casteur.d = va_arg(ap, double);
			donnees.donnees[1] = casteur.octets;
			casteur.d = va_arg(ap, double);
			donnees.donnees[2] = casteur.octets;
			break;
		}
		case TEXTE:
		{
			// Recuperation et serialisation de la taille du texte
			char taille = va_arg(ap, char);
			casteur.c = taille
			donnees.donnees[0] = casteur.octets;

			// Découpage du texte en troncons de 8 octets
			char texte[taille] = va_arg(ap, char[taille]);
			char troncon[CINT_TAILLE_TYPE_INTEGRAL];

			char i = 0;
			while(i!=taille && texte[i]!='\0')
			{
				// Copie du i-eme caractere dans le troncon
				troncon[i%CINT_TAILLE_TYPE_INTEGRAL] = texte[i];

				if(i == CINT_TAILLE_TYPE_INTEGRAL)
				{	
					// Si le troncon est rempli, il est serialise
					casteur.chaine = troncon;
					donnees[i/CINT_TAILLE_TYPE_INTEGRAL] = casteur.octets;
				}
				i++;
			}
			break;
		}
		case VRAC:
		{
			casteur.c = va_arg(ap, char);
			donnees.donnees[0] = casteur.octets;
			casteur.i = va_arg(ap, int);
			donnees.donnees[1] = casteur.octets;
			break;
		}
		case PAS_DE_DONNEES: default:
		{
			break;
		}
	}
	va_end(ap);

	_cint_cast_envoi casteur_envoi;
	casteur_envoi.donnees = donnees;

	com_envoyer(ip, casteur_envoi.octets);
}