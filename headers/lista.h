/**
 * @file lista.h
 * @brief Uma estrutura de dados de uma lista de tipo genérico
 * 
 *   Lista *lista_int = InicializaLista();
 *
 *   int *one1 = malloc(sizeof(int));
 *   int *one2 = malloc(sizeof(int));
 *   int *one3 = malloc(sizeof(int));
 *   int *one4 = malloc(sizeof(int));
 *   int *one5 = malloc(sizeof(int));
 *   int *one6 = malloc(sizeof(int));
 *
 *   *one1 = 0;
 *   *one2 = 1;
 *   *one3 = 2;
 *   *one4 = 3;
 *   *one5 = 4;
 *   *one6 = 5;
 *
 *   AdicionaElementoLista(lista_int, one1);
 *   AdicionaElementoLista(lista_int, one2);
 *   AdicionaElementoLista(lista_int, one3);
 *   AdicionaElementoLista(lista_int, one4);
 *   AdicionaElementoLista(lista_int, one5);
 *   AdicionaElementoLista(lista_int, one6);
 *
 *   int *a = PopLista(lista_int);
 *
 *   printf("Integer (5): %d\n", *a);
 *
 *   free(a);
 *
 *   LiberaLista(lista_int, &free);
 * 
 * @version 0.1
 * @date 2022-11-08
 *  
 */

#ifndef _LISTA_
#define _LISTA_

typedef struct tLista Lista;

/**
 * @brief Inicializa dinamicamente uma @ref Lista
 * 
 * @return Lista* Uma nova instancia de @ref Lista
 */
Lista *InicializaLista();

/**
 * @brief Libera a @p lista e todos os seus elementos da memória em que foram dinamicamente alocados
 * 
 * @param lista Uma instancia de @ref Lista
 * @param liberaElem Uma funcao destrutora dos elementos da lista
 */
void LiberaLista(Lista *lista, void (*liberaElem)(void *));

/**
 * @brief Adiciona um elemento @p elem ao final da lista @p lista
 * 
 * @param lista Uma instancia de @ref Lista de mesmo tipo que @p elem
 * @param elem O elemento que sera adicionado
 */
void AdicionaElementoLista(Lista *lista, void *elem);

/**
 * @brief Retorna o ultimo elemento adicionado na lista e o remove. (DE FREE NO ELEMENTO RETORNADO)
 * 
 * @param lista Uma instancia de @ref Lista
 * @return void* O elemento no topo da @p lista
 */
void *PopLista(Lista *lista);

#endif