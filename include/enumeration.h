#ifndef ENUMERATION_H
#define ENUMERATION_H

#include <stddef.h>

#include "context.h"

typedef struct {
    const word *extent; /* bitset d'objets    (words_per_att mots) */
    const word *intent; /* bitset d'attributs (words_per_obj mots) */
} Concept;

/* Fonction de rappel appelée sur chaque concept énuméré.
   Attention : les bitsets pointés par c peuvent être réutilisés après le
   retour du callback ; il faut les copier pour les conserver. */
typedef void (*concept_cb)(const FormalContext *ctx, const Concept *c, void *user);

/* Chaque fonction retourne le nombre de concepts énumérés (extent non vide). */

/* Algorithme naïf (oracle), pour nb_att petit (m <= 20 en pratique). */
size_t enum_naive(const FormalContext *ctx, concept_cb cb, void *user);

/* In-Close, allocations dynamiques à chaque niveau de récursion. */
size_t enum_inclose(const FormalContext *ctx, concept_cb cb, void *user);

/* In-Close avec une arena (pile mémoire) allouée une seule fois. */
size_t enum_inclose_arena(const FormalContext *ctx, concept_cb cb, void *user);

#endif /* ENUMERATION_H */
