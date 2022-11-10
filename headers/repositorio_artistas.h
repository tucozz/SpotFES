#ifndef _REPOSITORIO_ARTISTAS_
#define _REPOSITORIO_ARTISTAS_

typedef struct tRepoArtistas RepoArtistas;

RepoArtistas *InicializaRepoArtistas(const char *artistas_csv);

void LiberaRepoArtistas(RepoArtistas *repo);

Artista *CarregaArtistaCsvRepo(FILE *csv);

#endif
