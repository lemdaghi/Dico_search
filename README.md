# Projet Dictionnaire - Analyse de texte en C

---

## Présentation

Ce projet est une application C qui permet d'analyser un texte en français et de détecter les mots non présents dans un dictionnaire donné.

L'analyse est réalisée selon plusieurs méthodes de recherche différentes, afin de **comparer leur efficacité** :

- Recherche séquentielle
- Recherche binaire
- Recherche via tableau de pointeurs triés
- Recherche via table de hachage
- Recherche dans un arbre binaire de recherche (BST)
- Recherche via Trie (arbre préfixe)

Le projet est **entièrement compatible UTF-8** et gère correctement :
- Les accents (`é`, `è`, `à`, `ç`, etc.)
- Les tirets (`-`) pour les mots composés
- L'apostrophe typographique (`’`) pour les contractions ("l’addition")

---

## Organisation des dossiers

```
/Dico
  |- /src                   # Code source .c
  |- /include               # Headers .h
  |- /build                 # Objets compilés (.o)
  |- /dictionnaires         # Fichiers dictionnaires (ex: dico.txt)
  |- /tests                 # Textes à analyser (ex: texte1.txt, texte2.txt)
  |- /results               # Résultats (mots invalides détectés)
  |- Makefile               # Compilation automatique
  |- README.md              # Documentation projet
```

---

## Pré-requis

- Système Linux ou WSL / MacOS
- GCC (compilateur C)
- Locale UTF-8 française (`fr_FR.UTF-8` installée)
- Make installé

---

## Compilation

Pour compiler l'ensemble du projet :

```bash
make
```

Le binaire `projet` sera créé dans le dossier principal `/Dico`.

Pour nettoyer les fichiers objets :

```bash
make clean
```

Pour tout nettoyer (objets + exécutable + dossier build) :

```bash
make fclean
```

---

## Exécution

Le programme prend **deux arguments** :
- Le chemin du fichier dictionnaire
- Le chemin du fichier texte à analyser

**Exemple :**

```bash
./projet data/dico_lower.txt tests/text1.txt
```

➔ Les résultats sont automatiquement stockés dans le dossier `/results/`, avec un fichier séparé pour chaque méthode.

---

## Méthodes d'analyse utilisées

Chaque analyse est réalisée avec plusieurs stratégies de recherche :

| Méthode | Fichier résultat généré |
|:---|:---|
| Recherche séquentielle | `results/invalides_sequentiel.txt` |
| Recherche binaire | `results/invalides_binaire.txt` |
| Recherche avec pointeurs triés | `results/invalides_pointeurs.txt` |
| Recherche via table de hachage | `results/invalides_hash.txt` |
| Recherche via arbre BST | `results/invalides_bst.txt` |
| Recherche via Trie | `results/invalides_trie.txt` |

---

## Points techniques importants

- Support complet UTF-8
- Locale `fr_FR.UTF-8` activée
- Gestion des tirets (`-`) dans les mots composés
- Gestion correcte de l’apostrophe typographique (`’`)
- Respect de la casse : mots transformés en minuscules pour la comparaison
- Comparaison linguistique utilisant `strcoll()` pour respecter l’ordre alphabétique français



⚠️ Note spéciale - Arbre BST

La méthode utilisant un arbre binaire de recherche (BST) fonctionne correctement,
mais le temps de construction de l'arbre peut être très élevé pour des dictionnaires volumineux.
Cela est dû au fait que l'arbre n'est pas équilibré lors de l'insertion (tri déséquilibré),
ce qui peut conduire à une complexité de O(n²).

Les résultats restent valides, mais l'analyse est plus lente comparée aux autres méthodes.
Vous pouvez décomenter le code concernant la méthode BST dans le main et tester avec "dico_lower.txt"

---

## Améliorations possibles

- Optimisation mémoire sur le Trie
- Comparaison graphique des performances entre méthodes (Python/matplotlib)
