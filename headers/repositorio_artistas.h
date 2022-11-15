#ifndef _REPOSITORIO_ARTISTAS_
#define _REPOSITORIO_ARTISTAS_

#include "artista.h"

typedef struct tRepoArtistas RepoArtistas;

RepoArtistas *InicializaRepoArtistas(const char *artistas_csv);

void LiberaRepoArtistas(RepoArtistas *repo);

/**
 * @brief Busca na fonte o @ref Artista* com o hash igual a @p hash
 * 
 * @param repo O @ref RepoArtistas*
 * @param hash O hash pelo qual procurar
 * @return Artista* O @ref Artista* encontrado; NULL caso nao ache
 */
Artista *EncontraPeloHashRepoArtistas(RepoArtistas *repo, const char *hash);

#endif
