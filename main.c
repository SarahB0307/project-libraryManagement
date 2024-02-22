#include <stdio.h>
#include <stdlib.h>
#include "entreeSortieLC.h"
#include "biblioLC.h"


void menu() {
    printf("Actions possibles sur la bibliothèque :\n");
    printf("0 - Sortie du programme\n");
    printf("1 - Affichage de la bibliothèque\n");
    printf("2 - Insérer un ouvrage\n");
}
int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <nom du fichier> <nombre de lignes>\n", argv[0]);
        return 1;
    }

    char* nom_fichier = argv[1];
    int nombre_lignes = atoi(argv[2]);

    Biblio* bibliotheque = charger_n_entrees(nom_fichier, nombre_lignes);
    if (bibliotheque == NULL) {
        fprintf(stderr, "Erreur lors du chargement de la bibliothèque.\n");
        return 1;
    }
    enregistrer_biblio(bibliotheque, "bibliotheque_enregistree.txt");
    int rep;
        char choix[256]; 

        do {
            menu(); // Affichage du menu à chaque itération

            printf("Choisissez une action : ");
            fgets(choix, sizeof(choix), stdin); 

            // Convertir l'entrée en un entier
            rep = atoi(choix);

            switch (rep) {
                case 0:
                    printf("Sortie du programme.\n");
                    break;
                case 1:
                    printf("Affichage de la bibliothèque :\n");
                    afficher_biblio(bibliotheque);
                    break;
                case 2: {
                    // Insérer un ouvrage
                    int num;
                    char titre[256];
                    char auteur[256];

                    printf("Veuillez saisir le numéro, le titre et l'auteur de l'ouvrage : ");
                    fgets(choix, sizeof(choix), stdin); // Lecture de l'entrée de l'utilisateur

                    // Traitement de l'entrée de l'utilisateur
                    if ( sscanf(choix, "%d %s %s", &num, titre, auteur)==3){
                        inserer_en_tete(bibliotheque, num, titre, auteur);
                        printf("Ouvrage ajouté avec succès.\n");
                    }
                    else {
                        printf("Erreur Format.\n");
                    }
                    break;
                }
                // Ajoutez d'autres cas pour les autres actions possibles ici
                default:
                    printf("Action non reconnue.\n");
                    break;
            }
        } while (rep != 0);

        // Libérer la mémoire et terminer le programme
        liberer_biblio(bibliotheque);
        printf("Merci, et au revoir.\n");
    return 0;
}
