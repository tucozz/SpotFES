/**
 * @file repositorio_musicas.h
 * @brief Repositorio reponsavel por lidar com fontes de musicas
 * @version 0.1
 * @date 2022-11-10
 *
 * @example
 *    RepoMusicas *repo = InicializaRepoMusicas(argv[1]);
 *
 *    FILE *f = fopen(argv[1], "r");
 *
 *    Musica *msc1 = CarregaMusicaCsvRepo(f);
 *    Musica *msc2 = CarregaMusicaCsvRepo(f);
 *    Musica *msc3 = CarregaMusicaCsvRepo(f);
 *
 *    LiberaMusica(msc1);
 *    LiberaMusica(msc2);
 *    LiberaMusica(msc3);
 *
 *    fclose(f);
 *
 *    LiberaRepoMusicas(repo);
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _REPOSITORIO_MUSICAS_
#define _REPOSITORIO_MUSICAS_

#include <stdio.h>
#include <stdbool.h>

#include "musica.h"

typedef struct tRepoMusicas RepoMusicas;

/**
 * @brief Inicializa uma nova instancia de @ref RepoMusicas* com a fonte em
 * @p musicas_csv
 *
 * @param musicas_csv Fonte csv padrao contento uma serie de musicas
 * @return RepoMusicas* Ponteiro para uma nova instancia de @ref RepoMusicas*
 */
RepoMusicas *InicializaRepoMusicas(const char *musicas_csv);

/**
 * @brief Libera o @ref RepoMusicas dinamicamente alocado
 *
 * @param msc Uma instancia de @ref Musica
 */
void LiberaRepoMusicas(RepoMusicas *repo);

/**
 * @brief Busca na fonte todas as musicas que contem @p query como uma substring
 * do seu nome
 *
 * @warning Normaliza a @p query
 *
 * @param repo O @ref RepoMusicas
 * @param query A substring de consulta a ser procurada no nome das musicas
 * @return Lista* Uma @ref Lista* de @ref Musica* encontradas
 */
Lista *EncontraPeloNomeRepoMusica(RepoMusicas *repo, char *query);

/**
 * @brief Busca na fonte a @ref Musica* com o hash igual a @p hash
 *
 * @param repo O @ref RepoMusicas*
 * @param hash O hash pelo qual procurar
 * @return Musica* A @ref Musica* encontrada; NULL caso nao ache
 */
Musica *EncontraPeloHashRepoMusica(RepoMusicas *repo, const char *hash);

FILE *InicioIteradorRepoMsc(RepoMusicas *repo);

Musica *ProximoIteradorRepoMsc(FILE *itr);

bool FimIteradorRepoMsc(FILE *itr);

#endif
