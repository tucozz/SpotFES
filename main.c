#include <stdio.h>
#include <stdlib.h>

#include "app.h"

int main(int argc, char *argv[]) {
    if (argc != 3)
        return EXIT_FAILURE;

    App *app = InicializaApp(argv[1], argv[2]);

    RodaApp(app);

    LiberaApp(app);

    return EXIT_SUCCESS;
}
