#include <stdio.h>
#include <stdlib.h>

#include "erro_menu.h"

#include "console.h"

void ErroMenu(char *msg) {
    system("@cls||clear");
    printf(ANSI_COLOR_YELLOW);
    printf("%s", msg);
    printf(ANSI_COLOR_RESET "\npressione ENTER para continuar");
    scanf("%*c");
}
