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

int is_equilibre(ArbreBR * arbre)
{
    ///A FAIRE
}


int ajouter_noeud(ArbreBR *arbre, NoeudABR *noeud)
{

     if (noeud == NULL)
        return 0;

       //Cas o� l'ABR est vide
    if (arbre->racine == NULL)
    {
        arbre->racine = noeud;
        arbre->nb_mots_differents++;
        arbre->nb_mots_total++;
        printf("Ajout du noeud dans l'arbre initialement vide\n");
        return 1; //R�ussite
    }
    else
    {
        int different = inserer_noeud (&arbre->racine, noeud);// on utilise un pointeur de pointeur pour modifier la valeur contenue par le pointeur
        arbre->nb_mots_differents= arbre->nb_mots_differents + different ;
        arbre->nb_mots_total++;
        return 1;
    }


}

int inserer_noeud (NoeudABR **n, NoeudABR *noeud) // retourne 1 si nouveau mot, 0 si dej� dans l'arbre
{
    if (*n == NULL)
    {
        *n = noeud;
        return 1;
    }

    if (strcasecmp(noeud->mot, (*n)->mot)<0)
        return inserer_noeud (&(*n)->filsGauche, noeud);

    if (strcasecmp(noeud->mot, (*n)->mot)>0)
         return inserer_noeud (&(*n)->filsDroit, noeud);

    else // le mot est d�j� ins�r�
    {
            ListePosition *l = creer_liste_positions();
            ajouter_position(l, (*n)->positions.debut->numero_ligne, (*n)->positions.debut->ordre, (*n)->positions.debut->numero_phrase);
            ajouter_position(l, noeud->positions.debut->numero_ligne, noeud->positions.debut->ordre, noeud->positions.debut->numero_phrase);
            (*n)->positions = *l ;
            return 0;
    }
}



NoeudABR *rechercher_noeud(ArbreBR *arbre, char *mot){ //COMPLET, A TESTER
    NoeudABR *x = arbre->racine;
    while (strcasecmp(mot, x->mot) != 0 && x != NULL){ //tant qu'on n'a pas trouv� le mot et que l'arbre n'est pas fjni
        if (strcasecmp(mot, x->mot) < 0){
            x = x->filsGauche; //PEUT RENVOYER NULL SI L'ARBRE N'A PAS DE FG
        }
        else if (strcasecmp(mot, x->mot) > 0){
            x = x->filsDroit; //PEUT RENVOYER NULL SI L'ARBRE N'A PAS DE FD
        }
    }
    return x; //Si on sort de la boucle car on est arriv� au bout de l'arbre, on retourne x, qui vaut NULL. Sinon, on retourne le NoeudABR correspondant.
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
        noeud->mot = malloc( 30*sizeof(char));
        strcpy(noeud->mot, mot);
        return noeud;
}

/// PENSER A FREE (noeud -> mot ) dans DETRUIRE NOEUD

int profondeur(ArbreBR* arbre)
{
    if (arbre == NULL || arbre->racine == NULL)
        return -1;
    if (arbre->racine->filsDroit == NULL && arbre->racine->filsGauche == NULL)
        return 0;
    else
    {
        ArbreBR *SADroit = creer_abr();
        ArbreBR *SAGauche = creer_abr();
        SADroit->racine = arbre->racine->filsDroit;
        SAGauche->racine = arbre->racine->filsGauche;
        return max(profondeur(SADroit),profondeur(SAGauche)) + 1;
    }
}

void afficher_arbre(ArbreBR arbre)
{
    if (arbre.racine != NULL)
    {

    ArbreBR *SAGauche = creer_abr();
    ArbreBR *SADroit = creer_abr();
    SAGauche->racine = arbre.racine->filsGauche;
    SADroit->racine = arbre.racine->filsDroit;


    afficher_arbre(*SAGauche);


    printf("- %s\n",arbre.racine->mot);


    afficher_arbre(*SADroit);
    }

    return;
}
