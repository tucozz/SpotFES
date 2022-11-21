#include <stdio.h>
#include <stdlib.h>

#include "exportar_relatorio_menu.h"
#include "relatorio.h"

void ExportarRelatorioMenu(App *app) {
    system("@cls||clear");
    GerarRelatorio(GetRepoMusicasApp(app), GetRepoArtistasApp(app),
                   GetPlaylistsApp(app));
    printf(ANSI_COLOR_YELLOW "Relatório exportado." ANSI_COLOR_RESET
                             "\npressione ENTER para continuar");
    scanf("%*c");
}
