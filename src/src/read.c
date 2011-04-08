#define SAC_DO_COMPILE_MODULE 1
#define SAC_MUTC_MACROS  1
#define SAC_BACKEND muTC

#include "svp/fibre.h"
#include "sac.h"
#include <stdlib.h>
#include "svp/abort.h"

static int FibreCount = 0;

#define UNTYPED( type)                                                  \
void read_##type( SAC_ND_PARAM_out( res##type##_nt, type)){             \
  int i;                                                                \
  size_t *shape;                                                        \
                                                                        \
  SAC_ND_DECL__DESC( local##type##_nt, );                               \
  SAC_ND_DECL__DATA( local##type##_nt, type, );                         \
  int SAC_ND_A_MIRROR_DIM( local##type##_nt);                           \
  int SAC_ND_A_MIRROR_SIZE( local##type##_nt) = 1;                      \
                                                                        \
  SAC_ND_A_MIRROR_DIM( local##type##_nt) = fibre_rank( FibreCount);     \
  shape = (size_t *)fibre_shape( FibreCount);                           \
                                                                        \
  SAC_ND_ALLOC__DESC( local##type##_nt,                                 \
                     SAC_ND_A_MIRROR_DIM( local##type##_nt));           \
  SAC_ND_A_RC( local##type##_nt) = 1;                                   \
                                                                        \
  SAC_ND_A_DESC_DIM( local##type##_nt) =                                \
    SAC_ND_A_MIRROR_DIM( local##type##_nt);                             \
                                                                        \
  for ( i = 0; i < SAC_ND_A_DIM( local##type##_nt); i++){               \
    SAC_ND_A_MIRROR_SIZE( local##type##_nt) =                           \
      SAC_ND_A_MIRROR_SIZE( local##type##_nt) * (int)shape[i];          \
    SAC_ND_A_DESC_SHAPE( local##type##_nt, i) = (int)shape[i];          \
  }                                                                     \
                                                                        \
  SAC_ND_A_DESC_SIZE( local##type##_nt) =                               \
    SAC_ND_A_MIRROR_SIZE( local##type##_nt);                            \
                                                                        \
  SAC_ND_ALLOC__DATA( local##type##_nt);                                \
                                                                        \
  /* copy and change type  */                                           \
  for ( i=0; i < SAC_ND_A_SIZE( local##type##_nt); i++){                \
    switch ( fibre_tag( FibreCount)){                                   \
    case 0:                                                             \
      SAC_ND_A_FIELD( local##type##_nt)[i] =                            \
        (type )(((unsigned long*)fibre_data( FibreCount))[i]);          \
      break;                                                            \
    case 1:                                                             \
      SAC_ND_A_FIELD( local##type##_nt)[i] =                            \
        (type )(((long*)fibre_data( FibreCount))[i]);                   \
      break;                                                            \
    case 2:                                                             \
      SAC_ND_A_FIELD( local##type##_nt)[i] =                            \
        (type )(((double*)fibre_data( FibreCount))[i]);                 \
      break;                                                            \
    default:                                                            \
      svp_abort();                                                      \
      break;                                                            \
    }                                                                   \
  }                                                                     \
  FibreCount++;                                                         \
  SAC_ND_RET_out( res##type##_nt, local##type##_nt);                    \
}


#define resint_nt (res, (AUD, (NHD, (NUQ, (INT, (GLO, (FPA, )))))))
#define resfloat_nt (res, (AUD, (NHD, (NUQ, (FLO, (GLO, (FPA, )))))))
#define resdouble_nt (res, (AUD, (NHD, (NUQ, (FLO, (GLO, (FPA, )))))))

#define localint_nt (local, (AUD, (NHD, (NUQ, (INT, (GLO, (FPA, )))))))
#define localfloat_nt (local, (AUD, (NHD, (NUQ, (FLO, (GLO, (FPA, )))))))
#define localdouble_nt (local, (AUD, (NHD, (NUQ, (FLO, (GLO, (FPA, )))))))

UNTYPED( int)
UNTYPED( float)
UNTYPED( double)

