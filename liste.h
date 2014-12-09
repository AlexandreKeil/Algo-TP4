#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include "arbre.h"

ListePosition* creer_liste_positions();
int ajouter_position(ListePosition *listeP, int ligne, int ordre, int num_phrase);

#endif // LISTE_H_INCLUDED
