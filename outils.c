#include "outils.h"
#define MAX_LIGNE 500

int charger_fichier(ArbreBR *arbre, char *filename){ //INCOMPLET LULZ
    FILE* fichier= fopen(filename, "r");
    if (fichier == NULL){
        printf("Erreur ouverture du fichier\n");
        return -1;
    }
    else {

        char buff[MAX_LIGNE] = "";
        while (fgets(buff, MAX_LIGNE, fichier) != NULL) //lecture du fichier jusqu'à sa fin
        {
            /**
            opérations sur buff, qui contiendra chaque mot
            */
        }
        fclose(fichier);
    }
}

void affichageMenu(){
    printf("MENU\n");
    printf("1- Creer un ABR\n");
    printf("2- Charger un fichier dans l'ABR\n");
    printf("3- Caracteristiques de l'ABR\n");
    printf("4- Afficher tous les mots distincts par ordre alphabetique\n");
    printf("5- Rechercher un mot\n");
    printf("6- Afficher les phrases contenant 2 mots\n");
    printf("7- Quitter\n");
    printf("Votre choix ? ");
}
