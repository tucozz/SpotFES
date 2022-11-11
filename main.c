#include <stdio.h>
#include <stdlib.h>

#include "app.h"

#include "repositorio_artistas.h"

int main(int argc, char *argv[]) {
    /* if (argc != 3)
        return EXIT_FAILURE;

    App *app = InicializaApp(argv[1], argv[2]);

    RodaApp(app);

    LiberaApp(app); */

    RepoArtistas *repo = InicializaRepoArtistas(argv[1]);
 
     FILE *f = fopen(argv[1], "r");
 
     Artista *art1 = CarregaArtistaCsvRepo(f);
     Artista *art2 = CarregaArtistaCsvRepo(f);
 
     LiberaArtista(art1);
     LiberaArtista(art2);
 
     fclose(f);
 
     LiberaRepoArtistas(repo);

    return EXIT_SUCCESS;
}
