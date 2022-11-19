#include "console.h"
#include "artista.h"
#include "musica.h"
#include "playlist.h"

#include <stdio.h>
#include <string.h>

void ListarMusica(Musica *msc, int i) {
    int j;

    printf("%5d   | %17s", i, GetMscId(msc));
    if (strlen(GetMscId(msc)) > 17)
        printf("...");
    printf(" | %17s", GetMscName(msc));
    if (strlen(GetMscName(msc)) > 17)
        printf("...");
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

void ListarTodasMusicas(Lista *lista, int n, int m) {
    int i;

    printf("Indice: | Id:                 | Nome:             | Artistas:\n");

    for (i = n; i < m; i++) {
        ListarMusica(AdquireElementoLista(lista, i), i + 1);
        printf("\n");
    }
    printf("\n");
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
               GetArtName(AdquireElementoLista(GetMscArtists(msc), j)),
               GetArtId(AdquireElementoLista(GetMscArtists(msc), j)),
               GetArtSeguidores(AdquireElementoLista(GetMscArtists(msc), j)),
               GetArtPopularity(AdquireElementoLista(GetMscArtists(msc), j)));

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
    printf("%5d   | %17s", i, GetNomePlaylist(play));
    if (strlen(GetNomePlaylist(play)) > 17)
        printf("...");
    printf(" | %5d", GetQuantidadeLista(GetMusicasPlaylist(play)));
    printf("\n");
}

void ListarTodasPlaylists(Lista *lista, int n, int m) {
    int i;

    printf("Indice: | Nome:               | Numero de Musicas:\n");

    for (i = n; i < m; i++) {
        ListarPlaylist(AdquireElementoLista(lista, i), i + 1);
        printf("\n");
    }
    printf("\n");
}

void DetalharPlaylist(Playlist *play) {
    int i;

    printf("Nome: %s\n"
           "Numero de Musicas: %d\n"
           "Musicas:\n",
           GetNomePlaylist(play), GetQuantidadeLista(GetMusicasPlaylist(play)));
    for (i = 0; i < GetQuantidadeLista(GetMusicasIdPlaylist(play)); i++) {
        printf("%5d: %s\n", i,
               GetMscName(AdquireElementoLista(GetMusicasPlaylist(play), i)));
    }
    printf("\n");
}