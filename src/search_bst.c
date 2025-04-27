#include "search_bst.h"
#include <stdlib.h>
#include <string.h>

Node* inserer_bst(Node *racine, const char *mot) {
    if (racine == NULL) {
        Node *nouv = malloc(sizeof(Node));
        nouv->mot = strdup(mot);
        nouv->gauche = nouv->droite = NULL;
        return nouv;
    }

    int cmp = strcmp(mot, racine->mot);
    if (cmp < 0) {
        racine->gauche = inserer_bst(racine->gauche, mot);
    } else if (cmp > 0) {
        racine->droite = inserer_bst(racine->droite, mot);
    }
    // égalité -> ne rien faire, pas besoin de doublons
    return racine;
}

int rechercher_bst(Node *racine, const char *mot) {
    if (racine == NULL) return 0;

    int cmp = strcoll(mot, racine->mot);
    if (cmp == 0) return 1;
    else if (cmp < 0) return rechercher_bst(racine->gauche, mot);
    else return rechercher_bst(racine->droite, mot);
}

void liberer_bst(Node *racine) {
    if (racine) {
        liberer_bst(racine->gauche);
        liberer_bst(racine->droite);
        free(racine->mot);
        free(racine);
    }
}
