#include <stdio.h>
#include <stdlib.h>

#include "repositorio_playlists.h"
#include "sair_app_menu.h"

void SairAppMenu(App *app) {
    SalvaTodasPlaylistsRepo(GetPlaylistsApp(app));
    system("@cls||clear");
    printf("Volte sempre!\n");
}
