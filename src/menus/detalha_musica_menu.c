#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "detalha_musica_menu.h"

#include "console.h"
#include "listar_todas_playlists_menu.h"
#include "procurador.h"

static void AbrirMusicaNoNavegador(Musica *msc) {
    char command[256] = "xdg-open https://open.spotify.com/track/";
    strcat(command, GetMscId(msc));
    system(command);
}

void DetalhaMusicaMenu(App *app, Musica *msc, Playlist *playlistOrig) {
    CompletaMusica(msc, GetRepoArtistasApp(app));

    do {
        system("@cls||clear");
        DetalharMusica(msc);

        printf("[f] Escutar Música\n"
               "[a] Adicionar Música à Playlist\n"
               "[q] Voltar Menu\n");

        char curr;
        scanf("%c%*c", &curr);
        switch (curr) {
        case 'f':;
            AbrirMusicaNoNavegador(msc);
            printf(ANSI_COLOR_YELLOW
                   "Abrindo música no navegador..." ANSI_COLOR_RESET
                   "\npressione ENTER para voltar ao SpotFES");
            scanf("%*c");
            break;

        case 'a':;
            if (playlistOrig != NULL) {
                bool status = AdicionaMusicaPlaylist(playlistOrig, msc);
                if (status) {
                    printf(ANSI_COLOR_YELLOW
                           "Música adicionada" ANSI_COLOR_RESET
                           "\npressione ENTER para continuar");
                    scanf("%*c");
                    return;
                }

                printf(ANSI_COLOR_YELLOW
                       "Essa música já está na sua playlist" ANSI_COLOR_RESET
                       "\npressione ENTER para continuar");
                scanf("%*c");
                break;
            }

            ListarTodasPlaylistsMenu(app, msc);
            break;

        case 'q':;
            return;

        default:
            printf(ANSI_COLOR_YELLOW "Ops! Acao invalida. Favor especificar "
                                     "funcionalidade desejada" ANSI_COLOR_RESET
                                     "\npressione ENTER para continuar");
            scanf("%*c");
            break;
        }
    } while (true);
}
