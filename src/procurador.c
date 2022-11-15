#include <stdlib.h>

#include "procurador.h"

#include "playlist.h"

void CompletaMusica(Musica *msc, const RepoArtistas *repo) {
    if (GetMscArtists(msc) != NULL)
        return;

    Lista *artistas = InicializaLista(); // Lista<artista>
    Lista *hashes = GetMscArtistsId(msc); // Lista<string>

    int n = GetQuantidadeLista(hashes);
    for (int i = 0; i < n; i++) {
        char *hash = AdquireElementoLista(hashes, i);
        Artista *art = EncontraPeloHashRepoArtistas(repo, hash);
        AdicionaElementoLista(artistas, art);
    }
    
    IncluiMscArtistas(msc, artistas);
    LiberaLista(artistas, &LiberaArtista);
}

void CompletaPlaylist(Playlist *playlist, const RepoMusicas* repo) {
    if (GetMusicasPlaylist(playlist) != NULL)
        return;

    Lista *musicas = InicializaLista(); // Lista<musica>
    Lista *hashes = GetMusicasIdPlaylist(playlist); // Lista<string>

    int n = GetQuantidadeLista(hashes);
    for (int i = 0; i < n; i++) {
        char *hash = AdquireElementoLista(hashes, i);
        Artista *msc = EncontraPeloHashRepoArtistas(repo, hash);
        AdicionaElementoLista(musicas, msc);
    }
    
    IncluiMusicasPlaylist(playlist, musicas);
    LiberaLista(musicas, &LiberaMusica);
}
