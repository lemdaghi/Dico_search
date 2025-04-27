#include "search_pointers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Crée un tableau de pointeurs vers les mots
char **creer_tableau_pointeurs(char **dico, int taille) {
    char **pointeurs = malloc(taille * sizeof(char*));
    if (!pointeurs) {
        perror("Erreur allocation pointeurs");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < taille; i++) {
        pointeurs[i] = dico[i];
    }
    return pointeurs;
}

// Recherche binaire sur le tableau de pointeurs
int rechercher_pointeurs(char **pointeurs, int taille, const char *mot) {
    int gauche = 0;
    int droite = taille - 1;

    while (gauche <= droite) {
        int milieu = (gauche + droite) / 2;
        int cmp = strcoll(mot, pointeurs[milieu]);
        if (cmp == 0) {
            return 1;
        } else if (cmp < 0) {
            droite = milieu - 1;
        } else {
            gauche = milieu + 1;
        }
    }
    return 0;
}

// Libère le tableau de pointeurs (pas les mots eux-mêmes)
void liberer_pointeurs(char **pointeurs) {
    free(pointeurs);
}
