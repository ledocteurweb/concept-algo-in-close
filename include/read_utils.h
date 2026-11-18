#ifndef READ_UTILS_H
#define READ_UTILS_H

#include <stddef.h>
#include <stdio.h>

/* Fonctions utilitaires FOURNIES pour faciliter la lecture d'un fichier.
   (Ne pas modifier.) */

/* Lit une ligne de longueur quelconque dans *line (tampon alloué/agrandi
   automatiquement, de capacité *capacity ; à libérer avec free par
   l'appelant). Le '\n' final et un éventuel '\r' sont supprimés.
   Retourne 1 en cas de succès, 0 en fin de fichier, -1 en cas d'erreur. */
int read_line(FILE *f, char **line, size_t *capacity);

/* Retourne 1 si la ligne est vide ou ne contient que des espaces, 0 sinon. */
int is_blank_line(const char *s);

/* Convertit une chaîne en size_t (entier décimal positif, espaces autorisés
   autour). Retourne 1 en cas de succès, 0 sinon. */
int parse_size(const char *s, size_t *value);

/* Retourne une copie allouée de s (à libérer avec free), ou NULL. */
char *duplicate_string(const char *s);

#endif /* READ_UTILS_H */
