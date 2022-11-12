#ifndef _REPOSITORIO_BASE_
#define _REPOSITORIO_BASE_

#define REPO_CSV_DELIM ";"

#include "lista.h"

/**
 * @brief Carrega uma @ref Lista* de string padrao do repositorio a partir de
 * uma string
 *
 * @param str String padrao representando uma lista de strings separadas por '|'
 * @return Lista* Ponteiro para uma nova instancia de @ref Lista de string
 */
Lista *CarregaListaStringRepo(char *str);

/**
 * @brief Normaliza uma string @p str tornando todos os seus caracteres
 * minusculos para fins de consulta
 *
 * @param str A string a ser normalizada
 */
void NormalizaString(char *str);

#endif
