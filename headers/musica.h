#ifndef _MUSICA_
#define _MUSICA_

#include <stdbool.h>

#include "lista.h"

enum Mode { Minor = 0, Major = 1 };

typedef struct tMusica Musica;

/**
 * @brief Inicializa dinamicamente uma @ref Musica
 *
 * @warning Conteudo dos ponteiros NAO sao copiados na construcao, mas sao
 * liberados na destruicao
 *
 * @param id Hash identificador unico
 * @param name Nome
 * @param popularity Popularidade [0, 100]
 * @param duration_ms Duracao em milisegundos
 * @param explicit Se contem conteudo explicito ou nao
 * @param artists Lista de tipo string contendo o nome dos artistas
 * @param id_artists Lista de tipo string que guarda os hashes identificadores
 * unicos dos artistas
 * @param release_date Data de lancamento
 * @param danceability Danceabilidade [0.0, 1.0]
 * @param energy Energia [0.0, 1.0]
 * @param key Nota maior // TODO: Enum para as notas (nao sei o que significa)
 * @param loudness Sonoridade em db
 * @param mode Modo (?)
 * @param speechiness Musicalidade [0.0, 1.0]
 * @param acousticness Acustica [0.0, 1.0]
 * @param instrumentalness Instrumentalidade [0.0, 1.0]
 * @param liveness Vivacidade [0.0, 1.0]
 * @param valence Valencia [0.0, 1.0]
 * @param tempo Ritmo em bpm
 * @param time_signature Campo interno
 * @return Musica* Ponteiro para uma nova instancia de @ref Musica
 */
Musica *InicializaMusica(char *id, char *name, int popularity, int duration_ms,
                         bool explicit, Lista *artists, Lista *id_artists,
                         char *release_date, float danceability, float energy,
                         int key, float loudness, enum Mode mode,
                         float speechiness, float acousticness,
                         float instrumentalness, float liveness, float valence,
                         float tempo, int time_signature);

/**
 * @brief Libera a @ref Musica dinamicamente alocada
 *
 * @warning Libera os ponteiros que foram passados na inicializacao
 *
 * @param msc Uma instancia de @ref Musica
 */
void LiberaMusica(Musica *msc);

char *GetMscId(tMusica msc);

char *GetMscName(tMusica msc);

int GetMscPopularity(tMusica msc);

int GetMscDuration(tMusica msc);

bool IsExplicit(tMusica msc);

Lista *GetMscArtists(tMusica msc);

Lista *GetMscArtistsId(tMusica msc);

char *GetMscReleaseDate(tMusica msc);

float GetMscDanceability(tMusica msc);

float GetMscEnergy(tMusica msc);

int GetMscKey(tMusica msc);

float GetMscLoudness(tMusica msc);

bool GetMscMode(tMusica msc);

float GetMscSpeechiness(tMusica msc);

float GetMscAcousticness(tMusica msc);

float GetMscInstrumentalness(tMusica msc);

float GetMscLiveness(tMusica msc);

float GetMscValence(tMusica msc);

float GetMscTempo(tMusica msc);

int GetMscTimeSig(tMusica msc);

#endif
