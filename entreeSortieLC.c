#include <stdio.h>
#include <stdlib.h>
#include "entreeSortieLC.h"
#include "biblioLC.h"

Biblio* charger_n_entrees(char* nomfic, int n) {
    FILE *fichier = fopen(nomfic, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    Biblio* bibliotheque = creer_biblio();

    int num;
    char titre[100], auteur[100];
    for (int i = 0; i < n; ++i) {
        if (fscanf(fichier, "%d %s %s", &num, titre, auteur) == 3) {
            inserer_en_tete(bibliotheque, num, titre, auteur);
        } else {
            fprintf(stderr, "Erreur de lecture du fichier.\n");
            fclose(fichier);
            liberer_biblio(bibliotheque);
            return NULL;
        }
    }

    fclose(fichier);
    return bibliotheque;
}

void enregistrer_biblio(Biblio *b, char* nomfic) {
    FILE *fichier = fopen(nomfic, "w");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Livre* livre_courant = b->L;
    while (livre_courant != NULL) {
        fprintf(fichier, "%d %s %s\n", livre_courant->num, livre_courant->titre, livre_courant->auteur);
        livre_courant = livre_courant->suiv;
    }

    fclose(fichier);
}
