#ifndef _DETALHA_MUSICA_
#define _DETALHA_MUSICA_

#include "app.h"
#include "musica.h"
#include "playlist.h"

/**
 * @brief Detalha na tela uma @ref Musica* @p msc
 *
 * @param app O @ref App*
 * @param msc A @ref Musica*
 * @param playlistOrig A playlist que roteou ate essa lista, adiciona a musica
 * selecionada a ela; se nulo, segue para a tela de playlists
 */
void DetalhaMusicaMenu(App *app, Musica *msc, Playlist *playlistOrig);

#endif
