#FAR

Par : Thais AURARD, Florent BERLAND, Mahe SPAENLE

Démarrer le programme :
	installation :
		wget https://raw.githubusercontent.com/FlorentBerland/FAR/master/Code/install.sh
		chmod u+x install.sh
		./install.sh (entrer les identifiants github pour configurer le dépôt)
		cd FAR/Code/
		make download

	lancer le programme :
		se placer dans FAR/Code
		sudo make start
	
Ce qui fonctionne :
- Les déplacements
- Recalage selon la position fournie par le serveur de positions

Ce qui ne fonctionne pas :
- Détecter le début et la fin de la partie
- Poster l'ip sur Beebotte et récupérer les ip des participants
- Eviter les obstacles
- Adopter une stratégie défensive
- Fonctionner en wifi
- interactions avec le validateur de but

Particularités :
- Un paquet de bibliothèques faites à la main au cas où, mais inutilisées
- Un robot virtuel tourne en parallèle pour calculer les trajectoires (dans driver_ctrl.c)
- Le robot s'appelle Wheely
