#include <stdlib.h>

#include "musica.h"
#include "artista.h"

struct tMusica {
    char *id;
    char *name;
    int popularity;
    int duration_ms;
    bool explicit;
    Lista *artists;    // Lista<string>
    Lista *id_artists; // Lista<string>
    char *release_date;
    float danceability;
    float energy;
    int key;
    float loudness;
    bool mode;
    float speechiness;
    float acousticness;
    float instrumentalness;
    float liveness;
    float valence;
    float tempo;
    int time_signature;
};

Musica *InicializaMusica(char *id, char *name, int popularity, int duration_ms,
                         bool explicit, Lista *artists, Lista *id_artists,
                         char *release_date, float danceability, float energy,
                         int key, float loudness, enum Mode mode,
                         float speechiness, float acousticness,
                         float instrumentalness, float liveness, float valence,
                         float tempo, int time_signature) {
    Musica *msc = malloc(sizeof *msc);

    msc->id = id;
    msc->name = name;
    msc->popularity = popularity;
    msc->duration_ms = duration_ms;
    msc->explicit = explicit;
    msc->artists = artists;
    msc->id_artists = id_artists;
    msc->release_date = release_date;
    msc->danceability = danceability;
    msc->energy = energy;
    msc->key = key;
    msc->loudness = loudness;
    msc->mode = mode;
    msc->speechiness = speechiness;
    msc->acousticness = acousticness;
    msc->instrumentalness = instrumentalness;
    msc->liveness = liveness;
    msc->valence = valence;
    msc->tempo = tempo;
    msc->time_signature = time_signature;

    return msc;
}

void LiberaMusica(Musica *msc) {
    free(msc->id);
    free(msc->name);
    LiberaLista(msc->artists, &free);
    LiberaLista(msc->id_artists, &free);
    free(msc->release_date);
    
    free(msc);
}

char *GetMscId(tMusica msc)
    return msc.id;

char *GetMscName(tMusica msc)
    return msc.name;

int GetMscPopularity(tMusica msc)
    return msc.popularity;

int GetMscDuration(tMusica msc)
    return msc.duration_ms;

bool IsExplicit(tMusica msc)
    return msc.explicit;

Lista *GetMscArtists(tMusica msc)
    return msc.artists;

Lista *GetMscArtistsId(tMusica msc)
    return msc.id_artists;

char *GetMscReleaseDate(tMusica msc)
    return msc.release_date;

float GetMscDanceability(tMusica msc)
    return msc.danceability;

float GetMscEnergy(tMusica msc)
    return msc.energy;

int GetMscKey(tMusica msc)
    return msc.key;

float GetMscLoudness(tMusica msc)
    return msc.loudness;

bool GetMscMode(tMusica msc)
    return msc.mode;

float GetMscSpeechiness(tMusica msc)
    return msc.speechiness;

float GetMscAcousticness(tMusica msc)
    return msc.acousticness;

float GetMscInstrumentalness(tMusica msc)
    return msc.intrumentalness;

float GetMscLiveness(tMusica msc)
    return msc.liveness;

float GetMscValence(tMusica msc)
    return msc.valence;

float GetMscTempo(tMusica msc)
    return msc.tempo;

int GetMscTimeSig(tMusica msc)
    return msc.time_signature;

