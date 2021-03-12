#include "stdio.h"

int main() {
    char c='A';

    int i=10, j=20, k=30;

    printf("간단한 출력프로그램\n");
    printf("c=%c, c의 아스키코드 값은 %d\n", c, c);
    printf("i=%d, j=%d, k=%d\n", i, j, k);


    printf("%c\n", 123);
    printf("%d\n", 123);
    printf("%o\n", 123);
    printf("%x\n", 123);
    printf("%X\n", 123);
    printf("%f\n", 123.4353);
    printf("%e\n", 123.3242);
    printf("%s\n", "sdcsdacdsav");


    printf("|%d|\n", 123);
    printf("|%5d|\n", 123);
    printf("|%-5d|\n", 123);
    printf("|%05d|\n", 123);

    int j1, j2;

    printf("정수를 입력하시오\n");
    scanf("%d %d", &j1, &j2);
    printf("j1=>%d, j2=>%d\n", j1, j2);    
}
