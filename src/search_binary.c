#include "search_binary.h"
#include "utils.h"
#include <string.h>

// int recherche_binaire(char **dico, int nb_mots, const char *mot) {
//     int gauche = 0;
//     int droite = nb_mots - 1;

//     while (gauche <= droite) {
//         int milieu = (gauche + droite) / 2;
//         int cmp = strcmp(mot, dico[milieu]);

//         if (cmp == 0) {
//             return 1; // Trouvé
//         }
//         else if (cmp < 0) {
//             droite = milieu - 1;
//         }
//         else {
//             gauche = milieu + 1;
//         }
//     }
//     return 0; // Non trouvé
// }

int recherche_binaire(char **dico, int taille, const char *mot) {
    int gauche = 0;
    int droite = taille - 1;

    while (gauche <= droite) {
        int milieu = (gauche + droite) / 2;
        // int cmp = comparer_mots_francais(mot, dico[milieu]);
        to_lowercase(dico[milieu]);
        int cmp = strcoll(mot, dico[milieu]);

        if (cmp == 0) {
            return 1; // Trouvé
        } else if (cmp < 0) {
            droite = milieu - 1;
        } else {
            gauche = milieu + 1;
        }
    }

    return 0; // Pas trouvé
}
