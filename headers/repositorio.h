#ifndef _REPOSITORIO_
#define _REPOSITORIO_

typedef struct tRepositorio Repositorio;

Repositorio *InicializaRepositorio(char *artistascsv, char *musicascsv);

void *LiberaRepositorio(Repositorio *repo);

#endif
