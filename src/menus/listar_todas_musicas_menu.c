#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "listar_todas_musicas_menu.h"

#include "console.h"
#include "detalha_musica_menu.h"

void ListarTodasMusicasMenu(App *app, Lista *musicas, Playlist *playlistOrig) {
    const int ritmoPaginacao = 30;
    int n = 0;
    while (true) {
        bool primeiraPagina = n == 0;
        bool ultimaPagina = n + ritmoPaginacao >= GetQuantidadeLista(musicas);

        system("@cls||clear");
        ListarTodasMusicas(musicas, n, ritmoPaginacao);

        printf("[f] Ver Detalhes de Música\n");
        if (!primeiraPagina)
            printf("[k] Voltar Página\n");

        if (!ultimaPagina)
            printf("[l] Próxima Página\n");
        if (GetQuantidadeLista(musicas) > ritmoPaginacao)
            printf("[g] Navegar para página\n");
        printf("[q] Voltar Menu\n");

        char curr;
        scanf("%c%*c", &curr);
        if (curr == 'f') {
            int i = 0;
            do {
                system("@cls||clear");
                ListarTodasMusicas(musicas, n, ritmoPaginacao);
                printf("\nInforme o indice da musica: ");

                scanf("%d%*c", &i);

                if (i > 0 && i <= GetQuantidadeLista(musicas))
                    break;

                system("@cls||clear");
                printf(ANSI_COLOR_YELLOW
                       "Indice (%d) inválido." ANSI_COLOR_RESET
                       "\npressione ENTER para continuar",
                       i);
                scanf("%*c");
            } while (true);

            DetalhaMusicaMenu(app, AdquireElementoLista(musicas, i - 1),
                              playlistOrig);
        } else if (!primeiraPagina && curr == 'k') {
            n -= ritmoPaginacao;
        } else if (!ultimaPagina && curr == 'l') {
            n += ritmoPaginacao;
        } else if (GetQuantidadeLista(musicas) > ritmoPaginacao && curr == 'g') {
            int i = 0;
            do {
                system("@cls||clear");
                ListarTodasMusicas(musicas, n, ritmoPaginacao);
                printf("\nInforme a pagina: ");

                scanf("%d%*c", &i);

                if (i > 0 && i <= ceilf((float)GetQuantidadeLista(musicas) / ritmoPaginacao)) {
                    i--;
                    n = ritmoPaginacao * i;
                    break;
                }

                system("@cls||clear");
                printf(ANSI_COLOR_YELLOW
                       "Página (%d) inválida." ANSI_COLOR_RESET
                       "\npressione ENTER para continuar",
                       i);
                scanf("%*c");
            } while (true);
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
