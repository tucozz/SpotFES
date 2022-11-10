#include <stdlib.h>
#include <string.h>

#include "repositorio_artistas.h"

#include "lista.h"

struct tRepoArtistas {
    char *artistasCsv;
};

RepoArtistas *InicializaRepositorio(const char *artistas_csv) {
    RepoArtistas *repo = malloc(sizeof *repo);

    repo->artistasCsv = strdup(artistas_csv);

    return repo;
}

void LiberaRepositorio(RepoArtistas *repo) {
    free(repo->artistasCsv);

    free(repo);
}
