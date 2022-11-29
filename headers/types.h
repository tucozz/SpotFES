#ifndef _TYPES_
#define _TYPES_

typedef void (*free_fn)(void *);

typedef int (*compar_fn)(const void *, const void *);

typedef void *(*cpyval_fn)(const void *);

#endif
