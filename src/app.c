#include <stdio.h>
#include <stdlib.h>

#include "app.h"

#include "repositorio_artistas.h"
#include "repositorio_musicas.h"
#include "repositorio_playlists.h"

/** Funcao de Buscar Musicas */
#define APP_FUNC_BUSCMUSC 1
/** Funcao de Listar Musica */
#define APP_FUNC_LISTMUSC 2
/** Funcao de Criar Playlist */
#define APP_FUNC_CRIAPLAY 3
/** Funcao de Listar todas as Playlists */
#define APP_FUNC_LSPLAYLS 4
/** Funcao de Listar Playlist */
#define APP_FUNC_LISTPLAY 5
/** Funcao de Adicionar Musica a Playlist */
#define APP_FUNC_ADDMSCPL 6
/** Funcao de Recomendar Musicas dada uma Playlist */
#define APP_FUNC_RECOPLAY 7
/** Funcao de Gerar Relatorios */
#define APP_FUNC_GENRELAT 8
/** Acao de Voltar a Tras na Interface */
#define APP_ACTN_VOOOLTAR 9
/** Acao de Interagir com o contexto da interface */
#define APP_ACTN_INTERAGE 0

struct tApp {
    RepoMusicas *repoMsc;
    RepoArtistas *repoArt;
    Lista* playlists; // Lista<playlist>
};

App *InicializaApp(const char *artistascsv, const char *musicascsv) {
    App *app = malloc(sizeof *app);

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

void RodaApp() {
    while (1) {
        system("@cls||clear");
        printf("Digite o numero relacionado a funcionalidade desejada\n
        \n
        1. Encontrar Musica\n
        2. Listar Musica\n
        3. Criar Playlist\n
        4. Listar Playlists\n
        5. Listar Musicas da Playlist\n
        6. Adicionar Musica a Playlist\n
        7. Recomendar Musicas\n
        8. Gerar Relatorios\n
        9. Voltar\n");

        int curr;
        scanf("%d", &curr);
        switch (curr) {
        case APP_FUNC_BUSCMUSC:;

            break;

        case APP_FUNC_LISTMUSC:;
            break;

        case APP_FUNC_CRIAPLAY:;
            break;

        case APP_FUNC_LSPLAYLS:;
            break;

        case APP_FUNC_LISTPLAY:;
            break;

        case APP_FUNC_ADDMSCPL:;
            break;

        case APP_FUNC_RECOPLAY:;
            break;

        case APP_FUNC_GENRELAT:;
            break;

        case APP_ACTN_VOOOLTAR:;
            return;

        default:
            printf("Ops! Acao invalida. Favor especificar funcionalidade desejada\n");
            continue;
        }
    }
}

void SairApp(App *app) {
    SalvaTodasPlaylistsRepo(app->playlists);
}
