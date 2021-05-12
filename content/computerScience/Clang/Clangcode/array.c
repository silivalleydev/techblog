#include "stdio.h"

int main() {
    int a[4];
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;
    a[3] = 40;

    printf("0=>%d, 1=>%d, 2=>%d, 3=>%d\n", a[0], a[1], a[2], a[3]);


    int b[2] = {1, 2};

    printf("0=>%d, 1=>%d", b[0], b[1]);


}