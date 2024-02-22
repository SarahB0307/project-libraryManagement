#ifndef BIBLIOLC_H
#define BIBLIOLC_H

typedef struct livre {
    int num;
    char *titre;
    char *auteur;
    struct livre *suiv;
} Livre;

typedef struct { /* Tete fictive */
    Livre *L; /* Premier element */
} Biblio;

Livre* creer_livre(int num, char* titre, char* auteur);
void liberer_livre(Livre* l);
Biblio* creer_biblio();
void liberer_biblio(Biblio* b);
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur);
void afficher_biblio(Biblio* b);
Livre* recherche_par_numero(Biblio* b, int num);
Livre* recherche_par_titre(Biblio* b, char* titre);
Biblio * recherche_par_auteur (Biblio* b, char* auteur);
void suppression_ouvrage (Biblio* b, int num , char * auteur , char * titre) ;
void fusion_biblios(Biblio* b1, Biblio* b2);
Biblio* recherche_exemplaires_multiples(Biblio* b) ;



#endif /* BIBLIOLC_H */
