#include <stdio.h>
#include <stdlib.h>

#include "app.h"

#include "exception.h"
#include "repositorio_artistas.h"
#include "repositorio_musicas.h"
#include "repositorio_playlists.h"
#include "console.h"

static void EncontraMusicaMenu(App *app);

static void ListarTodasPlaylistsMenu(App *app);

static void GerarRelatorioMenu(App *app);

struct tApp {
    RepoMusicas *repoMsc;
    RepoArtistas *repoArt;
    Lista *playlists; // Lista<playlist>
};

App *InicializaApp(const char *artistascsv, const char *musicascsv) {
    App *app = malloc(sizeof *app);
    if (app == NULL)
        throwOutOfMemoryException("App malloc failed");

    app->repoMsc = InicializaRepoMusicas(musicascsv);
    app->repoArt = InicializaRepoArtistas(musicascsv);
    app->playlists = CarregaTodasPlaylistsRepo();

    return app;
}

void *LiberaApp(App *app) {
    LiberaRepoMusicas(app->repoMsc);
    LiberaRepoArtistas(app->repoArt);

    LiberaLista(app->playlists, &LiberaPLaylist);

    free(app);

    return NULL;
}

static void SairAppMenu(App *app) {
    system("@cls||clear");
    printf("Volte sempre!\n");
    SalvaTodasPlaylistsRepo(app->playlists);
}

void RodaApp(App *app) {
    while (true) {
        system("@cls||clear");
        printf("[f] Encontrar Música\n"
               "[g] Listar suas Playlists\n"
               "[r] Gerar Relatório\n"
               "[q] Sair\n");

        char curr;
        scanf("%c%*c", &curr);
        switch (curr) {
        case 'f':;
            EncontraMusicaMenu(app);
            break;

        case 'g':;
            ListarTodasPlaylistsMenu(app);
            break;

        case 'r':;
            ListarTodasPlaylistsMenu(app);
            break;

        case 'q':;
            SairAppMenu(app);
            return;

        default:
            printf("Ops! Acao invalida. Favor especificar funcionalidade "
                   "desejada\n");
            continue;
        }
    }
}

static void EncontraMusicaMenu(App *app) {
    system("@cls||clear");
    // TODO: isso
}

static void ListarTodasPlaylistsMenu(App *app) {
    system("@cls||clear");
    
}

static void GerarRelatorioMenu(App *app) {
    system("@cls||clear");
    // TODO: isso
}
