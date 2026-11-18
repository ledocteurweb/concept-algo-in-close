# Projet C : In-Close (énumération des concepts formels)

Binôme : _noms_ — Groupe : _n°_

## Organisation du dépôt

| Chemin | Rôle |
|---|---|
| `include/` | en-têtes : `bitset.h`, `context.h`, `enumeration.h`, `read_utils.h` |
| `src/read_utils.c` | fonctions utilitaires **fournies** (ne pas modifier) |
| `src/context.c` | `ctx_read`, `ctx_free` |
| `src/enum_naive.c` | énumération naïve (oracle) |
| `src/enum_inclose.c` | In-Close, allocations dynamiques |
| `src/enum_inclose_arena.c` | In-Close avec arena |
| `tests/compare.c` | programme de comparaison / validation |
| `data/` | contextes de test (`fil_rouge.ctx`, résultat attendu) |

## Compilation et exécution

    make          # produit bin/compare
    make test     # lance bin/compare sur data/fil_rouge.ctx
    make clean

## Rapport

### Choix d'implémentation
### Validation
### Performances
### Bitset vs tableau d'indices triés
