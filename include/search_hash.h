#ifndef SEARCH_HASH_H
#define SEARCH_HASH_H

typedef struct Cellule {
    char *mot;
    struct Cellule *suivant;
} Cellule;

typedef struct {
    Cellule **table;
    int taille_table;
} HashTable;

HashTable* creer_hash_table(int taille);
void inserer_hash(HashTable *ht, const char *mot);
int rechercher_hash(HashTable *ht, const char *mot);
void liberer_hash_table(HashTable *ht);

#endif
