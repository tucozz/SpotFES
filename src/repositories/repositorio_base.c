#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "repositorio_base.h"

#include "exception.h"

Lista *CarregaListaStringRepo(char *str) {
    Lista *lista = InicializaLista();

    char *saveptr = NULL, *token = NULL;
    for (token = str;; token = NULL) {
        token = strtok_r(token, "|", &saveptr);
        if (token == NULL)
            break;

        char *e = strdup(token);
        if (e == NULL)
            throwOutOfMemoryException(
                "RepositorioBase internal CarregaListaStringRepo token strdup "
                "failed");

        AdicionaElementoLista(lista, e);
    }

    return lista;
}

void NormalizaString(char *str) {
    for (; *str; ++str)
        *str = tolower(*str);
}
