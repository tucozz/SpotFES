#ifndef _EXCEPTION_
#define _EXCEPTION_

#define EXCEPTION_OUT_OF_MEMORY 137

void throwException(char *name, char *msg, int code);

void throwOutOfMemoryException(char *msg);

#endif
