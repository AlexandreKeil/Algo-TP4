#include "arbre.h"
#include "liste.h"
#include "outils.h"
#define TAILLE_NOM_FICHIER 50

int main()
{
    ArbreBR *a;
    char nomFichier[TAILLE_NOM_FICHIER];


    printf("Arbres binaires de recherche - Indexation d'un texte\n");
    affichageMenu();
    int choixUser;
    scanf("%d", &choixUser);
    do
    {
        printf("Choix invalide\nVotre choix ? ");
        scanf("%d", &choixUser);
    }
    while (choixUser < 1 || choixUser > 7);

    switch (choixUser)
    {
    case 1:
        a = creer_abr;
        if (l != NULL)
        {
            printf("Erreur de creation de la liste de positions.\n");
        }
        else
        {
            printf("Liste de positions creee.\n");
        }
        break;
    case 2:
        printf("Nom du fichier ?\n");
        scanf("%s", nomFichier);
        if (charger_fichier(a, nomFichier) >= 0){
            printf("Reussite\n");
        } else
            printf("Echech\n");
        break;
    }
    return 0;
}
