#ifndef _CONSOLE_
#define _CONSOLE_

#include "musica.h"
#include "playlist.h"

/**
 * @brief Desenha na tela uma linha da @p musica de uma tabela de @ref Musica*
 *
 * @param msc A @ref Musica*
 * @param i O indice baseado em 1 da linha
 */
void ListarMusica(Musica *msc, int i);

/**
 * @brief Desenha toda a tabela de @ref Musica*
 *
 * @param mscs A @ref Lista* de @ref Musica*
 * @param n Limite inferior do indice interno baseado em zero das musicas em
 * @p mscs
 * @param m Limite superior do indice interno baseado em zero das musicas em
 * @p mscs
 */
void ListarTodasMusicas(Lista *mscs, int n, int m);

/**
 * @brief Desenha na tela todas as informações dessa @ref Musica* @p msc ;
 * incluindo seus artista
 *
 * @param msc A @ref Musica*
 */
void DetalharMusica(Musica *msc);

/**
 * @brief Desenha na tela uma linha da @p playlist de uma tabela de
 * @ref Playlist*
 *
 * @param playlist A @ref playlist*
 * @param i O indice baseado em 1 da linha
 */
void ListarPlaylist(Playlist *playlist, int i);

/**
 * @brief Desenha toda a tabela de @ref Playlist*
 *
 * @param mscs A @ref Lista* de @ref Playlist*
 * @param n Limite inferior do indice interno baseado em zero das musicas em
 * @p mscs
 * @param m Limite superior do indice interno baseado em zero das musicas em
 * @p mscs
 */
void ListarTodasPlaylists(Lista *playlists, int n, int m);

/**
 * @brief Desenha na tela todas as informações dessa @ref Playlist* @p playlist
 * ; incluindo suas musicas
 *
 * @param msc A @ref Musica*
 */
void DetalharPlaylist(Playlist *playlist);

void ImprimeMarca(bool animacao);

void ImprimeSobre(bool animacao);

void ImprimeDelay(char str[], bool en, int delay);

#endif