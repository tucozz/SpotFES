#include <stdlib.h>

#include "lista.h"

#include "cpylib.h"
#include "exception.h"

static const int ritmo_crescimento_lista = 5;

struct tLista {
    int capacidade;
    int qtd;
    void **arr;
};

Lista *InicializaLista() {
    Lista *lista = malloc(sizeof *lista);
    if (lista == NULL)
        throwOutOfMemoryException("Lista malloc failed");

    const int capacidade_inicial = 5;

    lista->capacidade = capacidade_inicial;
    lista->qtd = 0;
    lista->arr = malloc(lista->capacidade * __SIZEOF_POINTER__);
    if (lista->arr == NULL)
        throwOutOfMemoryException("Lista internal arr malloc failed");

    return lista;
}

void LiberaLista(Lista *lista, void (*liberaElem)(void *)) {
    for (int i = 0; i < lista->qtd; i++)
        (*liberaElem)(lista->arr[i]);

    free(lista->arr);

    free(lista);
}

static int (*gcmpval)(const void *, const void *) = NULL;

static inline int ptrvalcmp(const void **ptr1, const void **ptr2) {
    if (gcmpval == NULL)
        return 0;

    return gcmpval(*ptr1, *ptr2);
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
        if (lista->arr == NULL)
            throwOutOfMemoryException("Lista internal arr up realloc failed");
    }

    lista->arr[lista->qtd++] = elem;
}

void *PopLista(Lista *lista) {
    if (lista->qtd < (lista->capacidade - 2 * ritmo_crescimento_lista)) {
        lista->capacidade -= ritmo_crescimento_lista;
        lista->arr =
            realloc(lista->arr, lista->capacidade * __SIZEOF_POINTER__);
        if (lista->arr)
            throwOutOfMemoryException("Lista internal arr down realloc failed");
    }

    void *r = lista->arr[lista->qtd - 1];
    lista->arr[lista->qtd - 1] = NULL;
    lista->qtd--;

    return r;
}

int EncontraLista(Lista *lista, void *alvo,
                  int (*cmpElem)(const void *, const void *)) {
    int n = GetQuantidadeLista(lista);
    for (int i = 0; i < n; i++)
        if (cmpElem(lista->arr[i], alvo) == 0)
            return i;

    return -1;
}

void OrdenaLista(Lista *lista, int (*cmpElem)(const void *, const void *)) {
    gcmpval = cmpElem;
    qsortcpy(lista->arr, lista->qtd, __SIZEOF_POINTER__, &ptrvalcmp);
    gcmpval = NULL;
}

Lista *CopiaLista(const Lista *lista, void *(*cpyelem)(const void *)) {
    Lista *cpy = InicializaLista();

    int i;
    for (i = 0; i < lista->qtd; i++) {
        void *cpye = cpyelem(lista->arr[i]);
        if (cpye == NULL)
            throwOutOfMemoryException(
                "Lista internal CopiaLista cpyelem failed");

        AdicionaElementoLista(cpy, cpye);
    }

    return cpy;
}
