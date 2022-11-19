#include <stdio.h>
#include <stdlib.h>

#include "exception.h"

void throwException(char *name, char *msg, int code) {
    fprintf(stderr, "%s\n\n%s\n", name, msg);
    exit(code);
}

void throwOutOfMemoryException(char *msg) {
    throwException("OutOfMemoryException", msg, EXCEPTION_OUT_OF_MEMORY);
}
