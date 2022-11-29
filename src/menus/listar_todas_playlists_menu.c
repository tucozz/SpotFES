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
    system("@cls||clear");

    ListarTodasPlaylists(GetPlaylistsApp(app), 0,
                         GetQuantidadeLista(GetPlaylistsApp(app)));

    printf("pressione ENTER para continuar...");
    scanf("%*c");
}
