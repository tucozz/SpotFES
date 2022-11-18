#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "musica.h"

#include "artista.h"

struct tMusica {
    char *id;
    char *name;
    int popularity;
    int duration_ms;
    bool explicit;
    Lista *artists;      // Lista<artista>
    Lista *name_artists; // Lista<string>
    Lista *id_artists;   // Lista<string>
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

Musica *InicializaMusica(const char *id, const char *name, const int popularity,
                         const int duration_ms, const bool explicit,
                         const Lista *name_artists, const Lista *id_artists,
                         const char *release_date, const float danceability,
                         const float energy, const int key,
                         const float loudness, const enum Mode mode,
                         const float speechiness, const float acousticness,
                         const float instrumentalness, const float liveness,
                         const float valence, const float tempo,
                         const int time_signature) {
    Musica *msc = malloc(sizeof *msc);

    msc->id = strdup(id);
    msc->name = strdup(name);
    msc->popularity = popularity;
    msc->duration_ms = duration_ms;
    msc->explicit = explicit;
    msc->artists = NULL;
    msc->name_artists = CopiaLista(name_artists, &strdup);
    msc->id_artists = CopiaLista(id_artists, &strdup);
    msc->release_date = strdup(release_date);
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
    if (msc->artists != NULL)
        LiberaLista(msc->artists, &LiberaArtista);

    LiberaLista(msc->name_artists, &free);
    LiberaLista(msc->id_artists, &free);
    free(msc->release_date);

    free(msc);
}

float SemelhancaMusicas(Musica *msc1, Musica *msc2) {
    float SomaMedia = pow((msc1->danceability - msc2->danceability), 2);
    SomaMedia += pow((msc1->energy - msc2->energy), 2);
    SomaMedia += pow((msc1->loudness - msc2->loudness), 2);
    SomaMedia += pow((msc1->speechiness - msc2->speechiness), 2);
    SomaMedia += pow((msc1->acousticness - msc2->acousticness), 2);
    SomaMedia += pow((msc1->instrumentalness - msc2->instrumentalness), 2);
    SomaMedia += pow((msc1->liveness - msc2->liveness), 2);
    SomaMedia += pow((msc1->valence - msc2->valence), 2);
    SomaMedia += pow((msc1->tempo - msc2->tempo), 2);

    return sqrt(SomaMedia);
}

char *GetMscId(Musica *msc) { return msc->id; }

char *GetMscName(Musica *msc) { return msc->name; }

int GetMscPopularity(const Musica *msc) { return msc->popularity; }

int GetMscDuration(const Musica *msc) { return msc->duration_ms; }

bool IsExplicit(const Musica *msc) { return msc->explicit; }

Lista *GetMscArtists(Musica *msc) { return msc->artists; }

Lista *GetMscArtistsName(Musica *msc) { return msc->name_artists; }

Lista *GetMscArtistsId(Musica *msc) { return msc->id_artists; }

char *GetMscReleaseDate(Musica *msc) { return msc->release_date; }

float GetMscDanceability(const Musica *msc) { return msc->danceability; }

float GetMscEnergy(const Musica *msc) { return msc->energy; }

int GetMscKey(const Musica *msc) { return msc->key; }

float GetMscLoudness(const Musica *msc) { return msc->loudness; }

bool GetMscMode(const Musica *msc) { return msc->mode; }

float GetMscSpeechiness(const Musica *msc) { return msc->speechiness; }

float GetMscAcousticness(const Musica *msc) { return msc->acousticness; }

float GetMscInstrumentalness(const Musica *msc) {
    return msc->instrumentalness;
}

float GetMscLiveness(const Musica *msc) { return msc->liveness; }

float GetMscValence(const Musica *msc) { return msc->valence; }

float GetMscTempo(const Musica *msc) { return msc->tempo; }

int GetMscTimeSig(const Musica *msc) { return msc->time_signature; }

bool IncluiMscArtistas(Musica *msc, const Lista *listart) {
    if (msc->artists != NULL || listart == NULL)
        return true;

    msc->artists = CopiaLista(listart, &CopiaArtista);

    return false;
}

Musica *CopiaMusica(const Musica *msc) {
    Musica *cpy = InicializaMusica(
        msc->id, msc->name, msc->popularity, msc->duration_ms, msc->explicit,
        msc->name_artists, msc->id_artists, msc->release_date,
        msc->danceability, msc->energy, msc->key, msc->loudness, msc->mode,
        msc->speechiness, msc->acousticness, msc->instrumentalness,
        msc->liveness, msc->valence, msc->tempo, msc->time_signature);

    IncluiMscArtistas(cpy, msc->artists);

    return cpy;
}
