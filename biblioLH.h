#ifndef BIBLIOLH_H
#define BIBLIOLH_H

typedef struct livreh {
    int clef;
    int  num;
    char* titre;
    char* auteur;
    struct livreh* suivant;
} LivreH;

typedef struct table {
    int nE;
    int m;
    LivreH** T ;
} BiblioH;

int fonctionClef(char* auteur);
LivreH* creer_livre_H(int num, char* titre, char* auteur);
void liberer_livre_H(LivreH* l);
BiblioH* creer_biblio_H(int m);
void liberer_biblio_H(BiblioH* b);
int fonctionHachage(int cle, int m);
void inserer_H(BiblioH* b, int num, char* titre, char* auteur);
void afficher_biblio_H(BiblioH* b);
LivreH* recherche_par_numero_H(BiblioH* b, int num);
LivreH* recherche_par_titre_H(BiblioH* b, char* titre);
BiblioH * recherche_par_auteur_H (BiblioH* b, char* auteur);
void suppression_ouvrage_H (BiblioH* b, int num , char * auteur , char * titre) ;
void fusion_biblios_H(BiblioH* b1, BiblioH* b2);
BiblioH* recherche_exemplaires_multiples_H(BiblioH* b) ;
#endif /* BIBLIOLH_H */

