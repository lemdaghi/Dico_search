#include "utils.h"
#include <ctype.h>
#include <time.h>
#include <string.h>

#define MAX_MOT 128

double chrono() {
    return (double)clock() / CLOCKS_PER_SEC;
}

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

void to_lowercase(char *mot) {
    for (int i = 0; mot[i]; i++) {
        if (mot[i] >= 'A' && mot[i] <= 'Z') {
            mot[i] = mot[i] + ('a' - 'A');
        }
        // Les accents (UTF-8) sont laissés tranquilles
    }
}

#include <string.h>

void simplifier_mot(const char *entree, char *sortie) {
    int i = 0, j = 0;
    while (entree[i]) {
        // Traitement naïf : si le caractère est simple ASCII, copie direct
        if ((unsigned char)entree[i] < 128) {
            sortie[j++] = entree[i++];
        }
        else {
            // Traitement spécial pour caractères accentués simples connus
            if ((unsigned char)entree[i] == 0xC3) {
                i++;
                switch ((unsigned char)entree[i]) {
                    case 0xA0: case 0xA1: case 0xA2: case 0xA3: case 0xA4: case 0xA5: // à á â ã ä å
                        sortie[j++] = 'a'; break;
                    case 0xA7: // ç
                        sortie[j++] = 'c'; break;
                    case 0xA8: case 0xA9: case 0xAA: case 0xAB: // è é ê ë
                        sortie[j++] = 'e'; break;
                    case 0xAC: case 0xAD: case 0xAE: case 0xAF: // ì í î ï
                        sortie[j++] = 'i'; break;
                    case 0xB1: // ñ
                        sortie[j++] = 'n'; break;
                    case 0xB2: case 0xB3: case 0xB4: case 0xB5: case 0xB6: // ò ó ô õ ö
                        sortie[j++] = 'o'; break;
                    case 0xB9: case 0xBA: case 0xBB: case 0xBC: // ù ú û ü
                        sortie[j++] = 'u'; break;
                    case 0xBD: case 0xBE: // ý ÿ
                        sortie[j++] = 'y'; break;
                    case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: // À Á Â Ã Ä Å
                        sortie[j++] = 'A'; break;
                    case 0x87: // Ç
                        sortie[j++] = 'C'; break;
                    case 0x88: case 0x89: case 0x8A: case 0x8B: // È É Ê Ë
                        sortie[j++] = 'E'; break;
                    case 0x8C: case 0x8D: case 0x8E: case 0x8F: // Ì Í Î Ï
                        sortie[j++] = 'I'; break;
                    case 0x91: // Ñ
                        sortie[j++] = 'N'; break;
                    case 0x92: case 0x93: case 0x94: case 0x95: case 0x96: // Ò Ó Ô Õ Ö
                        sortie[j++] = 'O'; break;
                    case 0x99: case 0x9A: case 0x9B: case 0x9C: // Ù Ú Û Ü
                        sortie[j++] = 'U'; break;
                    case 0x9D: // Ý
                        sortie[j++] = 'Y'; break;
                    default:
                        // Caractère non reconnu ➔ on l'ignore ou copie ?
                        sortie[j++] = '?'; // optionnel : marquer
                        break;
                }
                i++;
            } else {
                // Caractère UTF-8 inconnu ➔ ignorer ou copier ?
                sortie[j++] = '?'; // à adapter si besoin
                i++;
            }
        }
    }
    sortie[j] = '\0';
}

int comparer_mots_francais(const char *mot1, const char *mot2) {
    char simplifie1[MAX_MOT];
    char simplifie2[MAX_MOT];

    simplifier_mot(mot1, simplifie1);
    simplifier_mot(mot2, simplifie2);

    int res = strcoll(simplifie1, simplifie2);
    if (res != 0) return res;  // pas égal

    // Si simplifiés égaux, confirmer avec strcmp sur mots originaux
    return strcmp(mot1, mot2);
}

