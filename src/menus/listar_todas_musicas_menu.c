#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "listar_todas_musicas_menu.h"

#include "console.h"
#include "detalha_musica_menu.h"

void ListarTodasMusicasMenu(App *app, Lista *musicas, Playlist *playlistOrig) {
        system("@cls||clear");
        ListarTodasMusicas(musicas, 0, GetQuantidadeLista(musicas));

        printf("pressione ENTER para continuar...");
        scanf("%*c");
}
