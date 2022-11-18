#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "relatorio.h"

#include "dicionario.h"
#include "par_chave_valor.h"
#include "procurador.h"

#define RELAT_MSC_FILE "./relatorio_musicas.csv"
#define RELAT_ART_FILE "./relatorio_artistas.csv"

static void SalvaMusicaCsv(FILE *fcsv, Musica *msc) {
    fprintf(fcsv, "%s;%s;%d;%d;%d;", GetMscId(msc), GetMscName(msc),
            GetMscPopularity(msc), GetMscDuration(msc), IsExplicit(msc));

    Lista *artistas = GetMscArtists(msc); // Lista<Artista *>
    int n = GetQuantidadeLista(artistas);

    for (int i = 0; i < n; i++) {
        Artista *curr = AdquireElementoLista(artistas, i);
        char *currNome = GetArtName(curr);
        fprintf(fcsv, "%s", currNome);
        if ((i + 1) < n)
            fprintf(fcsv, "%c", '|');
    }
    fprintf(fcsv, "%c", ';');

    for (int i = 0; i < n; i++) {
        Artista *curr = AdquireElementoLista(artistas, i);
        char *currId = GetArtId(curr);
        fprintf(fcsv, "%s", currId);
        if ((i + 1) < n)
            fprintf(fcsv, "%c", '|');
    }

    fprintf(fcsv, ";%s;%g;%g;%d;%g;%d;%g;%g;%g;%g;%g;%g;%d\n",
            GetMscReleaseDate(msc), GetMscDanceability(msc), GetMscEnergy(msc),
            GetMscKey(msc), GetMscLoudness(msc), GetMscMode(msc),
            GetMscSpeechiness(msc), GetMscAcousticness(msc),
            GetMscInstrumentalness(msc), GetMscLiveness(msc),
            GetMscValence(msc), GetMscTempo(msc), GetMscTimeSig(msc));
}

static void SalvaArtistaCsv(FILE *fcsv, Artista *art) {
    fprintf(fcsv, "%s;%d.0;", GetArtId(art), GetArtSeguidores(art));
    Lista *generos = GetArtGeneros(art); // Lista<string>
    int n = GetQuantidadeLista(generos);
    for (int i = 0; i < n; i++) {
        char *curr = AdquireElementoLista(generos, i);
        fprintf(fcsv, "%s", curr);
        if ((i + 1) < n)
            fprintf(fcsv, "%c", '|');
    }
    fprintf(fcsv, ";%s;%d\n", GetArtName(art), GetArtPopularity(art));
}

static int OrdenaDescListaPCVPorValor(const ParChaveValor *a, const ParChaveValor *b) {
    int lV = *(int *)GetValorParCV(a);
    int rV = *(int *)GetValorParCV(b);

    return rV - lV;
}

void GerarRelatorio(RepoMusicas *repoMsc, RepoArtistas *repoArt,
                    Lista *playlists) {
    // Dicionario<string, int>
    // Associa o hash de uma musica com o numero de
    // vezes que ela se repete na playlist
    Dicionario *musicasQtd = InicializaDicionario(&strcmp, &free, &free);
    // Dicionario<string, Musica *>
    // Associa o hash de uma musica com sua representacao
    Dicionario *musicas = InicializaDicionario(&strcmp, &free, &LiberaMusica);

    int n = GetQuantidadeLista(playlists);
    for (int i = 0; i < n; i++) {
        Playlist *currPlay = AdquireElementoLista(playlists, i);
        CompletaPlaylist(currPlay, repoMsc);

        Lista *currPlayMscs = GetMusicasPlaylist(currPlay); // Lista<Musica *>
        int m = GetQuantidadeLista(currPlayMscs);
        for (int j = 0; j < m; j++) {
            Musica *currMsc = AdquireElementoLista(currPlayMscs, j);
            if (currMsc == NULL)
                continue;

            char *currMscHash = GetMscId(currMsc);

            // Ponteiro para o ponteiro do valor do ParChaveValor<string, int>
            void **dicValQtd =
                GetValorDicionario(musicasQtd, currMscHash, &strdup);
            if (*dicValQtd == NULL) {
                *dicValQtd = malloc(sizeof(int));
                *((int *)*dicValQtd) = 1;
            } else {
                *((int *)*dicValQtd) += 1;
            }

            void **dicValMsc =
                GetValorDicionario(musicas, currMscHash, &strdup);
            if (*dicValMsc == NULL) {
                CompletaMusica(currMsc, repoArt);
                *dicValMsc = CopiaMusica(currMsc);
            }
        }
    }

    // Lista<ParChaveValor<string, int>>
    Lista *paresMscQtd = GetTodosParesDicionario(musicasQtd);

    OrdenaLista(paresMscQtd, &OrdenaDescListaPCVPorValor);

    FILE *fcsv = fopen(RELAT_MSC_FILE, "w");

    n = GetQuantidadeLista(paresMscQtd);
    for (int i = 0; i < n; i++) {
        ParChaveValor *curr = AdquireElementoLista(paresMscQtd, i);
        char *hash = GetChaveParCV(curr);
        void **ptrmsc = GetValorDicionario(musicas, hash, &strdup);
        SalvaMusicaCsv(fcsv, *ptrmsc);
    }

    fclose(fcsv);

    // Dicionario<string, int>
    // Associa o hash de um Artista * com o numero de
    // vezes que ele se repete na playlist
    Dicionario *artistasQtd = InicializaDicionario(&strcmp, &free, &free);
    // Dicionario<string, Artista *>
    // Associa o hash de um Artista * com sua representacao
    Dicionario *artistas = InicializaDicionario(&strcmp, &free, &LiberaArtista);

    for (int i = 0; i < n; i++) {
        Musica *currMsc = GetValorParCV(
            AdquireElementoLista(GetTodosParesDicionario(musicas), i));

        Lista *currMscArts = GetMscArtists(currMsc); // Lista<Artista *>
        int m = GetQuantidadeLista(currMscArts);
        for (int j = 0; j < m; j++) {
            Artista *currArt = AdquireElementoLista(currMscArts, j);
            if (currArt == NULL)
                continue;

            char *currArtHash = GetArtId(currArt);

            // Ponteiro para o ponteiro do valor do ParChaveValor<string, int>
            void **dicValQtd =
                GetValorDicionario(artistasQtd, currArtHash, &strdup);
            if (*dicValQtd == NULL) {
                *dicValQtd = malloc(sizeof(int));
                *((int *)*dicValQtd) = 1;
            } else {
                *((int *)*dicValQtd) += 1;
            }

            void **dicValArt =
                GetValorDicionario(artistas, currArtHash, &strdup);
            if (*dicValArt == NULL) {
                *dicValArt = CopiaArtista(currArt);
            }
        }
    }

    // Lista<ParChaveValor<string, int>>
    Lista *paresArtQtd = GetTodosParesDicionario(artistasQtd);

    OrdenaLista(paresArtQtd, &OrdenaDescListaPCVPorValor);

    fcsv = fopen(RELAT_ART_FILE, "w");

    n = GetQuantidadeLista(paresArtQtd);
    for (int i = 0; i < n; i++) {
        ParChaveValor *curr = AdquireElementoLista(paresArtQtd, i);
        char *hash = GetChaveParCV(curr);
        void **ptrmsc = GetValorDicionario(artistas, hash, &strdup);
        SalvaArtistaCsv(fcsv, *ptrmsc);
    }

    fclose(fcsv);

    LiberaDicionario(musicasQtd);
    LiberaDicionario(musicas);
    LiberaDicionario(artistasQtd);
    LiberaDicionario(artistas);
}
