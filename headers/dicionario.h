#ifndef _DICIONARIO_
#define _DICIONARIO_

#include "lista.h";

typedef struct tDicionario Dicionario;

Dicionario *InicializaDicionario(int (*comparadorChaves)(void *, void *),
                                 void (*liberaChaves)(void *),
                                 void (*liberaValores)(void *));

void LiberaDicionario(Dicionario *dicio);

void **GetValorDicionario(Dicionario *dicio, const void *chave,
                          void *(*copiaChave)(void *));

Lista *GetTodosParesDicionario(Dicionario *dicio);

#endif
