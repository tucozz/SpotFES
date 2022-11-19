#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "repositorio_artistas.h"

#include "exception.h"
#include "lista.h"
#include "parser.h"
#include "repositorio_base.h"

struct tRepoArtistas {
    char *artistasCsv;
};

RepoArtistas *InicializaRepoArtistas(const char *artistas_csv) {
    RepoArtistas *repo = malloc(sizeof *repo);
    if (repo == NULL)
        throwOutOfMemoryException("RepoArtistas malloc failed");

    repo->artistasCsv = strdup(artistas_csv);
    if (repo->artistasCsv == NULL)
        throwOutOfMemoryException(
            "RepoArtistas internal artistasCsv strdup failed");

    return repo;
}

void LiberaRepoArtistas(RepoArtistas *repo) {
    free(repo->artistasCsv);

    free(repo);
}

/**
 * @brief Carrega um @ref Artista do arquivo @p csv
 *
 * @param csv Ponteiro para o inicio da secao do arquivo com um padrao
 * representando um @ref Artista
 * @return Artista* Se valido, retorna um ponteiro para uma nova instancia do
 * @ref Artista ali representada; do contrario, retorna NULL
 */
static Artista *CarregaArtistaCsvRepo(FILE *csv) {
    char *buffer = NULL;
    size_t len = 0;
    if (getline(&buffer, &len, csv) == -1) {
        free(buffer);
        return NULL;
    }

    char *art_id = NULL;
    int art_seguidores;
    Lista *art_generos = NULL; // Lista<string>
    char *art_name = NULL;
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
    free(buffer);

    if (i != 6) {
        free(art_id);
        free(art_name);
        if (art_generos != NULL)
            LiberaLista(art_generos, &free);

        return NULL;
    }

    Artista *art = NULL;
    art = InicializaArtista(art_id, art_seguidores, art_generos, art_name,
                            art_popularity);

    free(art_id);
    free(art_name);
    LiberaLista(art_generos, &free);

    return art;
}

Artista *EncontraPeloHashRepoArtistas(RepoArtistas *repo, const char *hash) {
    FILE *fcsv = fopen(repo->artistasCsv, "r");
    if (fcsv == NULL)
        throwException("IOException",
                       "RepositorioArtistas EncontraPeloHashRepoArtistas artistasCsv file opening failed",
                       EXIT_FAILURE);

    Artista *art = NULL;

    char *bufferart = NULL;
    size_t len = 0;
    long int lastfPosition;
    for (lastfPosition = ftell(fcsv); getline(&bufferart, &len, fcsv) != -1;
         lastfPosition = ftell(fcsv)) {

        /*
         * Primeiro adquire o hash e verifica se e o procurado;
         * se sim, so entao carrega o artista e retorna
         */

        // primeiro strtok retorna o hash (id)
        char *saveptr = NULL;
        char *token = strtok_r(bufferart, REPO_CSV_DELIM, &saveptr);

        int hasFound = strcmp(token, hash) == 0;

        // se nao encontrou, pula
        if (!hasFound)
            continue;

        fseek(fcsv, lastfPosition, SEEK_SET);
        Artista *found = CarregaArtistaCsvRepo(fcsv);
        if (found != NULL) {
            art = found;
            break;
        }
    }

    free(bufferart);
    fclose(fcsv);

    return art;
}
