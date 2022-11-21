#include <stdio.h>
#include <stdlib.h>

#include "app.h"

#include "encontra_musica_menu.h"
#include "erro_menu.h"
#include "exception.h"
#include "exportar_relatorio_menu.h"
#include "listar_todas_playlists_menu.h"
#include "repositorio_artistas.h"
#include "repositorio_musicas.h"
#include "repositorio_playlists.h"
#include "sair_app_menu.h"
#include "sobre_menu.h"

struct tApp {
    RepoMusicas *repoMsc;
    RepoArtistas *repoArt;
    Lista *playlists; // Lista<playlist>
};

App *InicializaApp(const char *musicascsv, const char *artistascsv) {
    App *app = malloc(sizeof *app);
    if (app == NULL)
        throwOutOfMemoryException("App malloc failed");

    app->repoMsc = InicializaRepoMusicas(musicascsv);
    app->repoArt = InicializaRepoArtistas(artistascsv);

    return app;
}

void *LiberaApp(App *app) {
    LiberaRepoMusicas(app->repoMsc);
    LiberaRepoArtistas(app->repoArt);

    LiberaLista(app->playlists, &LiberaPLaylist);

    free(app);

    return NULL;
}

RepoMusicas *GetRepoMusicasApp(App *app) { return app->repoMsc; }

RepoArtistas *GetRepoArtistasApp(App *app) { return app->repoArt; }

Lista *GetPlaylistsApp(App *app) { return app->playlists; }

void RodaApp(App *app) {
    app->playlists = CarregaTodasPlaylistsRepo();

    bool primeiraVez = true;
    while (true) {
        system("@cls||clear");

        printf("%c", '\n');
        ImprimeMarca(primeiraVez);
        printf("%c", '\n');
        primeiraVez = false;

        printf("[f] Encontrar Música\n"
               "[g] Listar suas Playlists\n"
               "[r] Exportar Relatório\n"
               "[b] Sobre\n"
               "[q] Sair\n");

        char curr;
        scanf("%c%*c", &curr);
        switch (curr) {
        case 'f':;
            EncontraMusicaMenu(app, NULL);
            break;

        case 'g':;
            ListarTodasPlaylistsMenu(app, NULL);
            break;

        case 'r':;
            ExportarRelatorioMenu(app);
            break;

        case 'b':;
            SobreMenu();
            break;

        case 'q':;
            SairAppMenu(app);
            return;

        default:
            ErroMenu("Ops! Acao invalida. Favor especificar funcionalidade "
                     "desejada");
            continue;
        }
    }
}
