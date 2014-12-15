#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include "arbre.h"

ListePosition *creer_liste_positions();
Position* creer_position(int ligne, int ordre, int num_phrase);
int ajouter_position(ListePosition *listeP, int ligne, int ordre, int num_phrase);
void afficher_liste(ListePosition *listeP);
void afficher_position(Position *p);

#endif // LISTE_H_INCLUDED
