#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"
#include "exception.h"

int main(int argc, char *argv[]) {
    if (argc != 3)
        throwException("ArgumentException",
                       "Couldn't find command line argument for tracks csv "
                       "file or artists csv file",
                       EXIT_FAILURE);

    App *app = InicializaApp(argv[1], argv[2]);

    RodaApp(app);

    LiberaApp(app);

    return EXIT_SUCCESS;
}
