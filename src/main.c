#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <sys/stat.h>

#include "dico_loader.h"
#include "utils.h"
#include "analyseur.h"
#include "search_sequential.h"
#include "search_binary.h"
#include "search_pointers.h"
#include "search_hash.h"
#include "search_bst.h"
#include "search_trie.h"

#define MAX_LIGNE 1024
#define MAX_MOT 128

int dico_size = 0; // variable globale pour l'adaptateur séquentiel/binaire

// Adaptateurs pour la fonction générique
int recherche_sequentielle_adapt(void *dico, const char *mot) {
    return recherche_sequentielle((char **)dico, dico_size, mot);
}

int recherche_binaire_adapt(void *dico, const char *mot) {
    return recherche_binaire((char **)dico, dico_size, mot);
}

int recherche_pointers_adapt(void *structure, const char *mot) {
    char **pointeurs = (char **)structure;
    return rechercher_pointeurs(pointeurs, dico_size, mot);
}

int recherche_hash_adapt(void *ht, const char *mot) {
    return rechercher_hash((HashTable *)ht, mot);
}

int recherche_bst_adapt(void *structure, const char *mot) {
    return rechercher_bst((Node *)structure, mot);
}

int recherche_trie_adapt(void *structure, const char *mot) {
    return rechercher_trie((TrieNode *)structure, mot);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s path_dico path_text\n", argv[0]);
        return 1;
    }

    // Activer la locale UTF-8
    setlocale(LC_ALL, "fr_FR.UTF-8");

    // Charger le dictionnaire
    char **dico = charger_dictionnaire(argv[1], &dico_size);
    if (!dico) {
        fprintf(stderr, "Erreur de chargement du dictionnaire : %s\n", argv[1]);
        return 1;
    }
    printf("%d mots charges.\n", dico_size);

    // Créer le dossier "results" s'il n'existe pas
    mkdir("results", 0777);
    
    // table de pointeurs
    printf("Copie dictionnaire -> table de pointeurs \n");
    char **pointeurs = creer_tableau_pointeurs(dico, dico_size);
    printf("Fin copie dictionnaire -> table de pointeurs \n");

    // table de hashage
    printf("Copie dictionnaire -> table de hashage \n");
    HashTable *ht = creer_hash_table(100003); // Taille premier grand nombre

    for (int i = 0; i < dico_size; i++) {
        inserer_hash(ht, dico[i]);
    }
    printf("Fin copie dictionnaire -> table de hashage \n");
    
    // // bst
    // printf("Copie dictionnaire -> BST \n");
    // Node *bst = NULL;
    // for (int i = 0; i < dico_size; i++) {
        //     bst = inserer_bst(bst, dico[i]);
        // }
        // printf("Fin copie dictionnaire -> BST \n");
        
    // Trie
    printf("Copie dictionnaire -> Trie \n");
    TrieNode *trie = creer_trie();
    for (int i = 0; i < dico_size; i++) {
        inserer_trie(trie, dico[i]);
    }
    printf("Fin copie dictionnaire -> Trie \n");

        
    // printf("Analyse du fichier %s avec dictionnaire %s...\n", argv[2], argv[1]);
    
    // Analyser avec séquentielle
    double debut = chrono();
    // printf("Analyse avec recherche séquentielle...\n");
    analyser_texte(argv[2], "results/invalides_sequentiel.txt", dico, recherche_sequentielle_adapt);
    double fin = chrono();
    printf("Temps méthode seq : %.7f secondes\n", fin - debut);


    // Analyser avec binaire
    debut = chrono();
    // printf("Analyse avec recherche binaire...\n");
    analyser_texte(argv[2], "results/invalides_binaire.txt", dico, recherche_binaire_adapt);
    fin = chrono();
    printf("Temps méthode bin : %.7f secondes\n", fin - debut);


    // Analyser avec pointeurs
    debut = chrono();
    // printf("Analyse avec tableau de pointeurs trié...\n");
    analyser_texte(argv[2], "results/invalides_pointers.txt", pointeurs, recherche_pointers_adapt);
    fin = chrono();
    printf("Temps méthode ptr : %.7f secondes\n", fin - debut);


    // Analyser avec hash
    debut = chrono();
    // printf("Analyse avec table de hachage...\n");
    analyser_texte(argv[2], "results/invalides_hash.txt", ht, recherche_hash_adapt);
    fin = chrono();
    printf("Temps méthode hash : %.7f secondes\n", fin - debut);


    // // Analyser avec BST
    // debut = chrono();
    // // printf("Analyse avec recherche bst...\n");
    // analyser_texte(argv[2], "results/invalides_bst.txt", bst, recherche_bst_adapt);
    // fin = chrono();
    // printf("Temps méthode bst : %.7f secondes\n", fin - debut);


    // Analyser avec Trie
    debut = chrono();
    // printf("Analyse avec Trie...\n");
    analyser_texte(argv[2], "results/invalides_trie.txt", trie, recherche_trie_adapt);
    fin = chrono();
    printf("Temps méthode trie : %.7f secondes\n", fin - debut);



    liberer_trie(trie);
    // liberer_bst(bst);
    liberer_hash_table(ht);
    liberer_pointeurs(pointeurs);
    liberer_dictionnaire(dico, dico_size);
    return 0;
}