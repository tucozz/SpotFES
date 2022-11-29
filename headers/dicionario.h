#ifndef _DICIONARIO_
#define _DICIONARIO_

#include "lista.h"
#include "types.h"

typedef struct tDicionario Dicionario;

Dicionario *InicializaDicionario(compar_fn comparadorChaves,
                                 free_fn liberaChaves,
                                 free_fn liberaValores);

void LiberaDicionario(Dicionario *dicio);

void **GetValorDicionario(Dicionario *dicio, const void *chave,
                          cpyval_fn copiaChave);

Lista *GetTodosParesDicionario(Dicionario *dicio);

#endif
