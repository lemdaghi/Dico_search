#ifndef SEARCH_TRIE_H
#define SEARCH_TRIE_H

typedef struct TrieNode {
    struct TrieNode *fils[256]; // 26 lettres de l'alphabet A-Z
    int fin_mot;               // 1 si c'est la fin d'un mot
} TrieNode;

TrieNode* creer_trie();
void inserer_trie(TrieNode *racine, const char *mot);
int rechercher_trie(TrieNode *racine, const char *mot);
void liberer_trie(TrieNode *racine);

#endif
