#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "repositorio_playlists.h"

struct tRepoPlaylists {
    char *playlistsCsv;
};

RepoPlaylists *InicializaRepoPlaylists(const char *playlists_csv) {
    RepoPlaylists *repo = malloc(sizeof *repo);

    repo->playlistsCsv = strdup(playlists_csv);

    return repo;
}

void LiberaRepoPlaylists(RepoPlaylists *repo) {
    free(repo->playlistsCsv);

    free(repo);
}
