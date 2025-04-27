#ifndef SEARCH_POINTERS_H
#define SEARCH_POINTERS_H

char **creer_tableau_pointeurs(char **dico, int taille);
int rechercher_pointeurs(char **pointeurs, int taille, const char *mot);
void liberer_pointeurs(char **pointeurs);

#endif
