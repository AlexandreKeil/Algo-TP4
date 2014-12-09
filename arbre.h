#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct position {
    int numero_ligne;
    int ordre;
    int numero_phrase;
    struct position* suivant;
} Position;

typedef struct listePosition {
    Position* debut;
    int nb_elements;
} ListePosition;

typedef struct noeudABR {
    char* mot;
    ListePosition positions;
    struct noeudABR* filsGauche;
    struct noeudABR* filsDroit;
} NoeudABR;

typedef struct arbreBR {
    NoeudABR* racine;
    int nb_mots_differents;
    int nb_mots_total;
} ArbreBR;

ArbreBR *creer_abr();
int ajouter_noeud(ArbreBR *arbre, NoeudABR *noeud);
NoeudABR *rechercher_noeud(ArbreBR *arbre, char *mot);

#endif // ARBRE_H_INCLUDED
