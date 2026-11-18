#include "enumeration.h"

/* TODO : In-Close avec une arena allouée une seule fois
   (capacité suffisante pour une branche : nb_att + 1 niveaux). */
size_t enum_inclose_arena(const FormalContext *ctx, concept_cb cb, void *user)
{
    (void)ctx; (void)cb; (void)user;
    return 0;
}
