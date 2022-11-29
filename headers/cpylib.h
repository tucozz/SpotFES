#ifndef _CPYLIB_
#define _CPYLIB_

#include <stdlib.h>

#include "types.h"

// clonei a qsort 😎

/**
 * @brief Sort NMEMB elements of BASE, of SIZE bytes each,
 * using COMPAR to perform the comparisons.
 * 
 */
void qsortcpy(void *__base, size_t __nmemb, size_t __size, compar_fn __compar);

#endif
