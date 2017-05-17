#include <stdarg.h>
#include "../headers/com_interface.h"

int cint_init(char id, int port, void(*f0)(char, double, double, double),
	void(*f1)(char, char, char *), void(*f2)(char, char, int))
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
		return com_init(port, &_cint_traiter_reception);
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
			_cint_copier_tableau(&donnees.donnees[0], &casteur.octets, CINT_TAILLE_TYPE_INTEGRAL);
			casteur.d = va_arg(ap, double);
			_cint_copier_tableau(&donnees.donnees[1], &casteur.octets, CINT_TAILLE_TYPE_INTEGRAL);
			casteur.d = va_arg(ap, double);
			_cint_copier_tableau(&donnees.donnees[2], &casteur.octets, CINT_TAILLE_TYPE_INTEGRAL);
			break;
		}
		case TEXTE:
		{
			// Recuperation et serialisation de la taille du texte
			char taille = va_arg(ap, char);
			casteur.c = taille;
			_cint_copier_tableau(&donnees.donnees[0], &casteur.octets, CINT_TAILLE_TYPE_INTEGRAL);

			// Découpage du texte en troncons de 8 octets
			char *texte = va_arg(ap, char[taille]);
			char troncon[CINT_TAILLE_TYPE_INTEGRAL];

			int i = 0;
			while(i!=taille && i<CINT_TAILLE_BUFFER_DONNEES-CINT_TAILLE_TYPE_INTEGRAL)
			{
				// Copie du i-eme caractere dans le troncon
				troncon[i%CINT_TAILLE_TYPE_INTEGRAL] = texte[i];

				if(i%CINT_TAILLE_TYPE_INTEGRAL == CINT_TAILLE_TYPE_INTEGRAL-1)
				{	
					// Si le troncon est rempli, il est serialise
					_cint_copier_tableau(&casteur.chaine, &troncon, CINT_TAILLE_TYPE_INTEGRAL);
					_cint_copier_tableau(&donnees.donnees[i/CINT_TAILLE_TYPE_INTEGRAL+1], &casteur.octets, CINT_TAILLE_TYPE_INTEGRAL);
				}
				i++;
			}
			break;
		}
		case VRAC:
		{
			casteur.c = va_arg(ap, char);
			_cint_copier_tableau(&donnees.donnees[0], &casteur.octets, CINT_TAILLE_TYPE_INTEGRAL);
			casteur.i = va_arg(ap, int);
			_cint_copier_tableau(&donnees.donnees[1], &casteur.octets, CINT_TAILLE_TYPE_INTEGRAL);
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

void _cint_traiter_reception(char* octets)
{
	_cint_cast_envoi casteur_envoi;
	_cint_copier_tableau(&casteur_envoi.octets, &octets, CINT_TAILLE_BUFFER_DONNEES);
	_cint_donnees_brutes donnees = casteur_envoi.donnees;

	_cint_cast_donnees casteur;
	switch(donnees.type)
	{
		case POSITION:
		{
			void(*fct)(char, double, double, double) = _cint_fonctions_cibles[POSITION];
			_cint_copier_tableau(&casteur.octets, &donnees.donnees[0], CINT_TAILLE_TYPE_INTEGRAL);
			double x = casteur.d;
			_cint_copier_tableau(&casteur.octets, &donnees.donnees[1], CINT_TAILLE_TYPE_INTEGRAL);
			double y = casteur.d;
			_cint_copier_tableau(&casteur.octets, &donnees.donnees[2], CINT_TAILLE_TYPE_INTEGRAL);
			double theta = casteur.d;
			fct(donnees.id_robot, x, y, theta);
			break;
		}
		case TEXTE:
		{
			void(*fct)(char, char, char*) = _cint_fonctions_cibles[TEXTE];
			_cint_copier_tableau(&casteur.octets, &donnees.donnees[0], CINT_TAILLE_TYPE_INTEGRAL);
			char taille = casteur.c;
			char texte[taille];
			char troncon[CINT_TAILLE_TYPE_INTEGRAL];
			int i=0;
			// i+1 car le premier indice des donnees contient la taille
			while(i+1<CINT_TAILLE_BUFFER_DONNEES/CINT_TAILLE_TYPE_INTEGRAL)
			{
				_cint_copier_tableau(&casteur.octets, &donnees.donnees[i+1], CINT_TAILLE_TYPE_INTEGRAL);
				_cint_copier_tableau(&troncon, &casteur.chaine, CINT_TAILLE_TYPE_INTEGRAL);				
				int j;
				for(j=0;j<CINT_TAILLE_TYPE_INTEGRAL;j++)
				{
					texte[CINT_TAILLE_TYPE_INTEGRAL*i + j] = troncon[j];
				}
			}
			fct(donnees.id_robot, taille, texte);
			break;
		}
		case VRAC:
		{
			void(*fct)(char, char, int) = _cint_fonctions_cibles[VRAC];
			_cint_copier_tableau(&casteur.octets, &donnees.donnees[0], CINT_TAILLE_TYPE_INTEGRAL);
			char arg1 = casteur.c;
			_cint_copier_tableau(&casteur.octets, &donnees.donnees[1], CINT_TAILLE_TYPE_INTEGRAL);
			int arg2 = casteur.i;
			fct(donnees.id_robot, arg1, arg2);
			break;
		}
		case PAS_DE_DONNEES: default:
		{
			break;
		}
	}
}

void _cint_copier_tableau(char* c1, char* c2, int taille)
{
	if(c1 != NULL && c2 != NULL);
	int i=0;
	for(;i<taille;i++)
	{
		c1[i] = c2[i];
	}
}