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
 * @brief Carrega uma @ref Musica do arquivo @p csv
 *
 * @param csv Ponteiro para o inicio da secao do arquivo com um padrao
 * representando uma @ref Musica
 * @return Musica* Se valido, retorna um ponteiro para uma nova instancia da
 * @ref Musica ali representada; do contrario, retorna NULL
 */
Musica *CarregaMusicaCsvRepo(FILE *csv);

#endif