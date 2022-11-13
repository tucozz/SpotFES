#ifndef _PLAYLIST_
#define _PLAYLIST_

#include "musica.h"

typedef struct tPlaylist Playlist;

Playlist *InicializaPlaylist();

void LiberaPLaylist(Playlist *playlist);

void AdicionaMusicaPlaylist(Playlist *playlist, Musica *msc);

#endif
