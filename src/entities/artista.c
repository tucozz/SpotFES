#include "artista.h"
#include <stdlib.h>

struct tArtista{
    char *id;
    int seguidores;
    Lista *generos;
    char *name;
    int popularity;
};

Musica *InicializaArtista(char *id, int seguidores, char **generos,
                          char *name, int popularity) {
    Artista *art = malloc(sizeof *art);

    art->id = id;
    art->seguidores = seguidores;
    art->generos = generos;
    art->name = name;
    art->popularity = popularity;

    return msc;
}

void LiberaArtista(Artista *art) {
    free(art->id);
    free(art->name);
    LiberaLista(art->generos, &free);
    
    free(msc);
}

