#ifndef _ARTISTA_
#define _ARTISTA_

#include "lista.h"

typedef struct tArtista Artista;

/**
 * @brief Inicializa dinamicamente um @ref Artista
 *
 * @warning Conteudo dos ponteiros NAO sao copiados na construcao, mas sao
 * liberados na destruicao.
 *
 * @param id Hash identificador unico
 * @param seguidores Quantidade de seguidores
 * @param generos Lista de tipo string contendo os generos
 * @param name Nome
 * @param popularity Popularidade [0, 100]
 * @return Artista* Ponteiro para uma nova instancia de @ref Artista
 */
Artista *InicializaArtista(char *id, int seguidores, Lista *generos, char *name,
                           int popularity);

/**
 * @brief Libera a @ref Artista dinamicamente alocada
 *
 * @warning Libera os ponteiros que foram passados na inicializacao
 *
 * @param msc Uma instancia de @ref Artista
 */
void LiberaArtista(Artista *artista);

char *GetArtId(tArtista art);
int GetArtSeguidores(tArtista art);
Lista *GetArtGeneros(tArtista art);
char *GetArtName(tArtista art);
int GetArtPopularity(tArtista art);


#endif
