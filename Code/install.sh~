#!/bin/bash

echo -e "Installation du répertoire FAR\n"

echo -n "Identifiant GitHub : "
read id_git
echo -n "Mail utilisé pour GitHub : "
read mail_git

mkdir FAR
cd FAR
git init
git remote add origin https://www.github.com/FlorentBerland/FAR.git
git pull origin master

git config --global user.name $id_git
git config user.name $id_git
git config --global user.email $mail_git
git config user.email $mail_git

echo -en "\e[1;33m
	__          ___               _       
	\ \        / / |             | |      
	 \ \  /\  / /| |__   ___  ___| |_   _ 
	  \ \/  \/ / | '_ \ / _ \/ _ \ | | | |
	   \  /\  /  | | | |  __/  __/ | |_| |
	    \/  \/   |_| |_|\___|\___|_|\__, |
	                                 __/ |
	                                |___/ \e[0;34m

	Prêt à fonctionner !
\e[0m
> tapez 'cd FAR/Code && make download' pour terminer l'installation

"
