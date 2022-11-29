#include <stdlib.h>
#include <string.h>

#include "cpylib.h"

#include "exception.h"

// CODIGO ~roubado~ADAPTADO DAS INTERWEBS!!!!
//     https://github.com/srjheam/ufes-snake/blob/master/JheamStorchRoss.c#L1361-L1416
static void mesclaArr(void *base, int d, int m, int e, size_t __size,
                      compar_fn __compar) {
    // Base a ser mesclada no formato de uma sequencia de bytes
    // Uso do char * sobre void * para caminhar pela memória do array é o melhor
    // dado que
    //     https://stackoverflow.com/a/62728128
    char *bbBase = base;

    int t1 = m - d + 1;
    int t2 = e - m;
    // cria vetores temporarios
    char *vetE = malloc(t1 * __size);
    if (vetE == NULL)
        throwOutOfMemoryException("Internal sorting algorithm malloc failed");
    char *vetD = malloc(t2 * __size);
    if (vetD == NULL)
        throwOutOfMemoryException("Internal sorting algorithm malloc failed");

    // copia as fatias para os vetores temporarios
    int i;
    for (i = 0; i < t1; i++)
        memcpy(vetE + i * __size, bbBase + (d + i) * __size, __size);

    int j;
    for (j = 0; j < t2; j++)
        memcpy(vetD + j * __size, bbBase + (m + 1 + j) * __size, __size);

    // mescla os vetores temporarios em ordem crescente
    i = 0;
    j = 0;
    int k;
    for (k = d; i < t1 && j < t2; k++) {
        if (__compar(vetE + i * __size, vetD + j * __size) <= 0) {
            memcpy(bbBase + k * __size, vetE + i * __size, __size);
            i++;
        } else {
            memcpy(bbBase + k * __size, vetD + j * __size, __size);
            j++;
        }
    }

    // insere os elementos remanescentes de vetE[] em ranking
    while (i < t1) {
        memcpy(bbBase + k * __size, vetE + i * __size, __size);
        i++;
        k++;
    }
    // insere os elementos remanescentes de vetE[] em ranking
    while (j < t2) {
        memcpy(bbBase + k * __size, vetD + j * __size, __size);
        j++;
        k++;
    }

    free(vetE);
    free(vetD);
}

static void ordenaMesclando(void *base, int d, int e, size_t __size,
                            compar_fn __compar) {
    if (d >= e)
        return;

    int m = d + (e - d) / 2;
    ordenaMesclando(base, d, m, __size, __compar);
    ordenaMesclando(base, m + 1, e, __size, __compar);
    mesclaArr(base, d, m, e, __size, __compar);
}
// FIM DO CODIGO ~roubado~ADAPTADO DAS INTERWEBS!!!!

void qsortcpy(void *__base, size_t __nmemb, size_t __size, compar_fn __compar) {
    ordenaMesclando(__base, 0, __nmemb - 1, __size, __compar);
}
