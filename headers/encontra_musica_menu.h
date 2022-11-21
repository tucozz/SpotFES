#ifndef _ENCONTRA_MUSICA_
#define _ENCONTRA_MUSICA_

#include "app.h"
#include "playlist.h"

/**
 * @brief Procura por uma musica e lista elas
 *
 * @param app O @ref App*
 * @param playlistOrig Pode ser NULL; é a playlist que invocou esse menu a
 * procura de uma musica para adicionar nela
 */
void EncontraMusicaMenu(App *, Playlist *playlistOrig);

#endif
