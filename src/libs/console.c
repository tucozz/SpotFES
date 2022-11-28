#include "console.h"
#include "artista.h"
#include "musica.h"
#include "playlist.h"
#include "sleeper.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

void ListarMusica(Musica *msc, int i) {
    int j;

    printf("%5d   | %s | ", i, GetMscId(msc));
    if (strlen(GetMscName(msc)) > 30)
        printf("%.27s...", GetMscName(msc));
    if (strlen(GetMscName(msc)) < 30)
        printf("%30s", GetMscName(msc));
    if (strlen(GetMscName(msc)) == 30)
        printf("%s", GetMscName(msc));
    printf(" | ");
    if (GetMscArtistsName(msc) == NULL)
        for (j = 0; j < (GetQuantidadeLista(GetMscArtists(msc))); j++)
            printf("%s, ",
                   GetArtName(AdquireElementoLista(GetMscArtists(msc), j)));

    else
        for (j = 0; j < (GetQuantidadeLista(GetMscArtistsName(msc))); j++)
            printf("%s, ",
                   (char *)AdquireElementoLista(GetMscArtistsName(msc), j));

    printf("\n");
}

void ListarTodasMusicas(Lista *lista, int n, int tamPag) {
    int i;

    printf("Indice: | Id:                    | Nome:                          | Artistas:\n");

    int qtd = GetQuantidadeLista(lista);
    for (i = 0; i < tamPag && i + n < qtd; i++) {
        ListarMusica(AdquireElementoLista(lista, i + n), i + n);
    }

    printf("\nEncontrados %d resultados%50s", qtd, " ");
    int currpag = n / tamPag + 1;
    printf("%d / %.0lf\n\n", currpag, ceilf((float)qtd / tamPag));    
}

void DetalharMusica(Musica *msc) {
    int i, j;

    printf("Nome: %s\n"
           "Id: %s\n"
           "Popularidade: %d\n"
           "Duracao: %dms\n"
           "Explicit: %d\n"
           "Data de Lancamento: %s\n"
           "Danceability: %f\n"
           "Energy: %f\n"
           "Key: %d\n"
           "Loudness: %f\n"
           "Speechiness: %f\n"
           "Acousticness: %f\n"
           "Instrumentalness: %f\n"
           "Liveness: %f\n"
           "Valence: %f\n"
           "Tempo: %f\n"
           "Time Signature: %d\n\n"
           "Artistas:\n",
           GetMscName(msc), GetMscId(msc), GetMscPopularity(msc),
           GetMscDuration(msc), IsExplicit(msc), GetMscReleaseDate(msc),
           GetMscDanceability(msc), GetMscEnergy(msc), GetMscKey(msc),
           GetMscLoudness(msc), GetMscSpeechiness(msc), GetMscAcousticness(msc),
           GetMscInstrumentalness(msc), GetMscLiveness(msc), GetMscValence(msc),
           GetMscTempo(msc), GetMscTimeSig(msc));

    for (i = 0; i < (GetQuantidadeLista(GetMscArtists(msc))); i++) {
        printf("Nome: %s\n"
               "Id: %s\n"
               "Seguidores: %d\n"
               "Popularidade: %d\n",
               GetArtName(AdquireElementoLista(GetMscArtists(msc), i)),
               GetArtId(AdquireElementoLista(GetMscArtists(msc), i)),
               GetArtSeguidores(AdquireElementoLista(GetMscArtists(msc), i)),
               GetArtPopularity(AdquireElementoLista(GetMscArtists(msc), i)));

        printf("Generos: ");
        for (j = 0; j < GetQuantidadeLista(GetArtGeneros(
                            AdquireElementoLista(GetMscArtists(msc), i)));
             j++) {
            printf("%s, ", (char *)AdquireElementoLista(
                               GetArtGeneros(
                                   AdquireElementoLista(GetMscArtists(msc), i)),
                               j));
        }
        printf("\n\n");
    }
}

void ListarPlaylist(Playlist *play, int i) {
    printf("%5d   | ", i);
    if (strlen(GetNomePlaylist(play)) > 27)
        printf("%.27s...", GetNomePlaylist(play));
    if (strlen(GetNomePlaylist(play)) < 27)
        printf("%30s", GetNomePlaylist(play));
    if (strlen(GetNomePlaylist(play)) == 27)
        printf("%s", GetNomePlaylist(play));
    printf(" | %5d", GetQuantidadeLista(GetMusicasIdPlaylist(play)));
    printf("\n");
}

