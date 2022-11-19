#include <stdlib.h>
#include <string.h>

#include "artista.h"

#include "exception.h"

struct tArtista {
    char *id;
    int seguidores;
    Lista *generos; // Lista<string>
    char *name;
    int popularity;
};

Artista *InicializaArtista(const char *id, const int seguidores,
                           const Lista *generos, const char *name,
                           const int popularity) {
    Artista *art = malloc(sizeof *art);
    if (art == NULL)
        throwOutOfMemoryException("Artista malloc failed");

    art->id = strdup(id);
    if (art->id == NULL)
        throwOutOfMemoryException("Artista internal id strdup failed");

    art->seguidores = seguidores;
    art->generos = CopiaLista(generos, &strdup);
    art->name = strdup(name);
    if (art->name == NULL)
        throwOutOfMemoryException("Artista internal name strdup failed");

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

int GetArtSeguidores(const Artista *art) { return art->seguidores; }

Lista *GetArtGeneros(Artista *art) { return art->generos; }

char *GetArtName(Artista *art) { return art->name; }

int GetArtPopularity(const Artista *art) { return art->popularity; }

Artista *CopiaArtista(const Artista *art) {
    Artista *cpy = InicializaArtista(art->id, art->seguidores, art->generos,
                                     art->name, art->popularity);

    return cpy;
}
