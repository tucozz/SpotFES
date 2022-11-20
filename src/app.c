#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"

#include "console.h"
#include "exception.h"
#include "procurador.h"
#include "relatorio.h"
#include "repositorio_artistas.h"
#include "repositorio_musicas.h"
#include "repositorio_playlists.h"

/**
 * @brief Procura por uma musica e lista elas
 *
 * @param app O @ref App*
 * @param playlistOrig Pode ser NULL; é a playlist que invocou esse menu a
 * procura de uma musica para adicionar nela
 */
static void EncontraMusicaMenu(App *app, Playlist *playlistOrig);

static void ListarTodasMusicasMenu(App *app, Lista *musicas,
                                   Playlist *playlistOrig);

static void DetalhaMusicaMenu(App *app, Musica *msc, Playlist *playlistOrig);

/**
 * @brief Lista todas as playlists do usuário
 *
 * @param app O @ref App*
 * @param mscOrig Pode ser NULL; é a musica que invocou esse menu querendo se
 * adicionar numa playlist
 */
static void ListarTodasPlaylistsMenu(App *app, Musica *mscOrig);

static void ExportarRelatorioMenu(App *app);

static void SairAppMenu(App *app);

static void AbrirMusicaNoNavegador(const Musica *msc);

static void SobreMenu();

struct tApp {
    RepoMusicas *repoMsc;
    RepoArtistas *repoArt;
    Lista *playlists; // Lista<playlist>
};

App *InicializaApp(const char *musicascsv, const char *artistascsv) {
    App *app = malloc(sizeof *app);
    if (app == NULL)
        throwOutOfMemoryException("App malloc failed");

    app->repoMsc = InicializaRepoMusicas(musicascsv);
    app->repoArt = InicializaRepoArtistas(artistascsv);
    app->playlists = CarregaTodasPlaylistsRepo();

    return app;
}

void *LiberaApp(App *app) {
    LiberaRepoMusicas(app->repoMsc);
    LiberaRepoArtistas(app->repoArt);

    LiberaLista(app->playlists, &LiberaPLaylist);

    free(app);

    return NULL;
}

static void ListarTodasPlaylistsMenu(App *app, Musica *mscOrig) {
    while (true) {
        int indice, i;

        system("@cls||clear");

        ListarTodasPlaylists(app->playlists, 0,
                             GetQuantidadeLista(app->playlists));

        printf("[c] Criar Playlist\n"
               "[d] Detalhar Playlist\n"
               "[q] Sair\n");

        char curr;
        scanf("%c%*c", &curr);

        switch (curr) {
        case 'c':;
            char nome[30];

            printf("Digite um nome para a playlist:\n");
            scanf("%29[^\n]%*c", nome);
            if (strlen(nome) <= 1) {
                return;
            }

            Playlist *play = InicializaPlaylist(nome, InicializaLista());
            AdicionaElementoLista(app->playlists, play);

            printf("Playlist %s Criada!\n", nome);
            break;

        case 'd':;
            printf("Digite o Indice da playlist desejada:\n");
            scanf("%d%*c", &indice);
            system("@cls||clear");
            CompletaPlaylist(AdquireElementoLista(app->playlists, indice), app->repoMsc);
            DetalharPlaylist(AdquireElementoLista(app->playlists, indice));

            printf("[r] Recomendar Musicas Semelhantes\n"
                   "[a] Adicionar Musica na Playlist\n"
                   "[q] Sair\n");

            char option;
            scanf("%c%*c", &option);

            switch (option) {
            case 'r':;
                printf("Quantas musicas recomendadas deseja?\n");
                char k;
                scanf("%c%*c", &k);

                Lista *recomendadas = InicializaLista;
                recomendadas = RecomendaMusicas(
                    AdquireElementoLista(app->playlists, indice), k,
                    app->repoMsc);

                for (i = 0; i < k; i++) {
                    ListarMusica(AdquireElementoLista(recomendadas, i), i);
                }

                LiberaLista(recomendadas, LiberaMusica);
                break;

            case 'a':;
                if (mscOrig != NULL) {
                    AdicionaElementoLista(
                        AdquireElementoLista(app->playlists, indice), mscOrig);
                    printf("Musica Adicionada!\n");
                    break;
                }

                EncontraMusicaMenu(
                    app, AdquireElementoLista(app->playlists, indice));
                break;

            case 'q':;
                return;

            default:
                printf(ANSI_COLOR_YELLOW
                       "Ops! Acao invalida. Favor especificar "
                       "funcionalidade " ANSI_COLOR_RESET
                       "desejada\npressione ENTER para continuar");
                scanf("%*c");
                continue;
            }

            break;

        case 'q':;
            return;

        default:
            printf(ANSI_COLOR_YELLOW "Ops! Acao invalida. Favor especificar "
                                     "funcionalidade " ANSI_COLOR_RESET
                                     "desejada\n");
            scanf("%*c");
            continue;
        }
    }
}

