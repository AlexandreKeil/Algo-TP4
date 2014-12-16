#include "outils.h"
#define MAX_CHAR 500

/*
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

        }
        fclose(fichier);
    }
}
*/

int charger_fichier(ArbreBR *arbre, char *filename){ //INCOMPLET LULZ
    FILE* fichier= fopen(filename, "r");
    char c;
    if (fichier == NULL){
        printf("Erreur ouverture du fichier\n");
        return -1;
    }
    else {
        char buff[MAX_CHAR];
        int i = 0;
        int phrase = 1;
        int ligne = 0;
        while (fgets(buff, MAX_CHAR, fichier) != NULL) //lecture du fichier jusqu'à sa fin
        {
            ligne++;
            while (buff[i] != '\n') ///Ajouter le cas d'un surplus ?
                {
                    int ordre = 0;
                    char mot[30] = "";
                    int j = 0;
                    ordre++;
                    while (buff[i] != ' ' && buff[i] != '.' )
                        {

                            mot[j] = buff[i];
                            ordre++;
                            j++;
                            i++;
                        }
                    NoeudABR* noeud = creer_noeud(mot, ligne, ordre, phrase);
                    ajouter_noeud(arbre, noeud);
                }
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
