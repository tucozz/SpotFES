#include <stdlib.h>

#include "playlist.h"

#include "lista.h"

struct tPlaylist {
    char *nome;
    Lista *musicas; // Lista<musica>
};

Playlist *InicializaPlaylist(char *nome, Lista *musicas) {
    Playlist *playlist = malloc(sizeof *playlist);

    playlist->nome = nome;
    playlist->musicas = musicas;

    return playlist;
}

void LiberaPLaylist(Playlist *playlist) {
    free(playlist->nome);

    LiberaLista(playlist->musicas, &LiberaMusica);

    free(playlist);
}

void AdicionaMusicaPlaylist(Playlist *playlist, Musica *msc) {
    AdicionaElementoLista(playlist->musicas, msc);
}
