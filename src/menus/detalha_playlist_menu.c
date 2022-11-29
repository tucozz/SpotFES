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
    CompletaPlaylist(currPlay, GetRepoMusicasApp(app));
    system("@cls||clear");
    DetalharPlaylist(currPlay);

    printf("pressione ENTER para continuar...");
    scanf("%*c");
}
