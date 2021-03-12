#include "stdio.h"

int main() {
    int x, y;

    x = 20;
    y = 10;

    printf("x+y=%d\n", x+y);
    printf("x*y=%d\n", x*y);
    printf("x/y=%d\n", x/y);
    printf("x%%y=%d\n", x%y);
    
    printf("x++=%d\n", ++x);
    printf("y--=%d\n", --y);

    // 참이면 1 거짓이면 0
    printf("x==y: %d\n", x == y);
    printf("x!=y: %d\n", x != y);
    printf("x>y: %d\n", x > y);
    printf("x<y: %d\n", x < y);
    printf("x>=y: %d\n", x >= y);

    printf("x&&y: %d\n", x && y);
    printf("x||y: %d\n", x||y);
    printf("!y: %d\n", !y);

}