#include <stdbool.h>
#include <stdlib.h>

#include "dicionario.h"

#include "exception.h"
#include "par_chave_valor.h"

struct tDicionario {
    Lista *pares; // Lista<ParChaveValor<void*, void*>>
    int (*comparadorChaves)(void *, void *);
    void (*liberaChaves)(void *);
    void (*liberaValores)(void *);
};

Dicionario *InicializaDicionario(int (*comparadorChaves)(void *, void *),
                                 void (*liberaChaves)(void *),
                                 void (*liberaValores)(void *)) {
    Dicionario *dicio = malloc(sizeof *dicio);
    if (dicio == NULL)
        throwOutOfMemoryException("Dicionario malloc failed");

    dicio->pares = InicializaLista(dicio->pares);
    dicio->comparadorChaves = comparadorChaves;
    dicio->liberaChaves = liberaChaves;
    dicio->liberaValores = liberaValores;

    return dicio;
}

void LiberaDicionario(Dicionario *dicio) {
    LiberaLista(dicio->pares, &LiberaParCV);

    free(dicio);
}

void **GetValorDicionario(Dicionario *dicio, const void *chave,
                          void *(*copiaChave)(void *)) {
    int n = GetQuantidadeLista(dicio->pares);

    void **val = NULL; // Ponteiro para o ponteiro do valor
    bool hasFound = false;

    int i;
    for (i = 0; i < n && !hasFound; i++) {
        ParChaveValor *curr = AdquireElementoLista(
            dicio->pares, i); // ParChaveValor<void*, void*>
        void *currChave = GetChaveParCV(curr);
        if (dicio->comparadorChaves(currChave, chave) == 0) {
            val = GetPtrValorParCV(curr);
            hasFound = true;
        }
    }

    if (!hasFound) {
        char *cpy_chave = (*copiaChave)(chave);
        if (cpy_chave == NULL)
            throwOutOfMemoryException(
                "Dicionario internal GetValorDicionario chave copy failed");

        ParChaveValor *novo = InicializaParCV(
            cpy_chave, NULL, dicio->liberaChaves, dicio->liberaValores);

        AdicionaElementoLista(dicio->pares, novo);

        val = GetPtrValorParCV(novo);
    }

    return val;
}

Lista *GetTodosParesDicionario(Dicionario *dicio) { return dicio->pares; }