void RodaApp(App *app) {
    bool primeiraVez = true;

    while (true) {
        system("@cls||clear");

        printf("%c", '\n');
        ImprimeMarca(primeiraVez);
        printf("%c", '\n');
        primeiraVez = false;

        printf("[f] Encontrar Música\n"
               "[g] Listar suas Playlists\n"
               "[r] Exportar Relatório\n"
               "[b] Sobre\n"
               "[q] Sair\n");

        char curr;
        scanf("%c%*c", &curr);
        switch (curr) {
        case 'f':;
            EncontraMusicaMenu(app, NULL);
            break;

        case 'g':;
            ListarTodasPlaylistsMenu(app, NULL);
            break;

        case 'r':;
            ExportarRelatorioMenu(app);
            break;

        case 'b':;
            SobreMenu();
            break;

        case 'q':;
            SairAppMenu(app);
            return;

        default:
            printf(ANSI_COLOR_YELLOW "Ops! Acao invalida. Favor especificar "
                                     "funcionalidade desejada " ANSI_COLOR_RESET
                                     "\npressione ENTER para continuar");
            scanf("%*c");
            continue;
        }
    }
}

static void EncontraMusicaMenu(App *app, Playlist *playlistOrig) {
    char buffer[64] = "";
    system("@cls||clear");
    printf("(submeter uma entrada vazia abandona a busca e volta para o "
           "último menu)\n"
           "Digite o nome da música pela qual quer procurar: ");
    scanf("%63[^\n]%*c", buffer);
    if (strlen(buffer) <= 1) {
        return;
    }

    // Lista<Musica *>
    Lista *resultado = EncontraPeloNomeRepoMusica(app->repoMsc, buffer);
    if (GetQuantidadeLista(resultado) == 0) {
        system("@cls||clear");
        printf(ANSI_COLOR_YELLOW "Nenhuma música encontrada." ANSI_COLOR_RESET
                                 "\npressione ENTER para continuar");
        scanf("%*c");
    } else
        ListarTodasMusicasMenu(app, resultado, playlistOrig);

    LiberaLista(resultado, &LiberaMusica);
}

static void ListarTodasMusicasMenu(App *app, Lista *musicas,
                                   Playlist *playlistOrig) {
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

                while (scanf("%d%*c", &i) != 1) {
                }

                if (i < 1 || i > GetQuantidadeLista(musicas)) {
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

static void DetalhaMusicaMenu(App *app, Musica *msc, Playlist *playlistOrig) {
    CompletaMusica(msc, app->repoArt);

    do {
        system("@cls||clear");
        DetalharMusica(msc);

        printf("[f] Escutar Música\n"
               "[a] Adicionar Música à Playlist\n"
               "[q] Voltar Menu\n");

        char curr;
        scanf("%c%*c", &curr);
        switch (curr) {
        case 'f':;
            AbrirMusicaNoNavegador(msc);
            printf(ANSI_COLOR_YELLOW
                   "Abrindo música no navegador..." ANSI_COLOR_RESET
                   "\npressione ENTER para voltar ao SpotFES");
            scanf("%*c");
            break;

        case 'a':;
            if (playlistOrig != NULL) {
                bool status = AdicionaMusicaPlaylist(playlistOrig, msc);
                if (status) {
                    printf(ANSI_COLOR_YELLOW
                           "Música adicionada" ANSI_COLOR_RESET
                           "\npressione ENTER para continuar");
                    scanf("%*c");
                    return;
                }

                printf(ANSI_COLOR_YELLOW
                       "Essa música já está na sua playlist" ANSI_COLOR_RESET
                       "\npressione ENTER para continuar");
                scanf("%*c");
                break;
            }

            ListarTodasPlaylistsMenu(app, msc);
            break;

        case 'q':;
            return;

        default:
            printf(ANSI_COLOR_YELLOW "Ops! Acao invalida. Favor especificar "
                                     "funcionalidade desejada" ANSI_COLOR_RESET
                                     "\npressione ENTER para continuar");
            scanf("%*c");
            break;
        }
    } while (true);
}

static void ExportarRelatorioMenu(App *app) {
    system("@cls||clear");
    GerarRelatorio(app->repoMsc, app->repoArt, app->playlists);
    printf(ANSI_COLOR_YELLOW "Relatório exportado." ANSI_COLOR_RESET
                             "\npressione ENTER para continuar");
    scanf("%*c");
}

static void SairAppMenu(App *app) {
    system("@cls||clear");
    printf("Volte sempre!\n");
    SalvaTodasPlaylistsRepo(app->playlists);
}

static void SobreMenu() {
    system("@cls||clear");
    ImprimeSobre(true);
    scanf("%*c");
}

static void AbrirMusicaNoNavegador(const Musica *msc) {
    char command[256] = "xdg-open https://open.spotify.com/track/";
    strcat(command, GetMscId(msc));
    system(command);
}
