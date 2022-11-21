#ifndef _LISTAR_TODAS_PLAYLISTS_
#define _LISTAR_TODAS_PLAYLISTS_

#include "app.h"
#include "musica.h"

/**
 * @brief Lista todas as playlists do usuário
 *
 * @param app O @ref App*
 * @param mscOrig Pode ser NULL; é a musica que invocou esse menu querendo se
 * adicionar numa playlist
 */
void ListarTodasPlaylistsMenu(App *app, Musica *mscOrig);

#endif
