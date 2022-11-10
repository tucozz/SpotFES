#include <stdlib.h>

#include "artista.h"

struct tArtista {
    char *id;
    int seguidores;
    Lista *generos;
    char *name;
    int popularity;
};

Artista *InicializaArtista(char *id, int seguidores, Lista *generos, char *name,
                           int popularity) {
    Artista *art = malloc(sizeof *art);

    art->id = id;
    art->seguidores = seguidores;
    art->generos = generos;
    art->name = name;
    art->popularity = popularity;

    return art;
}

void LiberaArtista(Artista *art) {
    free(art->id);
    free(art->name);
    LiberaLista(art->generos, &free);

    free(art);
}

char *GetArtId(tArtista art)
    return art.id;

int GetArtSeguidores(tArtista art)
    return art.seguidores;

Lista *GetArtGeneros(tArtista art)
    return art.generos;

char *GetArtName(tArtista art)
    return art.name;

int GetArtPopularity(tArtista art)
    return art.popularity;


