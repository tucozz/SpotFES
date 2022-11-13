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

char *GetArtId(Artista *art) { return art->id; }

int GetArtSeguidores(Artista *art) { return art->seguidores; }

Lista *GetArtGeneros(Artista *art) { return art->generos; }

char *GetArtName(Artista *art) { return art->name; }

int GetArtPopularity(Artista *art) { return art->popularity; }
