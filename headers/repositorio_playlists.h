#ifndef _REPOSITORIO_PLAYLISTS_
#define _REPOSITORIO_PLAYLISTS_

typedef struct tRepoPlaylists RepoPlaylists;

RepoPlaylists *InicializaRepoPlaylists(const char *playlists_csv);

void LiberaRepoPlaylists(RepoPlaylists *repo);

#endif
