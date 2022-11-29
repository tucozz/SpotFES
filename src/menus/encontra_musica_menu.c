#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encontra_musica_menu.h"

#include "console.h"
#include "listar_todas_musicas_menu.h"

void EncontraMusicaMenu(App *app, Playlist *playlistOrig) {
    char buffer[64] = "";
    system("@cls||clear");
    printf("(submeter uma entrada vazia abandona a busca e volta para o "
           "último menu)\n"
           "Digite o nome da música pela qual quer procurar: ");
    scanf("%63[^\n]%*c", buffer);
    if (strlen(buffer) < 1) {
        return;
    }

    // Lista<Musica *>
    Lista *resultado =
        EncontraPeloNomeRepoMusica(GetRepoMusicasApp(app), buffer);
    if (GetQuantidadeLista(resultado) == 0) {
        system("@cls||clear");
        printf(ANSI_COLOR_YELLOW "Nenhuma música encontrada." ANSI_COLOR_RESET
                                 "\npressione ENTER para continuar");
        scanf("%*c");
    } else {
        SetMusicasApp(app, resultado);
        ListarTodasMusicasMenu(app, resultado, playlistOrig);
    }
}
