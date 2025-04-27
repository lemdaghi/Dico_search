#include "dico_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOT 64

char **charger_dictionnaire(const char *filename, int *nb_mots) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;

    char mot[MAX_MOT];
    int taille = 0;
    int capacite = 1000;
    char **dico = malloc(sizeof(char*) * capacite);

    while (fscanf(f, "%63s", mot) == 1) {
        if (taille >= capacite) {
            capacite *= 2;
            char **tmp = realloc(dico, sizeof(char*) * capacite);
            if (!tmp) {
                fprintf(stderr, "Erreur realloc\n");
                exit(1);
            }
            dico = tmp;
        }
        dico[taille] = strdup(mot);
        taille++;
    }
    fclose(f);
    *nb_mots = taille;
    return dico;
}

void liberer_dictionnaire(char **dico, int nb_mots) {
    for (int i = 0; i < nb_mots; i++) {
        free(dico[i]);
    }
    free(dico);
}
