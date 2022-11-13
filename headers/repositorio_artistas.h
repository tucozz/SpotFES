#ifndef _REPOSITORIO_ARTISTAS_
#define _REPOSITORIO_ARTISTAS_

#include "artista.h"

typedef struct tRepoArtistas RepoArtistas;

RepoArtistas *InicializaRepoArtistas(const char *artistas_csv);

void LiberaRepoArtistas(RepoArtistas *repo);

#endif
