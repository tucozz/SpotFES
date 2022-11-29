#ifndef _PAR_CHAVE_VALOR_
#define _PAR_CHAVE_VALOR_

#include "types.h"

typedef struct tParChaveValor ParChaveValor;

ParChaveValor *InicializaParCV(void *chave, void *valor, free_fn liberaChave,
                               free_fn liberaValor);

void LiberaParCV(ParChaveValor *par);

void *GetChaveParCV(ParChaveValor *par);

const void *GetValorParCV(const ParChaveValor *par);

void *SetValorParCV(ParChaveValor *par, void *val);

void **GetPtrValorParCV(ParChaveValor *par);

#endif
