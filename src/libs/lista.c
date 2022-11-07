#include <stdlib.h>

#include "lista.h"

struct tLista {
    int capacidade;
    int qtd;
    void **arr;
};

Lista *InicializaLista() {

}

void *LiberaLista(Lista *lista) {

}

void AdicionaElementoLista(Lista *lista, void *elem) {

}

void *PopLista(Lista *lista) {
    void *r = lista->arr[lista->qtd - 1];
    lista->arr[lista->qtd - 1] = NULL;
    lista->qtd--;

    return r;
}