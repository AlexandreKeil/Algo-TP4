#include "liste.h"


ListePosition *creer_liste_positions()
{
    ListePosition * l = (ListePosition*)malloc(sizeof(ListePosition));
    if (l == NULL)
    {
        printf("creation de liste echouee \n");
        return NULL;
    }

    l->debut = NULL;
    l->nb_elements = 0;
    printf("Creation de liste reussie \n");
    return l;
}

int ajouter_position(ListePosition *listeP, int ligne, int ordre, int num_phrase)
{
    if (listeP == NULL) // Liste non existant non existant
    {
        printf("Cette liste n'existe pas \n");
        return 0;
    }

//Creation de la position
    Position* p = creer_position (ligne, ordre, num_phrase);

    if (listeP->debut == NULL) // Liste vide
    {
        listeP->debut = p;
        printf("Ajoute \n");
        listeP->nb_elements++;
        return 1;
    }

    Position *ptr = listeP->debut;

    if ((p->numero_ligne < ptr->numero_ligne | ((p->numero_ligne == ptr->numero_ligne) && (p->ordre < ptr->ordre))))
    {
        p->suivant = ptr;
        listeP->debut = p;
        listeP->nb_elements++;
        printf("Ajoute \n");

        return 1;
    }

    if ((p->numero_ligne == ptr->numero_ligne) && (p->ordre == ptr->ordre))
    {
        printf("Cette position a deja ete creee \n");
        return 0;
    }


    while ( (ptr->suivant != NULL) && ((p->numero_ligne > ptr->suivant->numero_ligne) || ((p->numero_ligne == ptr->suivant->numero_ligne) && (p->ordre > ptr->suivant->ordre)))           )
        // fin de chaine ou ((ligne plus petit) ou (ligne egale et ordre plus petit))
        ptr = ptr->suivant;

    if (ptr->suivant == NULL)
    {
        ptr->suivant = p;
        listeP->nb_elements++;
        printf("Ajoute \n");
        return 1;
    }

    if ((p->numero_ligne == ptr->suivant->numero_ligne) && (p->ordre == ptr->suivant->ordre))
    {
        printf("Cette position a deja ete creee \n");
        return 0;
    }

    if ((p->numero_ligne < ptr->suivant->numero_ligne | ((p->numero_ligne == ptr->suivant->numero_ligne) && (p->ordre < ptr->suivant->ordre))))
    {
        p->suivant = ptr->suivant;
        ptr->suivant = p;
        listeP->nb_elements++;
        printf("Ajoute \n");

        return 1;
    }
}

Position* creer_position(int ligne, int ordre, int num_phrase)
{
    Position* p = (Position*)malloc(sizeof(Position));
    if (p==NULL)
    {
        printf("Creation de position echouee \n");
        return NULL;

    }

    p->numero_ligne = ligne;
    p->ordre=ordre;
    p->numero_phrase = num_phrase;
    p->suivant = NULL;
    return p;
}

void afficher_liste(ListePosition *l)
{
    if (l == NULL)
    {
        printf("La liste n'existe pas \n");
        return;
    }


    if (l->debut == NULL)
    {
        printf("La liste est vide \n");
        return;
    }

    Position* p = l->debut;
    while (p != NULL)
    {
        afficher_position(p);
        p=p->suivant;
    }
    printf("\nFini \n");
    return;
}

void afficher_position(Position *p)
{
    if (p == NULL)
        printf("Cette position n'existe pas\n");
    else
    {
        printf("Ligne : %d, Ordre : %d, Phrase :%d\n", p->numero_ligne, p->ordre, p->numero_phrase);
    }
    return;
}
