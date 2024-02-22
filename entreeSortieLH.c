#include <stdio.h>
#include <stdlib.h>
#include "entreeSortieLH.h"
#include "biblioLH.h"


BiblioH* charger_n_entrees_H(char* nomfic, int n) {
    FILE *fichier = fopen(nomfic, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    BiblioH* bibliotheque = creer_biblio_H(n);
    int num;
    char titre[100], auteur[100];
    for (int i = 0; i < n; ++i) {
        if (fscanf(fichier, "%d %s %s", &num, titre, auteur) == 3) {
            inserer_H(bibliotheque, num, titre, auteur);
        } else {
            fprintf(stderr, "Erreur de lecture du fichier.\n");
            fclose(fichier);
            liberer_biblio_H(bibliotheque);
            return NULL;
        }
    }

    fclose(fichier);
    return bibliotheque;
}

void enregistrer_biblio_H(BiblioH *b, char* nomfic) {
    FILE *fichier = fopen(nomfic, "w");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    for (int i =0; i< b->nE ;i++){
        LivreH* livre_courant = b->T[i];
        while (livre_courant != NULL) {
            fprintf(fichier, "%d %s %s\n", livre_courant->num, livre_courant->titre, livre_courant->auteur);
            livre_courant = livre_courant->suivant;
        }
    }

    fclose(fichier);
}

