#include "arbre.h"
#include "liste.h"

ArbreBR *creer_abr() //COMPLET, A TESTER
{
    ArbreBR *a = (ArbreBR)malloc(sizeof(ArbreBR));
    if (a == NULL)
        return NULL;
    else
    {
        a->nb_mots_differents = 0;
        a->nb_mots_total = 0;
        a->racine = NULL;
        return a;
    }
}

int ajouter_noeud(ArbreBR *arbre, NoeudABR *noeud) //INCOMPLET LULZ
{
    //Cas où l'ABR est vide
    if (arbre->racine == NULL)
    {
        arbre->racine = noeud;
        printf("Ajout du noeud dans l'arbre initialement vide\n");
        return 1; //Réussite
    }
    else
    {
        NoeudABR* x, *y;
        x = arbre->racine;
        while (x != NULL && strcasecmp(noeud->mot, x->mot) != 0)
        {
            y = x;
            if (strcasecmp(noeud->mot, x->mot) < 0)  //nouveau mot "avant" le mot testé
            {
                x = x->filsGauche;
            }
            else if (strcasecmp(noeud->mot, x->mot) > 0)  //nouveau mot "apres" le mot testé
            {
                x = x->filsDroit;
            }
        }
        if (strcasecmp(noeud->mot, x->mot) == 0)  //la boucle s'arrête car le mot existe dans l'un des noeuds
        {

        }
        else   //la boucle s'arrête car on est arrivé au bout de l'arbre
        {
            x = noeud;
        }
    }
}

NoeudABR *rechercher_noeud(ArbreBR *arbre, char *mot){ //COMPLET, A TESTER
    NoeudABR *x = arbre->racine;
    while (strcasecmp(mot, x->mot) != 0 && x != NULL){ //tant qu'on n'a pas trouvé le mot
        if (strcasecmp(mot, x->mot) < 0){
            x = x->filsGauche;
        }
        else if (strcasecmp(mot, x->mot) > 0){
            x = x->filsDroit;
        }
    }
    return x; //Si on sort de la boucle car on est arrivé au bout de l'arbre, on retourne x, qui vaut NULL. Sinon, on retourne le NoeudABR correspondant.
}
