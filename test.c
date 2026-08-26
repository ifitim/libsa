#include <stdio.h>
#include "sa.h"

int main() {
    printf("Спиннер на 3 секунды:\n");
    sa_animation spinner = {SA_SPINNER, NULL, 0, 1};
    saani(spinner, 3);

    printf("\nТочки на 2 секунды:\n");
    sa_animation dots = {SA_DOTS, NULL, 0, 1};
    saani(dots, 2);

    printf("\nПрогресс-бар на 2 секунды:\n");
    sa_animation bar = {SA_BAR, NULL, 0, 1};
    saani(bar, 2);

    printf("\nПульс на 2 секунды:\n");
    sa_animation pulse = {SA_PULSE, NULL, 0, 1};
    saani(pulse, 2);

    printf("\nГотово!\n");
    return 0;
}
