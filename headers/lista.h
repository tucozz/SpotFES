#ifndef _LISTA_
#define _LISTA_

typedef struct tLista Lista;

Lista *InicializaLista();

void *LiberaLista(Lista *lista);

void AdicionaElementoLista(Lista *lista, void *elem);

/**
 * @brief Retorna o ultimo elemento adicionado na lista e o remove. (DE FREE NO ELEMENTO RETORNADO)
 * 
 * @param lista Uma instancia de @ref Lista
 * @return void* O elemento no topo da @p lista
 */
void *PopLista(Lista *lista);

#endif
