#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"

#include "detalha_musica_menu.h"
#include "detalha_playlist_menu.h"
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
#include "types.h"

struct tApp {
    RepoMusicas *repoMsc;
    RepoArtistas *repoArt;
    Lista *playlists; // Lista<playlist>
    Lista *musicas;   // Lista<Musica *>
};

App *InicializaApp(const char *musicascsv, const char *artistascsv) {
    App *app = malloc(sizeof *app);
    if (app == NULL)
        throwOutOfMemoryException("App malloc failed");

    app->repoMsc = InicializaRepoMusicas(musicascsv);
    app->repoArt = InicializaRepoArtistas(artistascsv);
    app->musicas = InicializaLista();

    return app;
}

void *LiberaApp(App *app) {
    LiberaRepoMusicas(app->repoMsc);
    LiberaRepoArtistas(app->repoArt);

    LiberaLista(app->playlists, (free_fn)&LiberaPLaylist);
    LiberaLista(app->musicas, (free_fn)&LiberaMusica);

    free(app);

    return NULL;
}

RepoMusicas *GetRepoMusicasApp(App *app) { return app->repoMsc; }

RepoArtistas *GetRepoArtistasApp(App *app) { return app->repoArt; }

Lista *GetPlaylistsApp(App *app) { return app->playlists; }

void SetMusicasApp(App *app, Lista *mscs) {
    if (app->musicas != NULL) {
        LiberaLista(app->musicas, (free_fn)&LiberaMusica);
    }

    app->musicas = mscs;
}

void RodaApp(App *app) {
    app->playlists = CarregaTodasPlaylistsRepo();

    bool primeiraVez = true;
    while (true) {
        system("@cls||clear");

        printf("%c", '\n');
        ImprimeMarca(primeiraVez);
        printf("%c", '\n');
        primeiraVez = false;

        printf("[f] Buscar músicas\n"
               "[h] Listar uma música\n"
               "[c] Criar uma playlist\n"
               "[g] Listar playlists\n"
               "[v] Listar uma playlist\n"
               "[d] Adicionar uma música na playlist\n"
               "[r] Exportar Relatório\n"
               "[b] Sobre\n"
               "[q] Sair\n");

        char curr;
        scanf("%c%*c", &curr);
        switch (curr) {
        case 'f':;
            EncontraMusicaMenu(app, NULL);
            break;

        case 'h':;
            if (GetQuantidadeLista(app->musicas) == 0) {
                ErroMenu("Primeiro, busque por músicas na funcionalidade [f]");
                break;
            }

            system("@cls||clear");
            printf("\nInforme o indice da musica: ");

            int i;
            scanf("%d%*c", &i);

            if (i >= 0 && i < GetQuantidadeLista(app->musicas)) {
                DetalhaMusicaMenu(app, AdquireElementoLista(app->musicas, i),
                                  NULL);
            } else {
                system("@cls||clear");
                printf(ANSI_COLOR_YELLOW
                       "Indice (%d) inválido." ANSI_COLOR_RESET
                       "\npressione ENTER para continuar",
                       i);
                scanf("%*c");
            }
            break;

        case 'c':;
            system("@cls||clear");
            printf("Digite um nome para a playlist:\n");

            char nome[30];
            scanf("%29[^\n]%*c", nome);
            if (strlen(nome) < 1) {
                return;
            }

            Lista *playMscs = InicializaLista(); // Lista<string>

            Playlist *play = InicializaPlaylist(nome, playMscs);
            AdicionaElementoLista(app->playlists, play);

            LiberaLista(playMscs, &free);

            printf("Playlist %s Criada!\npressione ENTER para continuar", nome);
            scanf("%*c");
            break;

        case 'g':;
            ListarTodasPlaylistsMenu(app, NULL);
            break;

        case 'v':;
            if (GetQuantidadeLista(GetPlaylistsApp(app)) == 0) {
                ErroMenu("Primeiro, crie uma playlist na funcionalidade [c]");
                break;
            }
            system("@cls||clear");
            printf("Digite o Indice da playlist desejada:\n");

            int iPlay;
            scanf("%d%*c", &iPlay);

            if (iPlay < 0 ||
                iPlay >= GetQuantidadeLista(GetPlaylistsApp(app))) {
                ErroMenu("Ops! Indique um indice valido para detalhar a "
                         "playlist.");
                break;
            }

            Playlist *currPlay =
                AdquireElementoLista(GetPlaylistsApp(app), iPlay);

            DetalhaPlaylistMenu(app, currPlay, NULL);
            break;

        case 'd':;
            if (GetQuantidadeLista(GetPlaylistsApp(app)) == 0) {
                ErroMenu("Primeiro, crie uma playlist na funcionalidade [c]");
                break;
            }
            if (GetQuantidadeLista(app->musicas) == 0) {
                ErroMenu("Primeiro, busque por músicas na funcionalidade [f]");
                break;
            }

            system("@cls||clear");
            printf("\nInforme o indice da musica: ");

            int iMsc;
            scanf("%d%*c", &iMsc);

            if (iMsc < 0 || iMsc >= GetQuantidadeLista(app->musicas)) {
                system("@cls||clear");
                printf(ANSI_COLOR_YELLOW
                       "Indice (%d) inválido." ANSI_COLOR_RESET
                       "\npressione ENTER para continuar",
                       iMsc);
                scanf("%*c");
                break;
            }

            Musica *o = AdquireElementoLista(app->musicas, iMsc);

            printf("Digite o Indice da playlist desejada:\n");
            int selecPlay;
            scanf("%d%*c", &selecPlay);

            if (selecPlay < 0 ||
                selecPlay >= GetQuantidadeLista(GetPlaylistsApp(app))) {
                ErroMenu("Ops! Indique um indice valido.");
                break;
            }

            Playlist *t =
                AdquireElementoLista(GetPlaylistsApp(app), selecPlay);

            if (AdicionaMusicaPlaylist(t, o))
                printf("Musica Adicionada!\n");
            else
                printf("Esta musica ja está na playlist!\n");

            printf("pressione ENTER para continuar...");
            scanf("%*c");
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
