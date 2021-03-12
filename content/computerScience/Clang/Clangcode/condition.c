#include "stdio.h"
#define CONDITION 1

int main() {
    #if CONDITION
        printf("\nA 프로그램을 컴파일");
    #else
        printf("\nB 프로그램을 컴파일");
    #endif
}