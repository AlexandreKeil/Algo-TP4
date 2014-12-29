#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct stPosition {
    int numero_ligne;
    int ordre;
    int numero_phrase;
    struct stPosition* suivant;
} Position;

typedef struct stListePosition {
    Position* debut;
    int nb_elements;
} ListePosition;

typedef struct stNoeudABR {
    char* mot;
    ListePosition positions;
    struct stNoeudABR* filsGauche;
    struct stNoeudABR* filsDroit;
} NoeudABR;

typedef struct stArbreBR {
    NoeudABR* racine;
    int nb_mots_differents;
    int nb_mots_total;
} ArbreBR;

ArbreBR *creer_abr();
int ajouter_noeud(ArbreBR *arbre, NoeudABR *noeud);
NoeudABR* creer_noeud(char* mot, int ligne, int ordre,  int phrase);
void afficher_arbre(ArbreBR arbre);
int inserer_noeud(NoeudABR** n, NoeudABR* noeud);
#endif // ARBRE_H_INCLUDED
