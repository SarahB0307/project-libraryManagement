#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioLH.h"

int fonctionClef(char* auteur) {
    int somme = 0;
    for (int i = 0; auteur[i] != '\0'; i++) {
        somme += (int)auteur[i];
    }
    return somme;
}

LivreH* creer_livre_H(int num, char* titre, char* auteur) {
    LivreH* livre = (LivreH*)malloc(sizeof(LivreH));
    if (livre != NULL) {
        livre->clef = fonctionClef(auteur);
        livre->titre = strdup(titre);
        livre->auteur = strdup(auteur);
        livre->num =num;
        livre->suivant = NULL;
    }
    return livre;
}

void liberer_livre_H(LivreH* l) {
    if (l != NULL) {
        free(l->titre);
        free(l->auteur);
        free(l);
    }
}

BiblioH* creer_biblio_H(int m) {
    BiblioH* biblio = (BiblioH*)malloc(sizeof(BiblioH));
    if (biblio != NULL) {
        biblio->nE = 0;
        biblio->m = m;
        biblio->T= (LivreH**)malloc(m*sizeof(LivreH*));
        for (int i =0 ;i < m ; i++)
            biblio->T[i]=NULL;
    }
    return biblio;
}

void liberer_biblio_H(BiblioH* b) {
    if (b != NULL) {
        for (int i = 0; i < b->m; i++) {
            LivreH* current = b->T[i];
            while (current != NULL) {
                LivreH* temp = current;
                current = current->suivant;
                liberer_livre_H(temp);
            }
        }
        free(b->T);
        free(b);
    }
}

int fonctionHachage(int cle, int m) {
    const double A = (sqrt(5) - 1) / 2;
    return (int)(m * ((cle * A) - (int)(cle * A)));
}

void inserer_H(BiblioH* b, int num, char* titre, char* auteur) {
    int index = fonctionHachage(fonctionClef(auteur), b->m);
    LivreH* nouveau_livre = creer_livre_H(num, titre, auteur);
    if (nouveau_livre == NULL)
        return;
    nouveau_livre->suivant = b->T[index];
    b->T[index] = nouveau_livre;
    b->nE++;
}


void afficher_livre_H(LivreH* livre) {
    printf("Numéro: %d | Titre: %s | Auteur: %s\n", livre->num, livre->titre, livre->auteur);
}

void afficher_biblio_H(BiblioH* biblio) {
    for (int i = 0; i < biblio->m; ++i) {
        LivreH* courant = biblio->T[i];
        while (courant != NULL) {
            afficher_livre_H(courant);
            courant = courant->suivant;
        }
    }
}

LivreH* recherche_par_numero_H(BiblioH* b, int num) {
    for (int i = 0; i < b->m; i++) {
        LivreH* courant = b->T[i];
        while (courant != NULL) {
            if (courant->num == num) {
                return courant; 
            }
            courant = courant->suivant;
        }
    }
    return NULL; 
}
LivreH* recherche_par_titre_H(BiblioH* biblio, char* titre) {
    
    for (int i = 0; i < biblio->m; i++) {
        LivreH* courant = biblio->T[i];
        while (courant != NULL) {
            if (strcmp(courant->titre, titre) == 0) {
                return courant; 
            }
            courant = courant->suivant;
        }
    }
    return NULL; 
}

BiblioH* recherche_par_auteur_H(BiblioH* biblio, char* auteur) {
    int clef = fonctionClef(auteur);
    int indice = fonctionHachage(clef, biblio->m);
    BiblioH* livres_auteur = creer_biblio_H(biblio->m);
    LivreH* courant = biblio->T[indice];
    while (courant != NULL) {            
        inserer_H(livres_auteur, courant->num, courant->titre, courant->auteur);
        
        courant=courant->suivant;
    }
    return livres_auteur;
}//beaucoup mieux que la liste chainées 

// Suppression d'un ouvrage

void suppression_ouvrage_H(BiblioH* b, int num, char* titre, char* auteur) {
    int clef = fonctionClef(auteur);
    int indice = fonctionHachage(clef, b->m);
    
    LivreH* prec = NULL;
    LivreH* courant = b->T[indice];
    
    while (courant != NULL) {
        if (courant->num == num && strcmp(courant->titre, titre) == 0 && strcmp(courant->auteur, auteur) == 0) {
            if (prec == NULL) {
                b->T[indice] = courant->suivant;
            } else {
                prec->suivant = courant->suivant;
            }
            free(courant);
            return;
        }
        prec = courant;
        courant = courant->suivant;
    }
}

void fusion_biblios_H(BiblioH* b1, BiblioH* b2) {
    for (int i = 0; i < b2->m; i++) {
        LivreH* courant = b2->T[i];
        while (courant != NULL) {
            inserer_H(b1, courant->num, courant->titre, courant->auteur);
            courant =courant->suivant ;
        }
    }
    liberer_biblio_H(b2);
}

BiblioH* recherche_exemplaire_multiples_H(BiblioH* biblio) {
    // Créer une table de hachage temporaire pour stocker les titres des livres déjà rencontrés
    BiblioH* titres_deja_vus = creer_biblio_H(biblio->m);

    // Créer une bibliothèque pour stocker les livres avec plusieurs exemplaires
    BiblioH* exemplaires_multiples = creer_biblio_H
    (biblio->m);

    // Parcourir chaque case de la table de hachage
    for (int i = 0; i < biblio->m; i++) {
        LivreH* livre = biblio->T[i];

        // Parcourir la liste de livres dans cette case
        while (livre != NULL) {
            // Vérifier si le titre du livre est déjà dans la table de hachage temporaire
            LivreH* existant = recherche_par_titre_H(titres_deja_vus, livre->titre);

            if (existant != NULL && existant->num != livre->num ) {
                // Le titre existe déjà, donc ce livre a un exemplaire multiple
                inserer_H(exemplaires_multiples, livre->num, livre->titre, livre->auteur);
                inserer_H(exemplaires_multiples, existant->num, existant->titre, existant->auteur);
            } else {
                // Ajouter le titre du livre dans la table de hachage temporaire
                inserer_H(titres_deja_vus, livre->num, livre->titre, livre->auteur);
            }

            livre = livre->suivant;
        }
    }

    // Libérer la mémoire de la table de hachage temporaire
    liberer_biblio_H(titres_deja_vus);

    return exemplaires_multiples;
}


