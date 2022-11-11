#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "repositorio_musicas.h"

#include "parser.h"
#include "repositorio_base.h"

struct tRepoMusicas {
    char *musicasCsv;
};

RepoMusicas *InicializaRepoMusicas(const char *musicas_csv) {
    RepoMusicas *repo = malloc(sizeof *repo);

    repo->musicasCsv = strdup(musicas_csv);

    return repo;
}

void LiberaRepoMusicas(RepoMusicas *repo) {
    free(repo->musicasCsv);

    free(repo);
}

/**
 * @brief Carrega uma @ref Musica do arquivo @p csv
 *
 * @param csv Ponteiro para o inicio da secao do arquivo com um padrao
 * representando uma @ref Musica
 * @return Musica* Se valido, retorna um ponteiro para uma nova instancia da
 * @ref Musica ali representada; do contrario, retorna NULL
 */
static Musica *CarregaMusicaCsvRepo(FILE *csv) {
    char *buffer = NULL;
    size_t len = 0;

    Musica *msc = NULL;
    if (getline(&buffer, &len, csv) == -1) {
        free(buffer);
        return NULL;
    }

    char *msc_id;
    char *msc_name;
    int msc_popularity;
    int msc_duration_ms;
    bool msc_explicit;
    Lista *msc_artists;
    Lista *msc_id_artists;
    char *msc_release_date;
    float msc_danceability;
    float msc_energy;
    int msc_key;
    float msc_loudness;
    enum Mode msc_mode;
    float msc_speechiness;
    float msc_acousticness;
    float msc_instrumentalness;
    float msc_liveness;
    float msc_valence;
    float msc_tempo;
    int msc_time_signature;

    char *saveptr = NULL, *token = NULL;
    int i;
    for (i = 1, token = buffer;; i++, token = NULL) {
        token = strtok_r(token, ";", &saveptr);
        if (token == NULL)
            break;

        if (i == 1) {
            if ((msc_id = strdup(token)) == NULL)
                break;
        } else if (i == 2) {
            if ((msc_name = strdup(token)) == NULL)
                break;
        } else if (i == 3) {
            if (!tryParseInt(token, &msc_popularity))
                break;
        } else if (i == 4) {
            if (!tryParseInt(token, &msc_duration_ms))
                break;
        } else if (i == 5) {
            int tmp_explicit;
            if (!tryParseInt(token, &tmp_explicit) ||
                (tmp_explicit != 1 && tmp_explicit != 0))
                break;

            msc_explicit = tmp_explicit;
        } else if (i == 6) {
            msc_artists = CarregaListaStringRepo(token);
        } else if (i == 7) {
            msc_id_artists = CarregaListaStringRepo(token);
        } else if (i == 8) {
            if ((msc_release_date = strdup(token)) == NULL)
                break;
        } else if (i == 9) {
            if (!tryParseFloat(token, &msc_danceability))
                break;
        } else if (i == 10) {
            if (!tryParseFloat(token, &msc_energy))
                break;
        } else if (i == 11) {
            if (!tryParseInt(token, &msc_key))
                break;
        } else if (i == 12) {
            if (!tryParseFloat(token, &msc_loudness))
                break;
        } else if (i == 13) {
            int tmp_mode;
            if (!tryParseInt(token, &tmp_mode) ||
                (tmp_mode != 1 && tmp_mode != 0))
                break;

            msc_mode = tmp_mode;
        } else if (i == 14) {
            if (!tryParseFloat(token, &msc_speechiness))
                break;
        } else if (i == 15) {
            if (!tryParseFloat(token, &msc_acousticness))
                break;
        } else if (i == 16) {
            if (!tryParseFloat(token, &msc_instrumentalness))
                break;
        } else if (i == 17) {
            if (!tryParseFloat(token, &msc_liveness))
                break;
        } else if (i == 18) {
            if (!tryParseFloat(token, &msc_valence))
                break;
        } else if (i == 19) {
            if (!tryParseFloat(token, &msc_tempo))
                break;
        } else if (i == 20) {
            if (!tryParseInt(token, &msc_time_signature))
                break;
        }
    }

    if (i != 21) {
        free(buffer);
        return msc;
    }

    msc = InicializaMusica(msc_id, msc_name, msc_popularity, msc_duration_ms,
                           msc_explicit, msc_artists, msc_id_artists,
                           msc_release_date, msc_danceability, msc_energy,
                           msc_key, msc_loudness, msc_mode, msc_speechiness,
                           msc_acousticness, msc_instrumentalness, msc_liveness,
                           msc_valence, msc_tempo, msc_time_signature);

    free(buffer);
    return msc;
}

Lista *EncontraPeloNomeRepoMusica(RepoMusicas *repo, char *query) {
    FILE *fcsv = fopen(repo->musicasCsv, "r");
    Lista *lista = InicializaLista();

    char *tmpMsc = NULL;
    size_t lenTmpMsc = 0;
    long int lastCsvPos;
    for (lastCsvPos = ftell(fcsv); getline(&tmpMsc, &lenTmpMsc, fcsv) != -1;
         lastCsvPos = ftell(fcsv)) {

        /*
         * Primeiro adquire o nome e verifica se contem a query;
         * se sim, so entao carrega a musica e adiciona na lista
         */

        // primeiro strtok retorna o hash (id) e o segundo retorna o nome
        char *saveptr = NULL;
        char *token = strtok_r(tmpMsc, REPO_CSV_DELIM, &saveptr);
        token = strtok_r(NULL, REPO_CSV_DELIM, &saveptr);
        
        NormalizaString(token);
        NormalizaString(query);

        int hasFound = strstr(token, query) != NULL;

        // se nao encontrou, pula
        if (!hasFound)
            continue;

        fseek(fcsv, lastCsvPos, SEEK_SET);
        Musica *msc = CarregaMusicaCsvRepo(fcsv);
        printf("%s\n", token);
        AdicionaElementoLista(lista, msc);
    }

    free(tmpMsc);
    fclose(fcsv);

    return lista;
}
