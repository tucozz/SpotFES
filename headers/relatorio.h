#ifndef _RELATORIO_
#define _RELATORIO_

#include "playlist.h"
#include "repositorio_artistas.h"
#include "repositorio_musicas.h"

void GerarRelatorio(RepoMusicas *repoMsc, RepoArtistas *repoArt,
                    Lista *playlists);

#endif
