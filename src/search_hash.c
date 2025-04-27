#include "search_hash.h"
#include <stdlib.h>
#include <string.h>

unsigned int hash(const char *mot, int taille_table) {
    unsigned int h = 0;
    for (int i = 0; mot[i]; i++) {
        h = 31 * h + (unsigned char)mot[i];
    }
    return h % taille_table;
}

HashTable* creer_hash_table(int taille) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->taille_table = taille;
    ht->table = calloc(taille, sizeof(Cellule*)); // initialise à NULL
    return ht;
}

void inserer_hash(HashTable *ht, const char *mot) {
    unsigned int idx = hash(mot, ht->taille_table);
    
    // On insère en tête de la liste chaînée
    Cellule *nouvelle = malloc(sizeof(Cellule));
    nouvelle->mot = strdup(mot);
    nouvelle->suivant = ht->table[idx];
    ht->table[idx] = nouvelle;
}

int rechercher_hash(HashTable *ht, const char *mot) {
    unsigned int idx = hash(mot, ht->taille_table);
    Cellule *courant = ht->table[idx];
    
    // On parcourt la liste chaînée dans la case
    while (courant) {
        if (strcmp(courant->mot, mot) == 0) {
            return 1;
        }
        courant = courant->suivant;
    }
    return 0;
}

void liberer_hash_table(HashTable *ht) {
    for (int i = 0; i < ht->taille_table; i++) {
        Cellule *courant = ht->table[i];
        while (courant) {
            Cellule *tmp = courant;
            courant = courant->suivant;
            free(tmp->mot);
            free(tmp);
        }
    }
    free(ht->table);
    free(ht);
}
