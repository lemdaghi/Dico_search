#include "search_trie.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// TrieNode* creer_trie() {
//     TrieNode *nouv = malloc(sizeof(TrieNode));
//     for (int i = 0; i < 26; i++) {
//         nouv->fils[i] = NULL;
//     }
//     nouv->fin_mot = 0;
//     return nouv;
// }

// void inserer_trie(TrieNode *racine, const char *mot) {
//     while (*mot) {
//         char c = *mot;
//         if (c >= 'A' && c <= 'Z') {
//             int index = c - 'A';
//             if (!racine->fils[index]) {
//                 racine->fils[index] = creer_trie();
//             }
//             racine = racine->fils[index];
//         }
//         mot++;
//     }
//     racine->fin_mot = 1;
// }

// int rechercher_trie(TrieNode *racine, const char *mot) {
//     while (*mot) {
//         char c = *mot;
//         if (c >= 'A' && c <= 'Z') {
//             int index = c - 'A';
//             if (!racine->fils[index]) {
//                 return 0;
//             }
//             racine = racine->fils[index];
//         }
//         mot++;
//     }
//     return racine->fin_mot;
// }

TrieNode *creer_trie() {
    TrieNode *nouv = malloc(sizeof(TrieNode));
    if (nouv) {
        memset(nouv->fils, 0, sizeof(nouv->fils));  // Initialise tous les fils à NULL
        nouv->fin_mot = 0;                          // Pas un mot complet encore
    }
    return nouv;
}

void inserer_trie(TrieNode *racine, const char *mot) {
    while (*mot) {
        unsigned char index = (unsigned char)*mot;
        if (!racine->fils[index]) {
            racine->fils[index] = calloc(1, sizeof(TrieNode));
        }
        racine = racine->fils[index];
        mot++;
    }
    racine->fin_mot = 1;
}

int rechercher_trie(TrieNode *racine, const char *mot) {
    while (*mot) {
        unsigned char index = (unsigned char)*mot;
        if (!racine->fils[index]) {
            return 0;  // chemin cassé
        }
        racine = racine->fils[index];
        mot++;
    }
    return racine->fin_mot;
}

void liberer_trie(TrieNode *racine) {
    for (int i = 0; i < 26; i++) {
        if (racine->fils[i]) {
            liberer_trie(racine->fils[i]);
        }
    }
    free(racine);
}
