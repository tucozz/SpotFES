#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listar_todas_playlists_menu.h"

#include "console.h"
#include "encontra_musica_menu.h"
#include "listar_todas_musicas_menu.h"
#include "playlist.h"
#include "procurador.h"

void ListarTodasPlaylistsMenu(App *app, Musica *mscOrig) {
    while (true) {
        int indice, i;

        system("@cls||clear");

        ListarTodasPlaylists(GetPlaylistsApp(app), 0,
                             GetQuantidadeLista(GetPlaylistsApp(app)));

        printf("[c] Criar Playlist\n"
               "[d] Detalhar Playlist\n"
               "[q] Sair\n");

        char curr;
        scanf("%c%*c", &curr);

        switch (curr) {
        case 'c':;
            char nome[30];

            printf("Digite um nome para a playlist:\n");
            scanf("%29[^\n]%*c", nome);
            if (strlen(nome) <= 1) {
                return;
            }

            Playlist *play = InicializaPlaylist(nome, InicializaLista());
            AdicionaElementoLista(GetPlaylistsApp(app), play);

            printf("Playlist %s Criada!\n", nome);
            break;

        case 'd':;
            printf("Digite o Indice da playlist desejada:\n");
            while (true) {
                scanf("%d%*c", &indice);
                indice--;

                if (indice >= 0 &&
                    indice < GetQuantidadeLista(GetPlaylistsApp(app)))
                    break;

                printf("Ops! Indique um indice valido para detalhar a "
                       "playlist.\n");
            }

            system("@cls||clear");

            CompletaPlaylist(AdquireElementoLista(GetPlaylistsApp(app), indice),
                             GetRepoMusicasApp(app));
            DetalharPlaylist(
                AdquireElementoLista(GetPlaylistsApp(app), indice));

            printf("[r] Recomendar Musicas Semelhantes\n"
                   "[a] Adicionar Musica na Playlist\n"
                   "[q] Sair\n");

            char option;
            scanf("%c%*c", &option);

            switch (option) {
            case 'r':;
                printf("Quantas musicas recomendadas deseja?\n");
                char k;
                scanf("%d%*c", &k);

                Lista *recomendadas = InicializaLista;
                recomendadas = RecomendaMusicas(
                    AdquireElementoLista(GetPlaylistsApp(app), indice), k,
                    GetRepoMusicasApp(app));

                ListarTodasMusicasMenu(
                    app, recomendadas,
                    AdquireElementoLista(GetPlaylistsApp(app), indice));

                LiberaLista(recomendadas, &LiberaMusica);
                break;

            case 'a':;
                if (mscOrig != NULL) {
                    if (AdicionaMusicaPlaylist(
                            AdquireElementoLista(GetPlaylistsApp(app), indice),
                            mscOrig)) {
                        printf("Musica Adicionada!\n");
                        break;
                    }
                    printf("Esta musica ja está na playlist!\n");
                }

                EncontraMusicaMenu(
                    app, AdquireElementoLista(GetPlaylistsApp(app), indice));
                break;

            case 'q':;
                return;

            default:
                printf(ANSI_COLOR_YELLOW
                       "Ops! Acao invalida. Favor especificar "
                       "funcionalidade " ANSI_COLOR_RESET
                       "desejada\npressione ENTER para continuar");
                scanf("%*c");
                continue;
            }

            break;

        case 'q':;
            return;

        default:
            printf(ANSI_COLOR_YELLOW "Ops! Acao invalida. Favor especificar "
                                     "funcionalidade " ANSI_COLOR_RESET
                                     "desejada\n");
            scanf("%*c");
            continue;
        }
    }
}
