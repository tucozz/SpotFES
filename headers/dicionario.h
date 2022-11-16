#ifndef _DICIONARIO_
#define _DICIONARIO_

#include "lista.h";

typedef struct tDicionario Dicionario;

Dicionario *InicializaDicionario(int (*comparador)(void *, void *));

void LiberaDicionario(Dicionario *dicio, void (*liberaChaves)(void *),
                      void (*liberaValores)(void *));

void *GetValor(Dicionario *dicio, void *hash);

Lista *GetTodosValores(Dicionario *dicio);

Lista *GetTodasChaves(Dicionario *dicio);

#endif
