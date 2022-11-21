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

    if (EncontraLista(playlist->musicas_id, GetMscId(msc), &strcmp) != -1)
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

    Lista *mscs = GetMusicasPlaylist(play);
    int n = GetQuantidadeLista(mscs);
    for (i = 0; i < n; i++) {
        Musica *curr = AdquireElementoLista(mscs, i);

        danceabilityM += GetMscDanceability(curr);
        energyM += GetMscEnergy(curr);
        loudnessM += GetMscLoudness(curr);
        speechinessM += GetMscSpeechiness(curr);
        acousticnessM += GetMscAcousticness(curr);
        instrumentalnessM += GetMscInstrumentalness(curr);
        livenessM += GetMscLiveness(curr);
        valenceM += GetMscValence(curr);
        tempoM += GetMscTempo(curr);
    }

    danceabilityM /= n;
    energyM /= n;
    loudnessM /= n;
    speechinessM /= n;
    acousticnessM /= n;
    instrumentalnessM /= n;
    livenessM /= n;
    valenceM /= n;
    tempoM /= n;

    Lista *mockIds = InicializaLista();   // Lista<string>
    Lista *mockNames = InicializaLista(); // Lista<string>
    Musica *msc = InicializaMusica(
        "media", "media", 0, 0, false, mockNames, mockIds, "4242-12-21", danceabilityM, energyM, 0,
        loudnessM, 0, speechinessM, acousticnessM, instrumentalnessM, livenessM,
        valenceM, tempoM, 0);

    LiberaLista(mockIds, &free);
    LiberaLista(mockNames, &free);

    return msc;
}