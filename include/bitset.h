#ifndef BITSET_H
#define BITSET_H

#include <limits.h>
#include <stdint.h>

/* Un bitset est un tableau de "word". */
typedef uint64_t word;

/* Taille d'un mot en bits */
#define WORD_BITS (sizeof(word) * CHAR_BIT)

/* Mot dont tous les bits valent 1 */
#define WORD_MAX (~((word)0))

#endif /* BITSET_H */
