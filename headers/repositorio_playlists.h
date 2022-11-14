#ifndef _REPOSITORIO_PLAYLISTS_
#define _REPOSITORIO_PLAYLISTS_

#include "lista.h"
#include "playlist.h"

/**
 * @brief Salva todas as @ref Playlist* em @p playlists
 *
 * @param playlists Uma lista de @ref Playlist* que serao salvas
 *
 * @exception EXIT_FAILURE Caso ocorra qualquer erro ao escrever qualquer campo;
 * mensagem de erro e registrada em stderr
 */
void SalvaTodasPlaylistsRepo(Lista *playlists);

/**
 * @brief Carrega em uma @ref Lista* todas as @ref Playlist* salvas
 *
 * @return Lista* A @ref Lista* de playlists salvas; vazia se nao houver
 * nenhuma, ou caso ocorra qualquer erro de leitura
 */
Lista *CarregaTodasPlaylistsRepo();

#endif
