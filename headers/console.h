#ifndef _CONSOLE_
#define _CONSOLE_

#include "musica.h"
#include "playlist.h"

void ListarMusica(Musica *, int i);

void ListarTodasMusicas(Lista *, int n, int m);

void DetalharMusica(Musica *);

void ListarPlaylist(Playlist *, int I);

void ListarTodasPlaylists(Lista *, int n, int m);

void DetalharPlaylist(Playlist *);

#endif