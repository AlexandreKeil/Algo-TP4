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
        while (fgets(buff, MAX_LIGNE, fichier) != NULL) //lecture du fichier jusqu'� sa fin
        {

        }
        fclose(fichier);
    }
}
*/
int max(int a, int b)
{
    return (a + b + fabs(a-b) ) / 2;
}

int min(int a,int b)
{
    return (a + b - fabs(a-b) ) / 2;
}

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
        int ordre = 1;
        char mot[30];
        int j;
        for (j=0; j<30; j++)
            mot[j] = '\0';
        int i = 0;
        char c = getc(fichier);

        while (c != EOF) //lecture du fichier jusqu'� sa fin
        {


            if (c == ' ' || c == '.' || c == '\n')
                {
                if (mot[0] != '\0')
                    {
                    NoeudABR* noeud = creer_noeud(mot, ligne, ordre, phrase);
                    ajouter_noeud(arbre, noeud);
                    ordre++;
                    for (j=0; j<30; j++)
                        mot[j] = '\0';

                    nb_mots++;
                    }
                i=-1;
                }

            else mot[i] = c;

            if (c == '.')
                phrase++;

            else if (c == '\n')
                {
                    phrase++;
                    ordre=1;
                }

            i++;
            c= getc(fichier);
        }
        NoeudABR* noeud = creer_noeud(mot, ligne, ordre, phrase);
        ajouter_noeud(arbre, noeud);
        nb_mots++;

        fclose(fichier);
    }
    return nb_mots;
}

void affichageMenu(){
    printf("\n");
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




void menu()
{

int choix;
ArbreBR *a = 0;


// AFFICHAGE DU MENU
    do
    {
        affichageMenu();

//CHOIX
        scanf("%d", &choix);

//TEST DES ERREURS POSSIBLES
        while(choix < 1 || choix > 7)
        {
            printf("Choix invalide.\n");
            scanf("%d", &choix);
        }


        /** ACTIONS SELON CHOIX*/
        switch(choix)
        {
// CREATION D'UN ABR
        case 1:
            a = creer_abr();
            printf("L'arbre a ete cree\n");
            break;

//CHARGMENT D'UN FICHIER DANS L'ABR
        case 2:
            if (a == NULL)
                printf("Veuillez d'abord creer un ABR (choix numero 1 du menu)\n\n");
            else
            {
                printf("Nous allons charger le fichier 'fichier.txt' pr�sent dans le dossier courant dans l'ABR\n");
                printf("Vous pourrez changer son contenu si besoin \n");
                charger_fichier(a,"fichier.txt");
            }
            break;

        case 3: //CARACTERISTIQUES DE L'ABR
            if (a == NULL)
                printf("Veuillez d'abord creer un ABR (choix numero 1 du menu)\n\n");
            else
            {
                printf("Voici les caracteristiques de l'ABR cree \n");
                printf("Nombre de noeuds : %d\n", a->nb_mots_differents);
                printf("Profondeur : %d\n", profondeur(a));
                if (is_equilibre(a) == 1)
                    printf("L'ABR est equilibre\n");
                else printf("L'ABR n'est pas equilibre\n");
            }
            break;

        case 4 : // AFFICHER LES MOTS DISTINCTS
            if (a == NULL)
                printf("Veuillez d'abord creer un ABR (choix numero 1 du menu)\n\n");
            else if (a->racine == NULL)
                printf("L'arbre est vide\n");
            else
                afficher_arbre(*a);
            break;

        } //switch

}
    while (choix !=7);

    return;


}



