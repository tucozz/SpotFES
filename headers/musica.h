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
Musica *InicializaMusica(const char *id, const char *name, const int popularity,
                         const int duration_ms, const bool explicit,
                         const Lista *name_artists, const Lista *id_artists,
                         const char *release_date, const float danceability,
                         const float energy, const int key,
                         const float loudness, const enum Mode mode,
                         const float speechiness, const float acousticness,
                         const float instrumentalness, const float liveness,
                         const float valence, const float tempo,
                         const int time_signature);

/**
 * @brief Libera a @ref Musica dinamicamente alocada
 *
 * @warning Libera os ponteiros que foram passados na inicializacao
 *
 * @param msc Uma instancia de @ref Musica
 */
void LiberaMusica(Musica *msc);

char *GetMscId(Musica *msc);

char *GetMscName(Musica *msc);

int GetMscPopularity(const Musica *msc);

int GetMscDuration(const Musica *msc);

bool IsExplicit(const Musica *msc);

Lista *GetMscArtists(Musica *msc);

Lista *GetMscArtistsName(Musica *msc);

Lista *GetMscArtistsId(Musica *msc);

char *GetMscReleaseDate(Musica *msc);

float GetMscDanceability(const Musica *msc);

float GetMscEnergy(const Musica *msc);

int GetMscKey(const Musica *msc);

float GetMscLoudness(const Musica *msc);

bool GetMscMode(const Musica *msc);

float GetMscSpeechiness(const Musica *msc);

float GetMscAcousticness(const Musica *msc);

float GetMscInstrumentalness(const Musica *msc);

float GetMscLiveness(const Musica *msc);

float GetMscValence(const Musica *msc);

float GetMscTempo(const Musica *msc);

int GetMscTimeSig(const Musica *msc);

/**
 * @brief Inclui uma @ref Lista* de @ref Artista* em @ref Musica* @p msc , caso
 * nao haja nenhuma
 *
 * @warning A @ref Lista* @p listart SERA COPIADA; atencao ao liberar o ponteiro
 * enviado pelos parametros
 *
 * @param msc A @ref Musica*
 * @param listart A @ref Lista* de @ref Artista*
 * @return int
 */
bool IncluiMscArtistas(Musica *msc, const Lista *listart);

/**
 * @brief Efetua uma copia da @ref Musica* @p msc
 *
 * @param msc A @ref Musica*
 * @return Musica* Uma nova instancia de @ref Musica* identica a original
 */
Musica *CopiaMusica(const Musica *msc);

#endif
