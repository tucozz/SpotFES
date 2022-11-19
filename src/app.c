#include <stdio.h>
#include <stdlib.h>

#include "app.h"

#include "console.h"
#include "exception.h"
#include "repositorio_artistas.h"
#include "repositorio_musicas.h"
#include "repositorio_playlists.h"

/**
 * @brief Procura por uma musica e lista elas
 *
 * @param app O @ref App*
 * @param playlistOrig Pode ser NULL; é a playlist que invocou esse menu a
 * procura de uma musica para adicionar nela
 */
static void EncontraMusicaMenu(App *app, Playlist *playlistOrig);

/**
 * @brief Lista todas as playlists do usuário
 *
 * @param app O @ref App*
 * @param mscOrig Pode ser NULL; é a musica que invocou esse menu querendo se
 * adicionar numa playlist
 */
static void ListarTodasPlaylistsMenu(App *app, Musica *mscOrig);

static void GerarRelatorioMenu(App *app);

static void SairAppMenu(App *app);

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
            EncontraMusicaMenu(app, NULL);
            break;

        case 'g':;
            ListarTodasPlaylistsMenu(app, NULL);
            break;

        case 'r':;
            GerarRelatorioMenu(app);
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

static void EncontraMusicaMenu(App *app, Playlist *playlistOrig) {
    system("@cls||clear");
    // TODO: isso
}

static void ListarTodasPlaylistsMenu(App *app, Musica *mscOrig) {
    system("@cls||clear");
}

static void GerarRelatorioMenu(App *app) {
    system("@cls||clear");
    // TODO: isso
}

static void SairAppMenu(App *app) {
    system("@cls||clear");
    printf("Volte sempre!\n");
    SalvaTodasPlaylistsRepo(app->playlists);
}
