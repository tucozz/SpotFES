#include <stdio.h>
#include <stdlib.h>

#include "listar_todas_musicas_menu.h"

#include "console.h"
#include "detalha_musica_menu.h"

void ListarTodasMusicasMenu(App *app, Lista *musicas, Playlist *playlistOrig) {
    const int ritmoPaginacao = 30;
    int n = 0, m = ritmoPaginacao <= GetQuantidadeLista(musicas)
                       ? ritmoPaginacao
                       : GetQuantidadeLista(musicas);
    while (true) {
        bool primeiraPagina = n == 0;
        bool ultimaPagina = m == GetQuantidadeLista(musicas);

        system("@cls||clear");
        ListarTodasMusicas(musicas, n, m);

        printf("[f] Ver Detalhes de Música\n");
        if (!primeiraPagina)
            printf("[k] Voltar Página\n");

        if (!ultimaPagina)
            printf("[l] Próxima Página\n");

        printf("[q] Voltar Menu\n");

        char curr;
        scanf("%c%*c", &curr);
        if (curr == 'f') {
            int i = 0;
            do {
                system("@cls||clear");
                ListarTodasMusicas(musicas, n, m);
                printf("\nInforme o indice da musica: ");

                scanf("%d%*c", &i);

                if (i < 1 || i > GetQuantidadeLista(musicas)) {
                    system("@cls||clear");
                    printf(ANSI_COLOR_YELLOW
                           "Indice (%d) inválido." ANSI_COLOR_RESET
                           "\npressione ENTER para continuar",
                           i);
                    scanf("%*c");

                } else
                    break;
            } while (true);

            DetalhaMusicaMenu(app, AdquireElementoLista(musicas, i - 1),
                              playlistOrig);
        } else if (!primeiraPagina && curr == 'k') {
            m = n;
            n -= ritmoPaginacao;
        } else if (!ultimaPagina && curr == 'l') {
            n = m;
            m = m + ritmoPaginacao <= GetQuantidadeLista(musicas)
                    ? m + ritmoPaginacao
                    : GetQuantidadeLista(musicas);
        } else if (curr == 'q') {
            return;
        } else {
            printf(ANSI_COLOR_YELLOW
                   "Ops! Acao invalida. Favor especificar funcionalidade "
                   "desejada" ANSI_COLOR_RESET
                   "\npressione ENTER para continuar");
            scanf("%*c");
        }
    }
}
