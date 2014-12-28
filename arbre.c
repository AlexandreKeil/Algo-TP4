#include "arbre.h"
#include "liste.h"

ArbreBR *creer_abr() //COMPLET, A TESTER
{
    ArbreBR *a = (ArbreBR*)malloc(sizeof(ArbreBR));
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

int ajouter_noeud(ArbreBR *arbre, NoeudABR *noeud) //INCOMPLET
{
    if (noeud == NULL)
        return 0;

       //Cas où l'ABR est vide
    if (arbre->racine == NULL)
    {
        arbre->racine = noeud;
        printf("Ajout du noeud dans l'arbre initialement vide\n");
        arbre->racine = noeud ;
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
            ListePosition *l = creer_liste_positions();
            ajouter_position(l, x->positions.debut->numero_ligne, x->positions.debut->ordre, x->positions.debut->numero_phrase);
            ajouter_position(l, noeud->positions.debut->numero_ligne, noeud->positions.debut->ordre, noeud->positions.debut->numero_phrase);
            x->positions = *l ;
        }
        else   //la boucle s'arrête car on est arrivé au bout de l'arbre
        {
            x = noeud;
        }
    }
}

NoeudABR *rechercher_noeud(ArbreBR *arbre, char *mot){ //COMPLET, A TESTER
    NoeudABR *x = arbre->racine;
    while (strcasecmp(mot, x->mot) != 0 && x != NULL){ //tant qu'on n'a pas trouvé le mot et que l'arbre n'est pas fjni
        if (strcasecmp(mot, x->mot) < 0){
            x = x->filsGauche; //PEUT RENVOYER NULL SI L'ARBRE N'A PAS DE FG
        }
        else if (strcasecmp(mot, x->mot) > 0){
            x = x->filsDroit; //PEUT RENVOYER NULL SI L'ARBRE N'A PAS DE FD
        }
    }
    return x; //Si on sort de la boucle car on est arrivé au bout de l'arbre, on retourne x, qui vaut NULL. Sinon, on retourne le NoeudABR correspondant.
}

NoeudABR* creer_noeud(char* mot, int ligne, int ordre, int phrase)
{
        NoeudABR* noeud = (NoeudABR*)malloc(sizeof(NoeudABR));
            if (noeud==NULL)
                return NULL;
        noeud->filsDroit=NULL;
        noeud->filsGauche=NULL;
        ListePosition *pos = creer_liste_positions();
        ajouter_position(pos, ligne, ordre, phrase);
        noeud->positions = *pos;
        noeud->mot = mot;
        return noeud;
}




void afficher_arbre(ArbreBR arbre)
{
    if (arbre.racine == NULL)
        printf("\n");

    else
    {
        ArbreBR *SousArbreGauche = creer_abr();
        ArbreBR *SousArbreDroit = creer_abr();
        SousArbreGauche = arbre.racine->filsDroit;
        SousArbreGauche = arbre.racine->filsGauche;

        afficher_arbre(*SousArbreGauche);
        printf("%s",arbre.racine->mot);
        afficher_arbre(*SousArbreDroit);
    }

    return;
}
