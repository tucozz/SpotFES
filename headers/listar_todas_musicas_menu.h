#ifndef _LISTAR_TODAS_MUSICAS_
#define _LISTAR_TODAS_MUSICAS_

#include "app.h"
#include "lista.h"
#include "playlist.h"

/**
 * @brief Lista na tela a @ref Lista* @p musicas com paginacao e interação com
 * as músicas
 *
 * @param app O @ref App*
 * @param musicas A @ref Lista* de @ref Musica*
 * @param playlistOrig A playlist que roteou ate essa lista, adiciona a musica
 * selecionada a ela; se nulo, segue para a tela de playlists
 */
void ListarTodasMusicasMenu(App *app, Lista *musicas, Playlist *playlistOrig);

#endif
