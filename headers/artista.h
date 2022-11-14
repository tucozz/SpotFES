#ifndef _ARTISTA_
#define _ARTISTA_

#include "lista.h"

typedef struct tArtista Artista;

/**
 * @brief Inicializa dinamicamente um @ref Artista
 *
 * @warning Conteudo dos ponteiros SAO copiados na construcao e liberados na
 * destruicao; lembre-se de liberar o conteudo passado pelos parametros se for o
 * caso
 *
 * @param id Hash identificador unico
 * @param seguidores Quantidade de seguidores
 * @param generos Lista de tipo string contendo os generos
 * @param name Nome
 * @param popularity Popularidade [0, 100]
 * @return Artista* Ponteiro para uma nova instancia de @ref Artista
 */
Artista *InicializaArtista(const char *id, const int seguidores,
                           const Lista *generos, const char *name,
                           const int popularity);

/**
 * @brief Libera a @ref Artista dinamicamente alocada
 *
 * @warning Libera os ponteiros que foram passados na inicializacao
 *
 * @param msc Uma instancia de @ref Artista
 */
void LiberaArtista(Artista *artista);

char *GetArtId(Artista *art);

int GetArtSeguidores(const Artista *art);

Lista *GetArtGeneros(Artista *art);

char *GetArtName(Artista *art);

int GetArtPopularity(const Artista *art);

/**
 * @brief Executa uma copia do @ref Artista* @p art
 *
 * @param art O @ref Artista* copiado
 * @return Artista* Uma nova instancia de @ref Artista* identica a original
 */
Artista *CopiaArtista(const Artista *art);

#endif
