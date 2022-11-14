#include <stdlib.h>

#include "lista.h"

static const int ritmo_crescimento_lista = 5;

struct tLista {
    int capacidade;
    int qtd;
    void **arr;
};

Lista *InicializaLista() {
    Lista *lista = malloc(sizeof *lista);

    const int capacidade_inicial = 5;

    lista->capacidade = capacidade_inicial;
    lista->qtd = 0;
    lista->arr = malloc(lista->capacidade * __SIZEOF_POINTER__);

    return lista;
}

void LiberaLista(Lista *lista, void (*liberaElem)(void *)) {
    for (int i = 0; i < lista->qtd; i++)
        (*liberaElem)(lista->arr[i]);

    free(lista->arr);

    free(lista);
}

int GetQuantidadeLista(const Lista *lista) { return lista->qtd; }

void *AdquireElementoLista(Lista *lista, int i) {
    if (i < 0 || i >= lista->qtd)
        return NULL;

    return lista->arr[i];
}

void AdicionaElementoLista(Lista *lista, void *elem) {
    if (lista->qtd == lista->capacidade) {
        lista->capacidade += ritmo_crescimento_lista;
        lista->arr =
            realloc(lista->arr, lista->capacidade * __SIZEOF_POINTER__);
    }

    lista->arr[lista->qtd++] = elem;
}

void *PopLista(Lista *lista) {
    if (lista->qtd < (lista->capacidade - 2 * ritmo_crescimento_lista)) {
        lista->capacidade -= ritmo_crescimento_lista;
        lista->arr =
            realloc(lista->arr, lista->capacidade * __SIZEOF_POINTER__);
    }

    void *r = lista->arr[lista->qtd - 1];
    lista->arr[lista->qtd - 1] = NULL;
    lista->qtd--;

    return r;
}

Lista *CopiaLista(const Lista * lista, void *(*cpyelem)(const void *)) {
    Lista *cpy = InicializaLista();

    int i;
    for (i = 0; i < lista->qtd; i++)
        AdicionaElementoLista(cpy, cpyelem(lista->arr[i]));

    return cpy;
}
