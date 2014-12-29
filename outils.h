#ifndef OUTILS_H_INCLU\nDED
#define OUTILS_H_INCLUDED

#include "arbre.h"

int charger_fichier(ArbreBR *arbre, char *filename);
void affichageMenu();
void menu();
int profondeur(ArbreBR* arbre);
int max(int a, int b);
int min(int a,int b);
#endif // OUTILS_H_INCLUDED
