#ifndef DICO_LOADER_H
#define DICO_LOADER_H

extern int dico_size;
char **charger_dictionnaire(const char *filename, int *nb_mots);
void liberer_dictionnaire(char **dico, int nb_mots);

#endif
