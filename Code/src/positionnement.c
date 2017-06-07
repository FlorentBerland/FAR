#include "../headers/positionnement.h"

float PositionX(){
  // Recherche dans le fichier position les dernieres positions données par le serveur de position
  FILE *para = fopen("bin/data/verifiedPosition.txt","r");

  if(para != NULL){
    char ligne[7];
    fgets(ligne, sizeof ligne, para);
    fclose(para);

    char var;
    var=ligne[0];
    int x=var-'0';
    float fX=(float)x;
    return fX;
  }
  else
  {
    printf("Erreur d'ouverture du fichier\n");
    return 0.;
  }
}

float PositionY(){
  // Recherche dans le fichier position les dernieres positions données par le serveur de position
  FILE *para = fopen("bin/data/position.txt","r");

  if(para != NULL){
    char ligne[7];
    fgets(ligne, sizeof ligne, para);
    fclose(para);

    char var2[2];
    if(ligne[3]=='_'){
      var2[0]=0;
      var2[1]=ligne[2];
    }
    else{
      var2[0]=ligne[2];
      var2[1]=ligne[3];
    }
    int a=(var2[0]-'0')*10;
    int b=var2[1]-'0';
    int y=a+b;
    float fY=(float)y;
    return fY;
  }
  else
  {
    printf("Erreur d'ouverture du fichier\n");
    return 0.;
  }
}
