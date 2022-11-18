#ifndef _PROCURADOR_
#define _PROCURADOR_

#include "playlist.h"
#include "repositorio_artistas.h"
#include "repositorio_musicas.h"

/**
 * @brief Completa uma @ref Musica* com sua @ref Lista* de @ref Artista*
 *
 * Caso a musica ja contenha uma @ref Lista* seu estado nao sera modificado;
 * Essa funcao pode retornar uma lista de ponteiros NULL de tamanho igual a
 * lista de hashes caso nao encontre nenhum artista
 *
 * @param msc A @ref Musica* a ser completada
 * @param repo O @ref RepoArtistas* com os dados dos artistas
 */
void CompletaMusica(Musica *msc, RepoArtistas *repo);

/**
 * @brief Completa uma @ref Playlist* com sua @ref Lista* de @ref Musica*
 *
 * Caso a playlist ja contenha uma @ref Lista* seu estado nao sera modificado;
 * Essa funcao pode retornar uma lista de ponteiros NULL de tamanho igual a
 * lista de hashes caso nao encontre nenhuma musica
 *
 * @param msc A @ref Playlist* a ser completada
 * @param repo O @ref RepoMusicas* com os dados das musicas
 */
void CompletaPlaylist(Playlist *playlist, RepoMusicas *repo);

/**
 * @brief Gera uma @ref Lista* de @p k @ref Musica* semelhantes a aquelas que
 * fazem parte da @p playlist
 *
 * @param playlist A @ref Playlist* para a qual recomendar musicas
 * @param k Quantidade de musicas para recomendar
 * @param repo O @ref RepoMusicas* onde está a fonte de musicas
 * @return Lista* Uma @ref Lista* de @ref Musica* com tamanho maximo igual a
 * @p k
 */
Lista *RecomendaMusicas(Playlist *playlist, int k, RepoMusicas *repo);

#endif
