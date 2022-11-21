#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sobre_menu.h"

#include "console.h"

void SobreMenu() {
    system("@cls||clear");
    ImprimeSobre(true);
    scanf("%*c");
}
