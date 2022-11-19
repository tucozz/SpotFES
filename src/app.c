#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"

#include "console.h"
#include "exception.h"
#include "procurador.h"
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

static void GerarRelatorioMenu(App *app);

static void SairAppMenu(App *app);

static void AbrirMusicaNoNavegador(const Musica *msc);

struct tApp {
    RepoMusicas *repoMsc;
    RepoArtistas *repoArt;
    Lista *playlists; // Lista<playlist>
};

App *InicializaApp(const char *artistascsv, const char *musicascsv) {
    App *app = malloc(sizeof *app);
    if (app == NULL)
        throwOutOfMemoryException("App malloc failed");

    app->repoMsc = InicializaRepoMusicas(musicascsv);
    app->repoArt = InicializaRepoArtistas(musicascsv);
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

        for (i = 0; i < GetQuantidadeLista(app->playlists); i++) {
            ListarPlaylist(app->playlists, i);
        }

        printf("[c] Criar Playlist\n"
               "[d] Detalhar Playlist\n"
               "[q] Sair\n");

        char curr;
        scanf("%c%*c", &curr);

        switch (curr) {
        case 'c':;
            char *nome;

            printf("Digite um nome para a playlist:\n");
            scanf("%s", nome);

            Playlist *play = InicializaPlaylist(nome, NULL);
            AdicionaElementoLista(app->playlists, play);

            printf("Playlist %s Criada!\n");
            break;

        case 'd':;
            printf("Digite o Indice da playlist desejada:\n");
            scanf("%c%*c", &indice);
            break;

        case 'q':;
            SairAppMenu(app);
            return;

        default:
            printf("Ops! Acao invalida. Favor especificar funcionalidade "
                   "desejada\n");
            continue;
        }
    }
}

void RodaApp(App *app) {
    while (true) {
        system("@cls||clear");
        printf("[f] Encontrar Música\n"
               "[g] Listar suas Playlists\n"
               "[r] Gerar Relatório\n"
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
            GerarRelatorioMenu(app);
            break;

        case 'q':;
            SairAppMenu(app);
            return;

        default:
            printf("Ops! Acao invalida. Favor especificar funcionalidade "
                   "desejada\npressione ENTER para continuar");
            scanf("%*c");
            continue;
        }
    }
}

static void EncontraMusicaMenu(App *app, Playlist *playlistOrig) {
    char *buffer = NULL;
    do {
        system("@cls||clear");
        printf("(submeter uma entrada vazia abandona a busca e volta para o "
               "último menu)\n"
               "Digite o nome da música pela qual quer procurar: ");

    } while (getline(&buffer, NULL, stdin) == -1);
    if (strlen(buffer) <= 1) {
        free(buffer);
        return;
    }

    // Lista<Musica *>
    Lista *resultado = EncontraPeloNomeRepoMusica(app->repoMsc, buffer);
    free(buffer);

    ListarTodasMusicasMenu(app, resultado, playlistOrig);
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
                printf("\nInforme o indice da musica: ");

                while (scanf("%d%*c", &i) != 1) {
                }

                if (i < 1 || i > GetQuantidadeLista(musicas)) {
                    printf("Indice (%d) inválido.\npressione ENTER para "
                           "continuar");
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
            printf("Ops! Acao invalida. Favor especificar funcionalidade "
                   "desejada\npressione ENTER para continuar");
            scanf("%*c");
        }
    }
}

static void DetalhaMusicaMenu(App *app, Musica *msc, Playlist *playlistOrig) {
    CompletaMusica(msc, app->repoArt);

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
        printf("Abrindo música no navegador...\npressione ENTER para voltar ao "
               "SpotFES");
        scanf("%*c");
        break;

    case 'a':;
        if (playlistOrig != NULL) {
            bool status = AdicionaMusicaPlaylist(playlistOrig, msc);
            if (status) {
                printf("Música adicionada\npressione ENTER para continuar");
                scanf("%*c");
                return;
            }

            printf("Essa música já está na sua playlist\npressione ENTER "
                   "para continuar");
            scanf("%*c");
            break;
        }

        ListarTodasPlaylistsMenu(app, msc);
        break;

    case 'q':;
        return;

    default:
        printf("Ops! Acao invalida. Favor especificar funcionalidade "
               "desejada\npressione ENTER para continuar");
        scanf("%*c");
        break;
    }
}

static void GerarRelatorioMenu(App *app) {
    system("@cls||clear");
    // TODO: isso
}

static void SairAppMenu(App *app) {
    system("@cls||clear");
    printf("Volte sempre!\n");
    SalvaTodasPlaylistsRepo(app->playlists);
}

static void AbrirMusicaNoNavegador(const Musica *msc) {
    char command[256] = "xdg-open https://open.spotify.com/track/";
    strcat(command, GetMscId(msc));
    system(command);
}
