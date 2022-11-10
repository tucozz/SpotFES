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

Artista *CarregaArtistaCsvRepo(FILE *csv) {
    char *buffer = NULL;
    size_t len = 0;

    Artista *art = NULL;
    if (getline(&buffer, &len, csv) == -1) {
        free(buffer);
        return NULL;
    }

    char *art_id;
    int art_seguidores;
    Lista *art_generos;
    char *art_name;
    int art_popularity;

    char *saveptr = NULL, *token = NULL;
    int i;
    for (i = 1, token = buffer;; i++, token = NULL) {
        token = strtok_r(token, ";", &saveptr);
        if (token == NULL)
            break;

        if (i == 1) {
            if ((art_id = strdup(token)) == NULL)
                break;
        } else if (i == 2) {
            if (!tryParseInt(token, &art_seguidores))
                break;
        } else if (i == 3) {
            art_generos = CarregaListaStringRepo(token);
        } else if (i == 4) {
            if ((art_name = strdup(token)) == NULL)
                break;
        } else if (i == 5) {
            if (!tryParseInt(token, &art_popularity))
                break;
        }
    }

    if (i != 6) {
        free(buffer);
        return msc;
    }

    art = Artista *InicializaArtista(art_id, art_seguidores, art_generos, art_name, art_popularity);

    free(buffer);
    return art;
}
