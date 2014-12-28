#include "outils.h"
#define MAX_CHAR 50

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

int charger_fichier(ArbreBR *arbre, char *filename){
    FILE* fichier= fopen(filename, "r"); // pointeur sur le fichier ouvert
    char c;
    int nb_mots = 0;
    if (fichier == NULL){
        printf("Erreur d'ouverture du fichier\n");
        return -1;
    }
    else {
        int phrase = 1;
        int ligne = 1;

        char c = getc(fichier);

        while (c != EOF) //lecture du fichier jusqu'à sa fin
        {
           int ordre = 1;
            while (c != '\n' && c != EOF ) // Boucle pour les lignes
                {
                    char mot[30] = "";
                    int i = 0;
                    while ( c != ' ' && c != '.' && c != EOF && c != '\n')
                        {
                            mot[i] = c;
                            i++;
                            c = getc(fichier);
                        }
                    if (c == '.')
                        phrase++;

                    NoeudABR* noeud = creer_noeud(mot, ligne, ordre, phrase);
                    ajouter_noeud(arbre, noeud);
                    ordre++;
                    nb_mots++;
                    if (c != EOF)  // sinon on ne s'arrête jamais
                        c = getc(fichier);
                }
        ligne++;
        if (c != EOF)
            c= getc(fichier);
        }
        fclose(fichier);
    }
    return nb_mots;
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
