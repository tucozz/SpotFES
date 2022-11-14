#include <stdlib.h>
#include <string.h>

#include "playlist.h"

struct tPlaylist {
    char *nome;
    Lista *musicas;    // Lista<musica>
    Lista *musicas_id; // Lista<string>
};

Playlist *InicializaPlaylist(const char *nome, const Lista *musicas_id) {
    Playlist *playlist = malloc(sizeof *playlist);

    playlist->nome = strdup(nome);
    playlist->musicas = NULL;
    playlist->musicas_id = CopiaLista(musicas_id, &strdup);

    return playlist;
}

void LiberaPLaylist(Playlist *playlist) {
    free(playlist->nome);

    if (playlist->musicas != NULL)
        LiberaLista(playlist->musicas, &LiberaMusica);

    LiberaLista(playlist->musicas_id, &free);

    free(playlist);
}

char *GetNomePlaylist(Playlist *playlist) { return playlist->nome; }

Lista *GetMusicasPlaylist(Playlist *playlist) { return playlist->musicas; }

Lista *GetMusicasIdPlaylist(Playlist *playlist) { return playlist->musicas_id; }

bool IncluiMusicasPlaylist(Playlist *playlist, const Lista *musicas) {
    if (playlist->musicas != NULL || musicas == NULL)
        return false;

    playlist->musicas = CopiaLista(musicas, &CopiaMusica);

    return true;
}

bool AdicionaMusicaPlaylist(Playlist *playlist, const Musica *msc) {
    if (msc == NULL)
        return false;

    if (playlist->musicas != NULL)
        AdicionaElementoLista(playlist->musicas, CopiaMusica(msc));

    AdicionaElementoLista(playlist->musicas_id, strdup(GetMscId(msc)));

    return true;
}

Playlist *CopiaPlaylist(const Playlist *playlist) {
    Playlist *cpy = InicializaPlaylist(playlist->nome, playlist->musicas_id);

    return cpy;
}
