#include <stdlib.h>
#include <string.h>

#include "repositorio_base.h"

Lista *CarregaListaStringRepo(char *str) {
    Lista *lista = InicializaLista();

    char *saveptr = NULL, *token = NULL;
    for (token = str;; token = NULL) {
        token = strtok_r(token, "|", &saveptr);
        if (token == NULL)
            break;

        AdicionaElementoLista(lista, strdup(token));
    }

    return lista;
}
