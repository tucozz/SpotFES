#ifndef _REPOSITORIO_BASE_
#define _REPOSITORIO_BASE_

#include "lista.h"

/**
 * @brief Carrega uma @ref Lista* de string padrao do repositorio a partir de
 * uma string
 *
 * @param str String padrao representando uma lista de strings separadas por '|'
 * @return Lista* Ponteiro para uma nova instancia de @ref Lista de string
 */
Lista *CarregaListaStringRepo(char *str);

#endif
