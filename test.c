#include <stdio.h>
#include <time.h>
#include "biblioLC.h" 
#include "biblioLH.h" 
#include "entreeSortieLC.h"
#include "entreeSortieLH.h"
#include "stdlib.h"

void comparer_temps_recherche(int repetitions) {
    // Initialisation des structures de données
    Biblio *biblio_liste;
    BiblioH *biblio_table;

    // Variables pour mesurer les temps de calcul
    double temps_total_liste = 0.0;
    double temps_total_table = 0.0;

    // Répéter le test plusieurs fois pour obtenir des temps moyens
    for (int i = 0; i < repetitions; i++) {
        // Charger les données dans les structures de données
        biblio_liste = charger_n_entrees("GdeBiblio.txt", 10);
        biblio_table = charger_n_entrees_H("GdeBiblio.txt",10);
        // 176 IVNJJO mwk 
        //91735 SLVV qbarfaz 
        int numero = 91735;
        char *titre = "SLVV";
        char *auteur = "qbarfaz";

        // Mesurer le temps de recherche avec une liste chaînée
        clock_t debut_liste = clock();

        recherche_par_numero(biblio_liste, numero);//plus fiable pour les tests car chaque livres a un numéro unique 
        //recherche_par_titre(biblio_liste, titre);
        //recherche_par_auteur(biblio_liste, auteur);

        clock_t fin_liste = clock();

        temps_total_liste += ((double)(fin_liste - debut_liste) )/ CLOCKS_PER_SEC;

        // Mesurer le temps de recherche avec une table de hachage
        clock_t debut_table = clock();
    
        recherche_par_numero_H(biblio_table, numero);
        //recherche_par_titre_H(biblio_table, titre);
        //recherche_par_auteur_H(biblio_table, auteur);

        clock_t fin_table = clock();

        temps_total_table += (double)(fin_table - debut_table) / CLOCKS_PER_SEC;

        liberer_biblio(biblio_liste);
        liberer_biblio_H(biblio_table);
    }

    // Calculer les temps moyens de recherche pour chaque structure
    double temps_moyen_liste = temps_total_liste / repetitions;
    double temps_moyen_table = temps_total_table / repetitions;

    // Afficher les résultats
    printf("Temps moyen de recherche avec une liste chaînée : %f secondes\n", temps_moyen_liste);
    printf("Temps moyen de recherche avec une table de hachage : %f secondes\n", temps_moyen_table);

    // Comparer les temps de recherche et donner une conclusion
    if (temps_moyen_liste < temps_moyen_table) {
        printf("La liste chaînée est plus appropriée pour cette recherche.\n");
    } else {
        printf("La table de hachage est plus appropriée pour cette recherche.\n");
    }
}


void comparer_temps_taille(){

    int taille_min = 1000;
    int taille_max = 50000;
    int pas = 2000;
    // Initialisation des structures de données
    Biblio *biblio_liste;
    BiblioH *biblio_table;

    // Variables pour mesurer les temps de calcul
    double temps_liste = 0.0;
    double temps_table = 0.0;

    FILE *fichier1 = fopen("result_liste.txt", "w");
        if (fichier1 == NULL) {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
            return;
        }
    fprintf(fichier1,"LISTE CHAÎNÉE :\n");
    for (int m = taille_min; m <= taille_max; m += pas) {
        
        // Créez une bibliothèque avec une liste de taille m
        biblio_liste = charger_n_entrees("GdeBiblio.txt", m);
        //49999 UQMNAC mzeita 
        int numero = m/2;
        char * titre = "UQMNAC";
        char *auteur = "mzeit";

        // Mesurer le temps de recherche avec une liste chaînée
        clock_t debut_liste = clock();

        recherche_par_numero(biblio_liste, numero);//plus fiable pour les tests car chaque livre a un numéro unique 
        //recherche_par_titre(biblio_liste, titre);
        //recherche_par_auteur(biblio_liste, auteur);

        clock_t fin_liste = clock();

        temps_liste = ((double)(fin_liste - debut_liste) )/ CLOCKS_PER_SEC;

         // Afficher les résultats
        fprintf(fichier1,"%d %f \n", m, temps_liste);
        liberer_biblio(biblio_liste);
        
    }
    fclose(fichier1);
    FILE *fichier2 = fopen("result_table.txt", "w");
        if (fichier2 == NULL) {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
            return;
        }
    fprintf(fichier2,"TABLE DE HACHAGE :\n");
    for (int m = taille_min; m <= taille_max; m += pas) {
        // Créez une bibliothèque avec une table de hachage de taille m
        biblio_table = charger_n_entrees_H("GdeBiblio.txt", 49999);

        //49999 UQMNAC mzeita 
        int numero = m/2;
        char *titre = "UQMNACooooo";
        char *auteur = "mzeitaoooo";

        // Mesurer le temps de recherche avec une table de hachage
        clock_t debut_table = clock();
    
        recherche_par_numero_H(biblio_table, numero);
        //recherche_par_titre_H(biblio_table, titre);
        //recherche_par_auteur_H(biblio_table, auteur);

        clock_t fin_table = clock();

        temps_table = ((double)(fin_table - debut_table) )/ CLOCKS_PER_SEC;

         // Afficher les résultats
        fprintf(fichier2,"%d %f \n", m, temps_table);

        liberer_biblio_H(biblio_table);
    }
    fclose(fichier2);
}

// cette fonction sert à voir le graphe du temps d'exécution en fonction de la taille (taille variables)
void comparaison_taille (){
    int taille_min = 1000;
    int taille_max = 50000;
    int pas = 2000;
    FILE *fichier1 = fopen("result_taille_table.txt", "w");
    if (fichier1 == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    for (int m = taille_min; m <= taille_max; m += pas){
        BiblioH * b = creer_biblio_H(m);
        FILE *fichier2 = fopen("GdeBiblio.txt", "r");
        if (fichier2 == NULL) {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
            return ;
        }
        int num;
        char titre[100], auteur[100];
        for (int i = 0; i < 1000; ++i) {
            if (fscanf(fichier2, "%d %s %s", &num, titre, auteur) == 3) {
                inserer_H(b, num, titre, auteur);
            } else {
                fprintf(stderr, "Erreur de lecture du fichier.\n");
                fclose(fichier2);
                liberer_biblio_H(b);
                return ;
            }
        }
        clock_t debut = clock();
        recherche_par_numero_H(b, -1);
        clock_t fin = clock();
        double temps = ((double)(fin - debut) )/ CLOCKS_PER_SEC;
        fprintf(fichier1,"%d %f \n", m, temps);
        fclose(fichier2);
        liberer_biblio_H(b);
    }
    fclose(fichier1);
    }


int main() {
    comparer_temps_recherche(1000); // Faire le test n fois pour obtenir des temps moyens
    comparer_temps_taille();
     
   
    	
    return 0;
}

/*commandes pour gnuplot  :
  gnuplot
  set terminal png 
  set output 'courbe_livre_inexistant.png'
  set xlabel "taille"
  set ylabel "temps de recherche (seconde)"
  plot "result_liste.txt" using 1:2 with lines title "liste chainee - livre_inexistant" , "result_table.txt" using 1:2 with lines title "table de hachage - livre_inexistant

  gnuplot
  set terminal png 
  set output 'courbe_livre_milieu_taille_table.png'
  set xlabel "taille"
  set ylabel "temps de recherche (seconde)"
  plot "result_table.txt" using 1:2 with lines title "table de hachage - livre_milieu"



*/
