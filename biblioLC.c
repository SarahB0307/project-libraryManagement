#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Livre* creer_livre(int num, char* titre, char* auteur) {
    Livre* livre = (Livre*)malloc(sizeof(Livre));
    if (livre == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le livre\n");
        exit(EXIT_FAILURE);
    }
    livre->num = num;
    livre->titre = strdup(titre);
    livre->auteur = strdup(auteur);
    livre->suiv = NULL;
    return livre;
}

void liberer_livre(Livre* l) {
    free(l->auteur);
    free(l->titre);
    free(l);
}

Biblio* creer_biblio() {
    Biblio* Bib = (Biblio*)malloc(sizeof(Biblio));
    if (Bib == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la bibliothèque\n");
        exit(EXIT_FAILURE);
    }
    Bib->L = NULL;
    return Bib;
}

void liberer_biblio(Biblio* b) {
    if (b== NULL)return ;
    Livre* tmp = b->L;
    while (tmp != NULL) {
        Livre* suivant = tmp->suiv;
        liberer_livre(tmp);
        tmp = suivant;
    }
    free(b);

}

void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur) {
    Livre *nouveau = creer_livre(num, titre, auteur);
    nouveau->suiv = b->L;
    b->L = nouveau;
}


// Affichage d'un livre
void afficher_livre(Livre* l) {
    printf("Numéro: %d Titre: %s Auteur: %s\n", l->num, l->titre, l->auteur);
}

// Affichage d'une bibliothèque
void afficher_biblio(Biblio* b) {
    Livre* livre_courant = b->L;
    while (livre_courant != NULL) {
        afficher_livre(livre_courant);
        livre_courant = livre_courant->suiv;
    }
}

// Recherche d'un ouvrage par son numéro
Livre* recherche_par_numero(Biblio* b, int num) {
    Livre* livre_courant = b->L;
    while (livre_courant != NULL && livre_courant->num != num ) {
        livre_courant = livre_courant->suiv;
    }
    return livre_courant;
}

// Recherche d'un ouvrage par son titre
Livre* recherche_par_titre(Biblio* b, char* titre) {
    Livre* livre_courant = b->L;
    while (livre_courant != NULL && strcmp(livre_courant->titre, titre) != 0) {
        livre_courant = livre_courant->suiv;
    }
    return livre_courant;
}

// la recherche de tous les livres d’un meme auteur (retourne une bibliotheque)
Biblio * recherche_par_auteur (Biblio* b, char* auteur) {
    Livre* livre_courant = b->L;
    Biblio * bib = creer_biblio();
    while (livre_courant != NULL ) {
        if (strcmp(livre_courant->auteur, auteur) == 0){
            inserer_en_tete (bib,livre_courant->num ,livre_courant->titre ,livre_courant->auteur);
        }
        livre_courant = livre_courant->suiv;
        
    }
    return bib;
}

// Suppression d'un ouvrage
void suppression_ouvrage (Biblio* b, int num , char * auteur , char * titre) {
    Livre *prev = NULL, *current = b->L;
    while ( current != NULL && current->num != num || strcmp(current->titre, titre) != 0 || strcmp(current->auteur, auteur) != 0 ){
        prev = current ;
        current = current->suiv;
    }
    if (current ){
        if (prev == NULL){
            b->L = current-> suiv ;
        }
        else {
            prev->suiv = current->suiv ;
        }
        liberer_livre(current);
    }
}

// Fusion de deux bibliothèques en ajoutant la deuxième à la première et en supprimant la deuxième
void fusion_biblios(Biblio* b1, Biblio* b2) {
    if (b1->L == NULL) {
        b1->L = b2->L;
    } else {
        Livre* last = b1->L;
        while (last->suiv != NULL) {
            last = last->suiv;
        }
        last->suiv = b2->L;
    }
    free(b2);
}

Biblio* ouvrages_multiples(Biblio* biblio) {
    Biblio* exemplaires_multiples = creer_biblio();
    Livre* livre = biblio->L;

    while (livre != NULL) {
        Biblio * bib = recherche_par_auteur(biblio, livre->auteur);
        Livre * livre_aut = bib->L;
        
        while ( livre_aut != NULL ) {
            if (strcmp(livre->titre, livre_aut->titre) == 0 && livre->num != livre_aut->num){
                inserer_en_tete(exemplaires_multiples, livre->num, livre->titre, livre->auteur);
                inserer_en_tete(exemplaires_multiples, livre_aut->num, livre_aut->titre, livre_aut->auteur);
            }  
            livre_aut = livre_aut->suiv;
        }
        livre = livre->suiv;
    }

    return exemplaires_multiples;
}
