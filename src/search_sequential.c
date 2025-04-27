#include "search_sequential.h"
#include <string.h>

int recherche_sequentielle(char **dico, int nb_mots, const char *mot) {
    for (int i = 0; i < nb_mots; i++) {
        if (strcoll(dico[i], mot) == 0) {
            return 1;
        }
    }
    return 0;
}
