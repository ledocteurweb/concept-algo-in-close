#ifndef CONTEXT_H
#define CONTEXT_H

#include <stddef.h>
#include <stdio.h>

#include "bitset.h"

typedef struct {
    size_t nb_obj; /* nombre d'objets */
    size_t nb_att; /* nombre d'attributs */

    /* Nombre de mots pour représenter un attribut
    (= un bitset sur les objets, i.e. un extent : ceil(nb_obj / WORD_BITS)) */
    size_t nb_word_obj;

    /* Nombre de mots pour représenter un objet
    (= un bitset sur les attributs, i.e. un intent : ceil(nb_att / WORD_BITS)) */
    size_t nb_word_att;

    /* Matrice d'incidence binaire "transposée" :
       incidence[i*words_per_att] représente l'attribut i */
    word* incidence;

    /* Noms des objets et des attributs (facultatifs) */
    char** obj_names; /* obj_names[j] : le nom de l'objet j */
    char** att_names; /* att_names[i] : le nom de l'attribut i */
} FormalContext;

/* Lit un contexte formel au format Burmeister.
   Retourne NULL en cas d'erreur. */
FormalContext* ctx_read(FILE* f);

/* Libère la mémoire occupée par un contexte (ctx peut être NULL). */
void ctx_free(FormalContext* ctx);

#endif /* CONTEXT_H */
