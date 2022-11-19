#include <stdio.h>
#include <stdlib.h>

#include "app.h"

#include "console.h"
#include "exception.h"
#include "repositorio_artistas.h"
#include "repositorio_musicas.h"
#include "repositorio_playlists.h"

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

static void EncontraMusicaMenu(App *app) {
    system("@cls||clear");
    // TODO: isso
}

static void ListarTodasPlaylistsMenu(App *app) {
    while(true){
        int indice, i;

        system("@cls||clear");

        for(i=0;i<GetQuantidadeLista(app->playlists);i++){
            ListarPlaylist(app->playlists, i);
        }

        printf("[c] Criar Playlist\n"
               "[d] Detalhar Playlist\n"
               "[q] Sair\n");

        char curr;
        scanf("%c%*c", &curr);

        switch (curr) {
        case 'c':;
            char *nome;

            printf("Digite um nome para a playlist:\n");
            scanf("%s", nome);

            Playlist *play = InicializaPlaylist(nome, NULL);
            AdicionaElementoLista(app->playlists, play);

            printf("Playlist %s Criada!\n");
            break;

        case 'd':;
            printf("Digite o Indice da playlist desejada:\n");
            scanf("%c%*c", &indice);
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

static void GerarRelatorioMenu(App *app) {
    system("@cls||clear");
    // TODO: isso
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
