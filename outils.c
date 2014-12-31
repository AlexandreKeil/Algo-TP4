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

        while (c != EOF) //lecture du fichier jusqu'à sa fin
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
                    ligne++;
                    ordre=1;
                }

            i++;
            c= getc(fichier);
        }
        if (mot[0] != '\0')
                { NoeudABR* noeud = creer_noeud(mot, ligne, ordre, phrase);
        ajouter_noeud(arbre, noeud);
        nb_mots++;
                }

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
    printf("7- Reequilibrer l'arbre\n");
    printf("8- Quitter\n");
    printf("Votre choix ? ");

}




void menu()
{

int choix;
ArbreBR *a = 0;
char mot[30];

// AFFICHAGE DU MENU
    do
    {
        affichageMenu();

//CHOIX
        scanf("%d", &choix);

//TEST DES ERREURS POSSIBLES
        while(choix < 1 || choix > 8)
        {
            printf("Choix invalide.\n");
            scanf("%d", &choix);
            printf("\n\n");
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
                printf("Nous allons charger le fichier 'fichier.txt' présent dans le dossier courant dans l'ABR\n");
                printf("Vous pourrez changer son contenu si besoin \n");
                charger_fichier(a,"fichier.txt");
            }
            break;

        case 3: //CARACTERISTIQUES DE L'ABR
            if (a == NULL)
                printf("Veuillez d'abord creer un ABR (choix numero 1 du menu) et charger un fichier dans cet arbre (choix 2)\n\n");
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
                printf("Veuillez d'abord creer un ABR (choix numero 1 du menu) et charger un fichier dans cet arbre (choix 2)\n\n");
            else if (a->racine == NULL)
                printf("L'arbre est vide\n");
            else
                afficher_arbre(*a);
            break;

        case 5: // RECHERCHE D'UN MOT
            if (a == NULL)
                printf("Veuillez d'abord creer un ABR (choix numero 1 du menu) et charger un fichier dans cet arbre (choix 2)\n\n");
            else
            {
                printf("Veuillez rentrer le mot que vous recherchez (un seul mot sans espace): \n");
                scanf("%s", &mot);

                printf("\nVous avez rentre : %s\n", mot);
                rechercher_noeud(a, mot);
            }
            break;

        case 7: // REEQUILIBRE DE L'ARBRE
                ///NE FONCTIONNE PÄS
             if (a == NULL)
                printf("Veuillez d'abord creer un ABR (choix numero 1 du menu) et charger un fichier dans cet arbre (choix 2)\n\n");
             else
             {
                ArbreBR* a_eq = creer_abr();
                afficher_arbre(*a_eq);
                reequilibre_tous(a, a_eq);
                /* if (a_eq == NULL)
                printf("Veuillez d'abord creer un ABR (choix numero 1 du menu) et charger un fichier dans cet arbre (choix 2)\n\n");
                else
                {
                printf("Voici les caracteristiques de l'ABR cree \n");
                printf("Nombre de noeuds : %d\n", a_eq->nb_mots_differents);
                printf("Profondeur : %d\n", profondeur(a_eq));
                if (is_equilibre(a_eq) == 1)
                    printf("L'ABR est equilibre\n");
                else printf("L'ABR n'est pas equilibre\n");
                }*/

                a= a_eq;
                printf("L'arbre a ete reequilibre\n");
             }


        break;
/*
        case 6: // RECHERCHE D'UNE PHRASE
            /*
        Recuper les deux mots

        Noeaud x = rechercher_noeud(1er mot)

        Noeud y = rechercher_noeud (2eme mot)

        Traiter les positions des noeuds récupérer, voir si les deux mot sont dans une ou plusieurs même phrase


           break;

        case 7:
            liberer_arbre(a); ///fonction a creer, suprimer les noeuds de chaque arbre
                                /// (appel recursif de la fonction en supprimant les ss arbre droit et gauche ?)

  */

        } //switch

}
    while (choix !=8);

    return;


}



