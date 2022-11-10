#include <stdio.h>
#include <stdlib.h>

#include "app.h"

#include "repositorio_musicas.h"

int main(int argc, char *argv[]) {
    /* if (argc != 3)
        return EXIT_FAILURE;

    App *app = InicializaApp(argv[1], argv[2]);

    RodaApp(app);

    LiberaApp(app); */

    RepoMusicas *repo = InicializaRepoMusicas(argv[1]);

    Lista *lista = EncontraPeloNomeRepoMusica(repo, "baby");

    LiberaLista(lista, &LiberaMusica);
    LiberaRepoMusicas(repo);

    return EXIT_SUCCESS;
}
