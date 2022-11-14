#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "repositorio_playlists.h"

#include "playlist.h"
#include "repositorio_base.h"

/**
 * @brief Salva uma @ref Playlist* @p playlist no arquivo @p fbin
 *
 * @warning @ref FILE* @p fbin PRECISA estar no modo wb
 *
 * @param fbin Ponteiro para o inicio da secao do arquivo onde @p playlist sera
 * salva
 * @param playlist A @ref Playlist* a ser salva
 *
 * @exception EXIT_FAILURE Caso ocorra qualquer erro ao escrever qualquer campo;
 * mensagem de erro e registrada em stderr
 */
static void SalvaPlaylistRepo(FILE *fbin, Playlist *playlist) {
    char *nome = GetNomePlaylist(playlist);
    size_t nlen = strlen(nome) + 1;
    if (fwrite(nome, nlen, 1, fbin) != 1) {
        perror("E01 Erro ao salvar nome da playlist no bin - em "
               "SalvaPlaylistRepo()");
        exit(EXIT_FAILURE);
    }

    Lista *musicas_id = GetMusicasIdPlaylist(playlist); // Lista<string>

    // quantidade de hashes da playlist
    int mscs_qtd = GetQuantidadeLista(musicas_id);
    size_t qsize = sizeof mscs_qtd;
    if (fwrite(&mscs_qtd, qsize, 1, fbin) != 1) {
        perror("E02 Erro ao salvar mscs_qtd da playlist no bin - em "
               "SalvaPlaylistRepo()");
        exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < mscs_qtd; i++) {
        char *msc_hash = AdquireElementoLista(musicas_id, i);

        size_t hlen = strlen(msc_hash) + 1;
        if (fwrite(msc_hash, hlen, 1, fbin) != 1) {
            perror("E04 Erro ao salvar msc_hash da playlist no bin - em "
                   "SalvaPlaylistRepo()");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * @brief Carrega uma @ref Playlist* do arquivo @p fbin
 *
 * @warning @ref FILE* @p fbin PRECISA estar no modo rb
 *
 * @param fbin Ponteiro para o inicio da secao do arquivo com um padrao
 * representando uma @ref Playlist*
 * @return Playlist* Se valido, retorna um ponteiro para uma nova instancia da
 * @ref Playlist* ali representada; do contrario, retorna NULL
 */
static Playlist *CarregaPlaylistRepo(FILE *fbin) {
    char *nome = NULL;
    size_t nlen = 0;
    if (getdelim(&nome, &nlen, '\0', fbin) == -1) {
        free(nome);

        return NULL;
    }

    // quantida de hashes salvos
    int mscs_qtd = -1;
    size_t qsize = sizeof mscs_qtd;
    if (fread(&mscs_qtd, qsize, 1, fbin) != 1) {
        free(nome);

        return NULL;
    }

    // lista de hashes
    Lista *musicas_id = InicializaLista(); // List<string>

    char *msc_hash = NULL;
    size_t mschlen = 0;
    int i;
    for (i = 0; i < mscs_qtd; i++) {
        if (getdelim(&msc_hash, &mschlen, '\0', fbin) == -1) {
            free(nome);
            LiberaLista(musicas_id, &free);
            free(msc_hash);

            return NULL;
        }

        AdicionaElementoLista(musicas_id, strdup(msc_hash));
    }

    Playlist *playlist = InicializaPlaylist(nome, musicas_id);

    free(nome);
    LiberaLista(musicas_id, &free);
    free(msc_hash);

    return playlist;
}

void SalvaTodasPlaylistsRepo(Lista *playlists) {
    FILE *fbin = fopen(REPO_PLAYLISTS_DEFAULT_PATH_SAVE, "wb");
    if (!fbin) {
        perror(
            "E08 Erro ao abrir arquivo (wb) " REPO_PLAYLISTS_DEFAULT_PATH_SAVE
            " - em SalvaTodasPlaylistsRepo()");
        exit(EXIT_FAILURE);
    }

    int pqtd = GetQuantidadeLista(playlists);
    int i;
    for (i = 0; i < pqtd; i++)
        SalvaPlaylistRepo(fbin, AdquireElementoLista(playlists, i));

    fclose(fbin);
}

Lista *CarregaTodasPlaylistsRepo() {
    Lista *playlists = InicializaLista();

    FILE *fbin = fopen(REPO_PLAYLISTS_DEFAULT_PATH_SAVE, "rb");
    if (!fbin) {
        return playlists;
    }

    Playlist *curr = NULL;
    while ((curr = CarregaPlaylistRepo(fbin)))
        AdicionaElementoLista(playlists, curr);

    fclose(fbin);

    return playlists;
}
