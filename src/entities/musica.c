#include <stdbool.h>

#include "musica.h"
#include "lista.h"

struct tMusica {
    char *id;
    char *name;
    int popularity;
    int duration_ms;
    bool explicit;
    Lista *artists;    // Lista<Artista>
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


