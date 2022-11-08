#include "repositorio.h"

struct tRepositorio{
    char *artistascsv;
    char *musicascsv;
};

Repositorio *InicializaRepositorio(char *artistascsv, char *musicascsv) {
    Repositorio *repo = malloc(sizeof *repo);

    repo->artistascsv = artistascsv;
    repo->musicascsv = musicascsv;

    return repo;
}

void *LiberaRepositorio(Repositorio *repo) {
    free(repo->artistascsv);
    free(repo->musicascsv);
    free(repo);
    
}
