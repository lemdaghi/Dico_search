// binary search tree
#ifndef SEARCH_BST_H
#define SEARCH_BST_H

typedef struct Node {
    char *mot;
    struct Node *gauche;
    struct Node *droite;
} Node;

Node* inserer_bst(Node *racine, const char *mot);
int rechercher_bst(Node *racine, const char *mot);
void liberer_bst(Node *racine);

#endif
