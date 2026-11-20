#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "context.h"
#include "read_utils.h"

static FormalContext* fail(char* line, FormalContext* ctx)
{
    free(line);
    ctx_free(ctx);
    return NULL;
}

/* TODO : libérer noms, matrice d'incidence et structure. */
void ctx_free(FormalContext* ctx)
{
    
    free(ctx);
    (void)ctx;
}

/* TODO : lire un contexte au format Burmeister (voir le sujet).
   Indications :
   - utiliser read_line, is_blank_line, parse_size, duplicate_string ;
   - le bit de l'objet i pour l'attribut j se trouve dans
     incidence[j * words_per_att + i / WORD_BITS], au rang i % WORD_BITS ;
   - en cas d'erreur : message sur stderr, libérer tout ce qui a été alloué, retourner NULL. */
/* Libère le tampon de ligne et le contexte (éventuellement NULL ou partiel). */
FormalContext* ctx_read(FILE* f)
{
    char* line = NULL;
    size_t capacity = 0;
    size_t nb_obj, nb_att;
    FormalContext* ctx = NULL;

    /* 1. Marqueur Burmeister */
    if (read_line(f, &line, &capacity) != 1 || strcmp(line, "B") != 0) {
        fprintf(stderr, "Erreur : marqueur Burmeister invalide.\n");
        return fail(line, ctx);
    }

    /* 2. Ligne vide après le marqueur */
    if (read_line(f, &line, &capacity) != 1 || !is_blank_line(line)) {
        fprintf(stderr, "Erreur : ligne vide attendue après B.\n");
        return fail(line, ctx);
    }

    /* 3. Nombre d'objets */
    if (read_line(f, &line, &capacity) != 1 || !parse_size(line, &nb_obj)) {
        fprintf(stderr, "Erreur : nombre d'objets invalide.\n");
        return fail(line, ctx);
    }

    /* 4. Nombre d'attributs */
    if (read_line(f, &line, &capacity) != 1 || !parse_size(line, &nb_att)) {
        fprintf(stderr, "Erreur : nombre d'attributs invalide.\n");
        return fail(line, ctx);
    }

    /* 5. Ligne vide après les dimensions */
    if (read_line(f, &line, &capacity) != 1 || !is_blank_line(line)) {
        fprintf(stderr, "Erreur : ligne vide attendue après les dimensions.\n");
        return fail(line, ctx);
    }

    /* 6. Création du contexte (À COMPLÉTER)
     *
     * À partir de nb_obj et nb_att :
     *  - allouer la structure *ctx et renseigner ctx->nb_obj et ctx->nb_att
     *    immédiatement (pour que ctx_free fonctionne si la suite échoue) ;
     *  - calculer ctx->nb_word_obj et ctx->nb_word_att ;
     *  - allouer et mettre à zéro les tableaux ctx->obj_names, ctx->att_names
     *    et ctx->incidence (nb_att * nb_word_obj mots), sans oublier le cas
     *    où une dimension vaut 0 ;
     *  - en cas d'échec ou de dimensions trop grandes : message sur stderr,
     *    puis  return fail(line, ctx);
     */
    /* TODO */
ctx = calloc(1,sizeof(FormalContext));
    if(ctx==NULL){
        fprintf(stderr, "Erreur d'allocation \n");
        return fail(line, ctx);
    }

    ctx->nb_obj = nb_obj;
    ctx->nb_att=nb_att;
    ctx->nb_word_att=nb_att / 64 + (nb_att%64 !=0);
    ctx->nb_word_obj=nb_obj / 64 + (nb_obj%64 !=0);

    if(nb_obj == 0){
        ctx->obj_names = calloc(1,sizeof(char*));
    }
    else{
        ctx->obj_names=calloc(nb_obj,sizeof(char*));
    }

    if(ctx->obj_names==0){
        fprintf(stderr, "Erreur d'allocation \n");
        return fail(line, ctx);      
    }




    if(nb_att == 0 ){
        ctx->att_names = calloc(1,sizeof(char*))
    }
    else{
        ctx->att_names=calloc(nb_att,sizeof(char*));
    }
    if(ctx->att_names==NULL){
        fprintf(stderr, "Erreur d'allocation \n");
        return fail(line, ctx);      
    } 

    //Verification de la taille max qu'on devra utiliser comme premier argument dans notre calloc si le produit dépasse la valeur max de sizeof on renvoie une erreur 
    if (ctx->nb_word_obj != 0 &&
        nb_att > SIZE_MAX / sizeof(word) / ctx->nb_word_obj) {
        fprintf(stderr, "Dimensions trop grandes\n");
        return fail(line, ctx);
    }

    size_t n = ctx->nb_att*ctx->nb_word_obj;
    if(n==0){
        ctx->incidence = calloc(1 , sizeof(word));
    }
    else{
        ctx->incidence = calloc(n, sizeof(word));
    }
    if(ctx->incidence==NULL){
        fprintf(stderr, "Erreur d'allocation \n");
        return fail(line, ctx);      
    } 


    
    

    /* 7. Noms des objets */
    for (size_t i = 0; i < nb_obj; i++) {
        if (read_line(f, &line, &capacity) != 1) {
            fprintf(stderr, "Erreur : nom d'objet manquant.\n");
            return fail(line, ctx);
        }
        /* TODO : stocker une copie de `line` dans ctx->obj_names[i]
           (échec d'allocation => message + return fail(line, ctx);) */
        ctx->obj_names[j]=malloc(strlen(line)+1);
            if(ctx->obj_names[j]==NULL){
                fprintf(stderr, "Erreur d'allocation \n");
                return fail(line, ctx);      
            } 
        strcpy(ctx->obj_names[j],line);
    }

    /* 8. Noms des attributs */
    for (size_t j = 0; j < nb_att; j++) {
        if (read_line(f, &line, &capacity) != 1) {
            fprintf(stderr, "Erreur : nom d'attribut manquant.\n");
            return fail(line, ctx);
        }
        /* TODO : stocker une copie de `line` dans ctx->att_names[j] */
        ctx->att_names[j]=malloc(strlen(line)+1);
            if(ctx->att_names[j]==NULL){
                fprintf(stderr, "Erreur d'allocation \n");
                return fail(line, ctx);      
            } 
        strcpy(ctx->att_names[j],line);
    }

    /* 9. Matrice d'incidence : une ligne par objet, un caractère par attribut
          ('X' : l'objet i possède l'attribut j, '.' : il ne l'a pas) */
    for (size_t i = 0; i < nb_obj; i++) {
        if (read_line(f, &line, &capacity) != 1) {
            fprintf(stderr, "Erreur : ligne d'incidence manquante.\n");
            return fail(line, ctx);
        }
        if (strlen(line) != nb_att) {
            fprintf(stderr, "Erreur : longueur incorrecte pour l'objet %zu.\n", i);
            return fail(line, ctx);
        }
        for (size_t j = 0; j < nb_att; j++) {
            if (line[j] == 'X') {
                /* TODO : mettre à 1 le bit de l'objet i dans l'extent
                   de l'attribut j (dans ctx->incidence) */
                ctx->incidence[j*ctx->nb_word_obj + i/64] |= ((word)1 << (i%64));
            } else if (line[j] != '.') {
                fprintf(stderr,
                    "Erreur : caractère '%c' invalide pour l'objet %zu, attribut %zu.\n",
                    line[j], i, j);
                return fail(line, ctx);
            }
        }
    }

    free(line);
    return ctx;
}
