#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "detalha_playlist_menu.h"

#include "console.h"
#include "encontra_musica_menu.h"
#include "erro_menu.h"
#include "listar_todas_musicas_menu.h"
#include "procurador.h"

void DetalhaPlaylistMenu(App *app, Playlist *currPlay, Musica *mscOrig) {
    while (true) {
        system("@cls||clear");

        CompletaPlaylist(currPlay, GetRepoMusicasApp(app));
        DetalharPlaylist(currPlay);

        if (GetQuantidadeLista(GetMusicasPlaylist(currPlay)) > 0)
            printf("[r] Recomendar Musicas Semelhantes\n");
        printf("[a] Adicionar Musica na Playlist\n"
               "[q] Sair\n");

        char option;
        scanf("%c%*c", &option);

        if (GetQuantidadeLista(GetMusicasPlaylist(currPlay)) > 0 && option == 'r') {
            printf("Quantas musicas recomendadas deseja?\n");
            int k;
            scanf("%d%*c", &k);

            Lista *recomendadas =
                RecomendaMusicas(currPlay, k, GetRepoMusicasApp(app));

            ListarTodasMusicasMenu(app, recomendadas, currPlay);

            LiberaLista(recomendadas, &LiberaMusica);
        } else if (option == 'a') {
            if (mscOrig != NULL)
                if (AdicionaMusicaPlaylist(currPlay, mscOrig))
                    printf("Musica Adicionada!\n");
                else
                    printf("Esta musica ja está na playlist!\n");
            else
                EncontraMusicaMenu(app, currPlay);
        } else if (option == 'q')
            return;
        else {
            ErroMenu("Ops! Acao invalida. Favor especificar funcionalidade "
                     "desejada");
        }
    }
}