void ListarTodasPlaylists(Lista *lista, int n, int m) {
    int i;

    printf("Indice: | Nome:                          | Numero de Musicas:\n");

    for (i = n; i < m; i++) {
        ListarPlaylist(AdquireElementoLista(lista, i), i + 1);
    }
    printf("\n");
}

void DetalharPlaylist(Playlist *play) {
    int i;

    printf("Nome: %s\n"
           "Numero de Musicas: %d\n"
           "Musicas:\n",
           GetNomePlaylist(play),
           GetQuantidadeLista(GetMusicasIdPlaylist(play)));
    for (i = 0; i < GetQuantidadeLista(GetMusicasIdPlaylist(play)); i++) {
        Musica *msc = AdquireElementoLista(GetMusicasPlaylist(play), i);
        printf("%5d: %s\n", i, msc == NULL ? "-" : GetMscName(msc));
    }
    printf("\n");
}

void ImprimeDelay(char str[], bool en, int delay) {
    for (int i = 0; i < strlen(str); i++, en && msleep(delay))
        printf("%c", str[i]);
}

void ImprimeMarca(bool animacao) {
    char marca[] =
        " .d8888b.                                   888         8888888888      8888888888       .d8888b.          \n"
        "d88P  Y88b                                  888         888             888             d88P  Y88b        \n"
        "Y88b.                                       888         888             888             Y88b.             \n"
        " \"Y888b.        88888b.        .d88b.       888888      8888888         8888888          \"Y888b.        \n"
        "    \"Y88b.      888 \"88b      d88\"\"88b      888         888             888                 \"Y88b.   \n"
        "      \"888      888  888      888  888      888         888             888                   \"888      \n"
        "Y88b  d88P      888 d88P      Y88..88P      Y88b.       888             888             Y88b  d88P        \n"
        " \"Y8888P\"       88888P\"        \"Y88P\"        \"Y888      888             8888888888       \"Y8888P\" \n"
        "                888                                                                                       \n"
        "                888                                                                                       \n"
        "                888                                                                                       \n";

    printf(ANSI_COLOR_GREEN);

    ImprimeDelay(marca, animacao, 2);

    printf(ANSI_COLOR_RESET);

    if (animacao)
        msleep(512);
}

void ImprimeSobre(bool animacao) {
    int delay = 0;
    if (animacao)
        delay = 1;

    char logo[] =
        " ⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣤⣶⣶⣶⣶⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀ \n"
        " ⠀⠀⠀⠀⢀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⡀⠀⠀⠀⠀ \n"
        " ⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠀⠀⠀ \n"
        " ⠀⢀⣾⣿⡿⠿⠛⠛⠛⠉⠉⠉⠉⠛⠛⠛⠿⠿⣿⣿⣿⣿⣿⣷⡀⠀ \n"
        " ⠀⣾⣿⣿⣇⠀⣀⣀⣠⣤⣤⣤⣤⣤⣀⣀⠀⠀⠀⠈⠙⠻⣿⣿⣷⠀ \n"
        " ⢠⣿⣿⣿⣿⡿⠿⠟⠛⠛⠛⠛⠛⠛⠻⠿⢿⣿⣶⣤⣀⣠⣿⣿⣿⡄ \n"
        " ⢸⣿⣿⣿⣿⣇⣀⣀⣤⣤⣤⣤⣤⣄⣀⣀⠀⠀⠉⠛⢿⣿⣿⣿⣿⡇ \n"
        " ⠘⣿⣿⣿⣿⣿⠿⠿⠛⠛⠛⠛⠛⠛⠿⠿⣿⣶⣦⣤⣾⣿⣿⣿⣿⠃ \n"
        " ⠀⢿⣿⣿⣿⣿⣤⣤⣤⣤⣶⣶⣦⣤⣤⣄⡀⠈⠙⣿⣿⣿⣿⣿⡿⠀ \n"
        " ⠀⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⡿⠁⠀ \n"
        " ⠀⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠀⠀⠀ \n"
        " ⠀⠀⠀⠀⠈⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁⠀⠀⠀⠀ \n"
        " ⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⠛⠿⠿⠿⠿⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀ \n"
        "\n";
    char txt[] =
        ANSI_COLOR_YELLOW
        "          SpotFES\n"
        ANSI_COLOR_RESET
        "\n"
        "  Arthur Estefanato Lopes\n"
        "     Jheam Storch Ross\n"
        "\n"
        "🛇  Nenhum Direito Reservado\n";

    printf(ANSI_COLOR_GREEN);

    ImprimeDelay(logo, true, delay);

    printf(ANSI_COLOR_RESET);

    ImprimeDelay(txt, true, delay);
}
