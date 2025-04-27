#include "analyseur.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define MAX_MOT 256
#define MAX_LIGNE 2048

// Fonction pour déterminer si un caractère est acceptable
int est_debut_utf8(unsigned char c) {
    return (c >= 192);
}

// Détermine combien d'octets un caractère UTF-8 utilise
int taille_utf8(unsigned char c) {
    if (c < 128) return 1;         // ASCII simple
    else if ((c >> 5) == 0x6) return 2;  // 110xxxxx
    else if ((c >> 4) == 0xE) return 3;  // 1110xxxx
    else if ((c >> 3) == 0x1E) return 4; // 11110xxx
    else return 1;  // Erreur, mais on continue (sécurité)
}

int est_caractere_valide(unsigned char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '-'))
        return 1;
    if (c == '\'') // Apostrophe ASCII (') → considérer comme coupure
        return 0;
    if (c == 0xE2) // Apostrophe typographique ‘ ou ’
        return 0;
    if (c >= 192)
        return 1;
    return 0;
}

void analyser_texte(const char *nom_texte, const char *nom_sortie,
    void *structure, fonction_recherche recherche)
{
    FILE *f_texte = fopen(nom_texte, "r");
    FILE *f_sortie = fopen(nom_sortie, "w");
    if (!f_texte || !f_sortie) {
        perror("Erreur ouverture fichier");
        return;
    }

    setlocale(LC_ALL, "fr_FR.UTF-8");

    char ligne[MAX_LIGNE];
    char mot[MAX_MOT];
    int idx;

    while (fgets(ligne, sizeof(ligne), f_texte)) {
        idx = 0;
        for (int i = 0; ligne[i] != '\0';) {
            unsigned char c = (unsigned char)ligne[i];

            if (est_caractere_valide(c)) {
                int len = taille_utf8(c);  // combien d'octets pour ce caractère ?

                if (idx + len < MAX_MOT) {
                    for (int j = 0; j < len; j++) {
                        mot[idx++] = ligne[i++];
                    }
                } else {
                    i += len;  // éviter débordement
                }
            } else {
                if (idx > 0) {
                    mot[idx] = '\0';
                    to_lowercase(mot);

                    if (!recherche(structure, mot)) {
                        fprintf(f_sortie, "%s\n", mot);
                    }
                    idx = 0;
                }
                i++;
            }
        }

        if (idx > 0) {
            mot[idx] = '\0';
            to_lowercase(mot);

            if (!recherche(structure, mot)) {
                fprintf(f_sortie, "%s\n", mot);
            }
        }
    }

    fclose(f_texte);
    fclose(f_sortie);
}

// void analyser_texte(const char *nom_texte, const char *nom_sortie,
//     void *structure, fonction_recherche recherche)
// {
//     FILE *f_texte = fopen(nom_texte, "r");
//     FILE *f_sortie = fopen(nom_sortie, "w");
//     if (!f_texte || !f_sortie) {
//         perror("Erreur ouverture fichier");
//         return;
//     }

//     setlocale(LC_CTYPE, "fr_FR.UTF-8");

//     char ligne[MAX_LIGNE];
//     char mot[MAX_MOT];
//     int idx;

//     while (fgets(ligne, sizeof(ligne), f_texte)) {
//         idx = 0;
//         for (int i = 0; ligne[i] != '\0'; ++i) {
//             unsigned char c = (unsigned char)ligne[i];

//             // Accepter lettres (ASCII) ou tiret ou caractères UTF-8 étendus
//             if (isalpha(c) || c == '-' || c >= 192) {
//                 if (idx < MAX_MOT - 1) {
//                     mot[idx++] = c;
//                 }
//             } else {
//                 if (idx > 0) {
//                     mot[idx] = '\0';
//                     to_lowercase(mot);

//                     if (!recherche(structure, mot)) {
//                         fprintf(f_sortie, "%s\n", mot);
//                     }
//                     idx = 0;
//                 }
//             }
//         }
//         // Si un mot à la fin de la ligne
//         if (idx > 0) {
//             mot[idx] = '\0';
//             to_lowercase(mot);

//             if (!recherche(structure, mot)) {
//                 fprintf(f_sortie, "%s\n", mot);
//             }
//         }
//     }

//     fclose(f_texte);
//     fclose(f_sortie);
// }
