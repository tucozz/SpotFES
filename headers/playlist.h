#ifndef _PLAYLIST_
#define _PLAYLIST_

#include "lista.h"
#include "musica.h"

typedef struct tPlaylist Playlist;

Playlist *InicializaPlaylist(const char *nome, const Lista *musicas_id);

void LiberaPLaylist(Playlist *playlist);

char *GetNomePlaylist(Playlist *playlist);

Lista *GetMusicasPlaylist(Playlist *playlist);

Lista *GetMusicasIdPlaylist(Playlist *playlist);

/**
 * @brief Inclui uma @ref Lista* de @ref Musica* a @ref Playlist* @p playlist
 *
 * @warning A @ref Lista* de @ref Musica* SERA COPIADA; lembre-se de liberar o
 * ponteiro @p musicas
 *
 * @param playlist A @ref Playlist*
 * @param musicas A @ref Lista* de @ref Musica*
 * @return bool Verdadeiro, se a inclusao deu certo, ou seja, playlist->musicas
 * e NULL e @p musicas nao e NULL; do contrario, Falso
 */
bool IncluiMusicasPlaylist(Playlist *playlist, const Lista *musicas);

/**
 * @brief Adiciona uma @ref Musica* @p msc a @ref Playlist* @p playlist
 *
 * @warning Ao adicionar a @ref Musica* @p msc ela SERA COPIADA; certifique-se
 * de liberar o ponteiro da musica original nos parametros
 *
 * @param playlist A @ref Playlist*
 * @param msc A @ref Musica* que sera adicionada na playlist
 * @return bool Verdadeiro se adicionada, ou seja, msc nao e NULL; do contrario,
 * Falso
 */
bool AdicionaMusicaPlaylist(Playlist *playlist, const Musica *msc);

/**
 * @brief Efetua uma copia da @ref Playlist* @p playlist
 *
 * @param msc A @ref Playlist*
 * @return Musica* Uma nova instancia de @ref Musica* identica a original
 */
Playlist *CopiaPlaylist(const Playlist *playlist);

#endif
