/* Fonctions utilitaires FOURNIES pour la lecture de fichiers. Ne pas modifier. */

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "read_utils.h"

int read_line(FILE *f, char **line, size_t *capacity)
{
    size_t len = 0;
    int c;

    if (*line == NULL || *capacity == 0) {
        *capacity = 128;
        *line = malloc(*capacity);
        if (*line == NULL)
            return -1;
    }

    while ((c = fgetc(f)) != EOF) {
        if (c == '\n')
            break;

        if (len + 1 >= *capacity) {
            if (*capacity > SIZE_MAX / 2)
                return -1;

            size_t new_capacity = *capacity * 2;
            char *tmp = realloc(*line, new_capacity);

            if (tmp == NULL)
                return -1;

            *line = tmp;
            *capacity = new_capacity;
        }

        (*line)[len++] = (char)c;
    }

    if (c == EOF && ferror(f))
        return -1;

    if (c == EOF && len == 0)
        return 0;

    /* Supprimer le '\r' des fichiers Windows CRLF. */
    if (len > 0 && (*line)[len - 1] == '\r')
        len--;

    (*line)[len] = '\0';
    return 1;
}

int is_blank_line(const char *s)
{
    while (*s != '\0') {
        if (!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}

int parse_size(const char *s, size_t *value)
{
    char *end;
    uintmax_t n;

    while (isspace((unsigned char)*s))
        s++;

    if (*s == '\0' || *s == '-')
        return 0;

    n = strtoumax(s, &end, 10);

    if (end == s || n > SIZE_MAX)
        return 0;

    while (isspace((unsigned char)*end))
        end++;

    if (*end != '\0')
        return 0;

    *value = (size_t)n;
    return 1;
}

char *duplicate_string(const char *s)
{
    size_t len = strlen(s);

    if (len == SIZE_MAX)
        return NULL;

    char *copy = malloc(len + 1);

    if (copy != NULL)
        memcpy(copy, s, len + 1);

    return copy;
}
