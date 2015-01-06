#include "arbre.h"
#include "liste.h"

ArbreBR *creer_abr(){ //COMPLET, A TESTER

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

int is_equilibre(ArbreBR * arbre) // renvoie 1 si equilibré, 0 sinon.
{
    if(arbre->racine == NULL)
        return 1;

    ArbreBR *SAGauche = creer_abr();
    ArbreBR *SADroit = creer_abr();
    SAGauche->racine = arbre->racine->filsGauche;
    SADroit->racine = arbre->racine->filsDroit;

    if (equilibre(arbre) >= -1 && equilibre(arbre) <= 1 && is_equilibre(SAGauche) && is_equilibre(SADroit))
        return 1;

    else
        return 0;
}

int equilibre(ArbreBR *arbre)
{
    if(arbre->racine == NULL)
        return 0;

    ArbreBR *SAGauche = creer_abr();
    ArbreBR *SADroit = creer_abr();
    SAGauche->racine = arbre->racine->filsGauche;
    SADroit->racine = arbre->racine->filsDroit;

    return profondeur(SAGauche)- profondeur(SADroit);
}


int ajouter_noeud(ArbreBR *arbre, NoeudABR *noeud)
{


     if (noeud == NULL)
        return 0;

       //Cas où l'ABR est vide
  if (arbre->racine == NULL)
    {
        arbre->racine = noeud;
        arbre->nb_mots_differents++;
        arbre->nb_mots_total++;
        printf("Ajout du noeud dans l'arbre initialement vide\n");
        return 1; //Réussite
    }
    else
    {
        int different = inserer_noeud (&arbre->racine, noeud);// on utilise un pointeur de pointeur pour modifier la valeur contenue par le pointeur
        arbre->nb_mots_differents= arbre->nb_mots_differents + different ;
        arbre->nb_mots_total++;
        return 1;
    }


}


int ajouter_noeud_reeq(ArbreBR *arbre, NoeudABR *n)
{


     if (n == NULL)
        return 0;

       //Cas où l'ABR est vide

    NoeudABR* noeud = copie_noeud(n); // pour enlever les successeurs


  if (arbre->racine == NULL)
    {
        arbre->racine = n;
        arbre->nb_mots_differents++;
        arbre->nb_mots_total++;
        printf("Ajout du noeud dans l'arbre initialement vide\n");
        return 1; //Réussite
    }
    else
    {
        int different = inserer_noeud_reeq (&arbre->racine, noeud);// on utilise un pointeur de pointeur pour modifier la valeur contenue par le pointeur
        arbre->nb_mots_differents= arbre->nb_mots_differents + different ;
        arbre->nb_mots_total++;
        return 1;
    }

}



int inserer_noeud_reeq (NoeudABR **n, NoeudABR *noeud) // retourne 1 si nouveau mot, 0 si dejà dans l'arbre
{
    int retour;
    ArbreBR* SAGauche=creer_abr();
    ArbreBR* SADroit =creer_abr();

    if (*n == NULL)
    {
        *n = noeud;
        return 1;
    }

    if (strcasecmp(noeud->mot, (*n)->mot)<0)
    {
        retour = inserer_noeud_reeq (&(*n)->filsGauche, noeud);
        SAGauche ->racine = (*n)->filsGauche;
        reequilibre(SAGauche);
        return retour;
    }
    if (strcasecmp(noeud->mot, (*n)->mot)>0)
    {

         retour = inserer_noeud_reeq (&(*n)->filsDroit, noeud);
         SADroit ->racine = (*n)->filsDroit;
         reequilibre(SADroit);
         return retour;

    }
    else // le mot est déjà inséré
    {
            ListePosition *l = creer_liste_positions();
            ajouter_position(l, (*n)->positions.debut->numero_ligne, (*n)->positions.debut->ordre, (*n)->positions.debut->numero_phrase);
            ajouter_position(l, noeud->positions.debut->numero_ligne, noeud->positions.debut->ordre, noeud->positions.debut->numero_phrase);
            (*n)->positions = *l ;
            return 0;
    }
}




int inserer_noeud (NoeudABR **n, NoeudABR *noeud) // retourne 1 si nouveau mot, 0 si dejà dans l'arbre
{

    Position *x;

    if (*n == NULL)
    {
        *n = noeud;
        return 1;
    }

    if (strcasecmp(noeud->mot, (*n)->mot)<0)
        return inserer_noeud (&(*n)->filsGauche, noeud);

    if (strcasecmp(noeud->mot, (*n)->mot)>0)
         return inserer_noeud (&(*n)->filsDroit, noeud);

    else // le mot est déjà inséré
    {

            x = noeud->positions.debut;
             while (x != NULL)
            {
                   ajouter_position(&(*n)->positions, x->numero_ligne, x->ordre, x->numero_phrase);
                   x = x->suivant;

            }
            return 0;
    }
}



NoeudABR *rechercher_noeud(ArbreBR *arbre, char *mot){ //COMPLET, A TESTER
    NoeudABR *x = arbre->racine;
    Position * pos ;
    int i =1;

    if (x==NULL)
    {
        printf("Le mot '%s' n'est pas dans l'arbre \n",mot);
        return NULL;
    }

    if (strcasecmp(mot, x->mot) == 0)
    {
        printf("Position(s) de '%s' : \n", mot);
        afficher_liste(x->positions);
    }
    else
    {
        ArbreBR *SADroit = creer_abr();
        ArbreBR *SAGauche = creer_abr();
        SADroit->racine = arbre->racine->filsDroit;
        SAGauche->racine = arbre->racine->filsGauche;

        if (strcasecmp(mot, x->mot) < 0)
           return rechercher_noeud(SAGauche,mot); //PEUT RENVOYER NULL SI L'ARBRE N'A PAS DE FG

        else //(strcasecmp(mot, x->mot) > 0)
           return rechercher_noeud(SADroit,mot); //PEUT RENVOYER NULL SI L'ARBRE N'A PAS DE FD

    }


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
    ArbreBR *SADroit = creer_abr();
    ArbreBR *SAGauche = creer_abr();

    if (arbre == NULL || arbre->racine == NULL)
        return -1;


    else
    {
        afficher_arbre(*arbre);
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


NoeudABR *copie_noeud(NoeudABR *n)
{
        NoeudABR* noeud = (NoeudABR*)malloc(sizeof(NoeudABR));
            if (noeud==NULL)
                return NULL;

        noeud->filsDroit=NULL;
        noeud->filsGauche=NULL;

        ListePosition *pos = creer_liste_positions();
        *pos = n->positions;
        noeud->positions = *pos;

        noeud->mot = malloc( 30*sizeof(char));
        strcpy(noeud->mot, n->mot);
        return noeud;
}

/*
ArbreBR * reequilibre_tous(ArbreBR *arbre, ArbreBR * arbre_final)
{

    if (arbre == NULL)
        return NULL;


    if (arbre->racine != NULL)
    {
        NoeudABR*noeud = *noeud(arbre->racine);

        ajouter_noeud(arbre_final,noeud);

        arbre_final = reequilibre(arbre_final);

          if (arbre_final == NULL)
                printf("Veuillez d'abord creer un ABR (choix numero 1 du menu) et charger un fichier dans cet arbre (choix 2)\n\n");
                else
                {
                printf("Voici les caracteristiques de l'ABR cree \n");
                printf("Nombre de noeuds : %d\n",arbre_final->nb_mots_differents);
                printf("Profondeur : %d\n", profondeur(arbre_final));
                if (is_equilibre(arbre_final) == 1)
                    printf("L'ABR est equilibre\n");
                else printf("L'ABR n'est pas equilibre\n");
                }


        if (arbre->racine->filsDroit != NULL)
        {
        ArbreBR *SADroit = creer_abr();
        SADroit->racine = arbre->racine->filsDroit;
        reequilibre_tous(SADroit, arbre_final);
        }

        if (arbre->racine->filsGauche != NULL)
        {
        ArbreBR *SAGauche = creer_abr();
        SAGauche->racine = arbre->racine->filsGauche;
        reequilibre_tous(SAGauche, arbre_final);
        }
    }

    return arbre_final;

}*/


ArbreBR* RD(ArbreBR* arbre)
{
    if (arbre == NULL || arbre->racine->filsGauche == NULL)
        return arbre;

   NoeudABR* tmp = arbre->racine->filsGauche;
   arbre->racine->filsGauche = tmp->filsDroit;
   tmp->filsDroit = arbre->racine;
   arbre->racine = tmp;

   return arbre;
}

ArbreBR* RG(ArbreBR* arbre)
{
    if (arbre == NULL || arbre->racine->filsDroit == NULL)
        return arbre;


   NoeudABR* tmp = arbre->racine->filsDroit;
   arbre->racine->filsDroit = tmp->filsGauche;
   tmp->filsGauche = arbre->racine;
   arbre->racine = tmp;

   return arbre;

}


ArbreBR* RGD(ArbreBR* arbre)
{
    if (arbre == NULL || arbre->racine->filsGauche == NULL||arbre->racine->filsGauche->filsDroit == NULL )
        return arbre;

    ArbreBR *SAGauche = creer_abr();
    SAGauche->racine = arbre->racine->filsGauche;


    arbre->racine->filsGauche = RG(SAGauche)->racine;
    RD(arbre);

    return arbre;
}

ArbreBR* RDG(ArbreBR* arbre)
{
    if (arbre == NULL || arbre->racine->filsDroit == NULL||arbre->racine->filsDroit->filsGauche == NULL )
        return arbre;

    ArbreBR *SADroit = creer_abr();
    SADroit->racine = arbre->racine->filsDroit;


    arbre->racine->filsDroit = RD(SADroit)->racine;
    RG(arbre);

    return arbre;
}


ArbreBR * reequilibre_tous(ArbreBR *arbre, ArbreBR *arbre_final) ///NE FONCTIONNE PAS
{
    ArbreBR * SADroit = creer_abr();
    ArbreBR * SAGauche = creer_abr();

    if (arbre == NULL || arbre->racine ==NULL  )
        return NULL;

    afficher_arbre(*arbre_final);
    printf("\n\n");
    SAGauche->racine = arbre->racine->filsGauche;
    SADroit->racine = arbre->racine->filsDroit;

    if (arbre->racine->mot !=NULL)
    ajouter_noeud_reeq(arbre_final,copie_noeud(arbre->racine));

    reequilibre_tous(SAGauche,arbre_final);

    reequilibre_tous(SADroit,arbre_final);

    return arbre_final;

}

ArbreBR* reequilibre(ArbreBR *arbre) /// fonctionne pour un arbre petit (premier apparence d'un eq=2)
{
    if (equilibre(arbre) == 2)
    {
        ArbreBR *SAGauche = creer_abr();
        SAGauche->racine = arbre->racine->filsGauche;
        if (equilibre(SAGauche) >=0)
           return RG(arbre);
        else
           return RGD(arbre);
    }

    if (equilibre(arbre) == -2)
    {
        ArbreBR *SADroit = creer_abr();
        SADroit->racine = arbre->racine->filsDroit;
        if (equilibre(SADroit) <= 0)
            return RD(arbre);
        else return RDG(arbre);
    }

    return arbre;

}

void liberer_arbre(ArbreBR *a){
    NoeudABR* noeudRac = a->racine;
    liberer_noeud(noeudRac);
    free(a);
}

void liberer_noeud(NoeudABR *n){
    if (n->filsGauche != NULL){
        liberer_noeud(n->filsGauche);
    }
    if (n->filsDroit != NULL){
        liberer_noeud(n->filsDroit);
    }
    liberer_position(n->positions.debut);
    free(n);
}
