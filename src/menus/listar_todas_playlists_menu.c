#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listar_todas_playlists_menu.h"

#include "console.h"
#include "detalha_playlist_menu.h"
#include "encontra_musica_menu.h"
#include "erro_menu.h"
#include "listar_todas_musicas_menu.h"
#include "playlist.h"
#include "procurador.h"

void ListarTodasPlaylistsMenu(App *app, Musica *mscOrig) {
    while (true) {
        system("@cls||clear");

        ListarTodasPlaylists(GetPlaylistsApp(app), 0,
                             GetQuantidadeLista(GetPlaylistsApp(app)));

        printf("[c] Criar Playlist\n");
        if (GetQuantidadeLista(GetPlaylistsApp(app)) > 0)
            printf("[d] Detalhar Playlist\n");
        printf("[q] Sair\n");

        char curr;
        scanf("%c%*c", &curr);

        if (curr == 'c') {
            char nome[30];

            printf("Digite um nome para a playlist:\n");
            scanf("%29[^\n]%*c", nome);
            if (strlen(nome) <= 1) {
                return;
            }

            Lista *playMscs = InicializaLista(); // Lista<string>

            Playlist *play = InicializaPlaylist(nome, playMscs);
            AdicionaElementoLista(GetPlaylistsApp(app), play);

            LiberaLista(playMscs, &free);

            printf("Playlist %s Criada!\n", nome);
            scanf("%*c");
        } else if (GetQuantidadeLista(GetPlaylistsApp(app)) > 0 &&
                   curr == 'd') {
            int indice;
            while (true) {
                system("@cls||clear");
                ListarTodasPlaylists(GetPlaylistsApp(app), 0,
                                     GetQuantidadeLista(GetPlaylistsApp(app)));

                printf("Digite o Indice da playlist desejada:\n");
                scanf("%d%*c", &indice);
                indice--;

                if (indice >= 0 &&
                    indice < GetQuantidadeLista(GetPlaylistsApp(app)))
                    break;

                ErroMenu("Ops! Indique um indice valido para detalhar a "
                         "playlist.");
            }

            Playlist *currPlay =
                AdquireElementoLista(GetPlaylistsApp(app), indice);

            DetalhaPlaylistMenu(app, currPlay, mscOrig);
        } else if (curr == 'q')
            return;

        else {
            ErroMenu("Ops! Acao invalida. Favor especificar funcionalidade "
                     "desejada");
        }
    }
}
