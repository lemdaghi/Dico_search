#ifndef ANALYSEUR_H
#define ANALYSEUR_H

typedef int (*fonction_recherche)(void *structure, const char *mot);

void analyser_texte(const char *nom_texte, const char *nom_sortie,
                    void *structure, fonction_recherche recherche);

#endif
