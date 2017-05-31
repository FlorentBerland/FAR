#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

float PositionX(){
  // Recherche dans le fichier position les dernieres positions données par le serveur de position
  FILE *para = fopen("position.txt","r");

  if(para != NULL){
    char ligne[7];
    fgets(ligne, sizeof ligne, para);
    fclose(para);

    char var;
    var=ligne[0];
    int x=var-'0';
    float fX=(float)x;
    printf("x: %f\n", fX);
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
  FILE *para = fopen("position.txt","r");

  if(para != NULL){
    char ligne[7];
    fgets(ligne, sizeof ligne, para);
    fclose(para);

    char var2[2];
    if(ligne[3]=='\n'){
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
    printf("y: %f\n", fY);
    return fY;
  }
  else
  {
    printf("Erreur d'ouverture du fichier\n");
    return 0.;
  }
}

int main(){
  bool partie = 1;
  float x;
  float y;
  while(partie){
    x=PositionX();
    y=PositionY();
    sleep(2);
  }
  return 0;
}
