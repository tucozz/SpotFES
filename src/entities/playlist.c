#include <stdlib.h>
#include <string.h>

#include "playlist.h"

#include "exception.h"

struct tPlaylist {
    char *nome;
    Lista *musicas;    // Lista<musica>
    Lista *musicas_id; // Lista<string>
};

Playlist *InicializaPlaylist(const char *nome, const Lista *musicas_id) {
    Playlist *playlist = malloc(sizeof *playlist);
    if (playlist == NULL)
        throwOutOfMemoryException("Musica malloc failed");

    playlist->nome = strdup(nome);
    if (playlist->nome == NULL)
        throwOutOfMemoryException("Playlist internal nome strdup failed");

    playlist->musicas = NULL;
    playlist->musicas_id = CopiaLista(musicas_id, &strdup);

    return playlist;
}

void LiberaPLaylist(Playlist *playlist) {
    free(playlist->nome);

    if (playlist->musicas != NULL)
        LiberaLista(playlist->musicas, &LiberaMusica);

    LiberaLista(playlist->musicas_id, &free);

    free(playlist);
}

char *GetNomePlaylist(Playlist *playlist) { return playlist->nome; }

Lista *GetMusicasPlaylist(Playlist *playlist) { return playlist->musicas; }

Lista *GetMusicasIdPlaylist(Playlist *playlist) { return playlist->musicas_id; }

bool IncluiMusicasPlaylist(Playlist *playlist, const Lista *musicas) {
    if (playlist->musicas != NULL || musicas == NULL)
        return false;

    playlist->musicas = CopiaLista(musicas, &CopiaMusica);

    return true;
}

bool AdicionaMusicaPlaylist(Playlist *playlist, const Musica *msc) {
    if (msc == NULL)
        return false;

    if (EncontraLista(playlist->musicas_id, GetMscId(msc), &strcmp) != NULL)
        return false;

    if (playlist->musicas != NULL)
        AdicionaElementoLista(playlist->musicas, CopiaMusica(msc));

    char *msc_id = strdup(GetMscId(msc));
    if (msc_id == NULL)
        throwOutOfMemoryException(
            "Playlist internal AdicionaMusicaPlaylist msc_id strdup failed");

    AdicionaElementoLista(playlist->musicas_id, msc_id);

    return true;
}

Playlist *CopiaPlaylist(const Playlist *playlist) {
    Playlist *cpy = InicializaPlaylist(playlist->nome, playlist->musicas_id);

    return cpy;
}

Musica *CriaMusicaMedia(const Playlist *play) {
    int i;

    float danceabilityM = 0;
    float energyM = 0;
    float loudnessM = 0;
    float speechinessM = 0;
    float acousticnessM = 0;
    float instrumentalnessM = 0;
    float livenessM = 0;
    float valenceM = 0;
    float tempoM = 0;

    for (i = 0; i < GetQuantidadeLista(GetMusicasPlaylist(play)); i++) {
        danceabilityM += GetMscDanceability(AdquireElementoLista(play, i));
        energyM += GetMscEnergy(AdquireElementoLista(play, i));
        loudnessM += GetMscLoudness(AdquireElementoLista(play, i));
        speechinessM += GetMscSpeechiness(AdquireElementoLista(play, i));
        acousticnessM += GetMscAcousticness(AdquireElementoLista(play, i));
        instrumentalnessM +=
            GetMscInstrumentalness(AdquireElementoLista(play, i));
        livenessM += GetMscLiveness(AdquireElementoLista(play, i));
        valenceM += GetMscValence(AdquireElementoLista(play, i));
        tempoM += GetMscTempo(AdquireElementoLista(play, i));
    }

    danceabilityM =
        danceabilityM / GetQuantidadeLista(GetMusicasPlaylist(play));
    energyM = energyM / GetQuantidadeLista(GetMusicasPlaylist(play));
    loudnessM = loudnessM / GetQuantidadeLista(GetMusicasPlaylist(play));
    speechinessM = speechinessM / GetQuantidadeLista(GetMusicasPlaylist(play));
    acousticnessM =
        acousticnessM / GetQuantidadeLista(GetMusicasPlaylist(play));
    instrumentalnessM =
        instrumentalnessM / GetQuantidadeLista(GetMusicasPlaylist(play));
    livenessM = livenessM / GetQuantidadeLista(GetMusicasPlaylist(play));
    valenceM = valenceM / GetQuantidadeLista(GetMusicasPlaylist(play));
    tempoM = tempoM / GetQuantidadeLista(GetMusicasPlaylist(play));

    Musica *msc = InicializaMusica(
        NULL, "media", 0, 0, 0, NULL, NULL, NULL, danceabilityM, energyM, 0,
        loudnessM, 0, speechinessM, acousticnessM, instrumentalnessM, livenessM,
        valenceM, tempoM, 0);

    return msc;
}