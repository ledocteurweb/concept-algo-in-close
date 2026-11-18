/* Exécutable de test : compare enum_naive, enum_inclose et enum_inclose_arena.
   TODO :
   - générer des contextes aléatoires (petits, densité variable) ;
   - collecter les concepts de chaque algorithme (via le callback / `user`) ;
   - vérifier que les trois ensembles de concepts sont identiques (indépendamment de l'ordre) ;
   - mesurer et afficher les temps d'exécution (clock_gettime). */

#include <stdio.h>

#include "context.h"
#include "enumeration.h"

int main(int argc, char *argv[])
{
    const char *filename = argc > 1 ? argv[1] : "data/fil_rouge.ctx";
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror(filename);
        return 1;
    }

    FormalContext *ctx = ctx_read(f);
    fclose(f);
    if (ctx == NULL) {
        fprintf(stderr, "ctx_read a échoué (ou n'est pas encore implémentée)\n");
        return 1;
    }

    /* TODO : appeler les trois énumérations et comparer */

    ctx_free(ctx);
    return 0;
}
