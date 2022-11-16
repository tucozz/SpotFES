#include <stdlib.h>
#include <stdbool.h>

#include "dicionario.h"

struct tDicionario {
    Lista *chaves;
    Lista *valores;
    int (*comparadorChaves)(void *, void *);
};

Dicionario *InicializaDicionario(int (*comparadorChaves)(void *, void *)) {
    Dicionario *dicio = malloc(sizeof *dicio);

    InicializaLista(dicio->chaves);
    InicializaLista(dicio->valores);
    dicio->comparadorChaves = comparadorChaves;

    return dicio;
}

void LiberaDicionario(Dicionario *dicio, void (*liberaChaves)(void *),
                      void (*liberaValores)(void *)) {
    LiberaLista(dicio->chaves, &liberaChaves);
    LiberaLista(dicio->valores, &liberaValores);

    free(dicio);
}

void *GetValor(Dicionario *dicio, void *hash) {
    int n = GetQuantidadeLista(dicio->chaves);

    void *val = NULL;
    bool hasFound = false;

    int i;
    for (i = 0; i < n; i++) {
        void *curr = AdquireElementoLista(dicio->chaves, i);
        if (dicio->comparadorChaves(curr, hash) == 0) {
            val = curr;
            hasFound = true;
        }
    }

    if (!hasFound) {
        // TODO: ponteiro para função (?)
    }
    
    return val;
}

Lista *GetTodasChaves(Dicionario *dicio) { return dicio->chaves; }

Lista *GetTodosValores(Dicionario *dicio) { return dicio->valores; }
