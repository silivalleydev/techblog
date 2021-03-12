#include <stdio.h>
#define ADDR "사평대로"
#define PLUS(x, y)(x + y)
// command + shift + b <-- 빌드 및 실행
// 빌드는 gcc build active file 선택
// 실행은 exec -> Continue without Scanning the task output

// main함수 바깥에 선언하면 전역변수로 어디서든 사용가능
int val=10;

void func() {
    int val=20;
    printf("func에서 val값=%d\n", val);
}

int main(void) {
    printf("hello, world, C!\n");

    // 지역변수로 선언(main함수 내에서만 사용가능)
    int a, b;
    a=100;
    b=50;

    printf("a=%d, b=%d\n", a, b);

    char ch;
    int in;
    ch = in = 'A';// 'A'는 아스키코드로 65

    printf("ch=%d\n", ch);
    printf("in=%d\n", in);

    ch = in = 100;
    printf("ch=%c\n", ch);
    printf("in=%c\n", in);

    enum day1 {SUN, MON, TUE, WED, THU, FRI, SAT} d1;
    enum day2 {sun=2, mon, tue, wed, thu, fri, sat} d2;

    d1 = WED;
    d2 = wed;

    printf("열거형 d1 저장된 값은 %d 입니다.\n", d1);
    printf("열거형 d2 저장된 값은 %d 입니다.\n", d2);

    int num1, num2;
    num1=32767+1;
    num2=-32768-1;
    printf("num1=%d\n",num1);
    printf("num2=%d\n",num2);
    printf("main에서 val값=%d\n", val);
    func();

    int i, sum;

    for(i=1; i<10; i++)
        sum=sum+i;
    printf("sum값=%d\n", sum);
    printf("매크로값: %s\n", ADDR);
    printf("매크로함수: %d", PLUS(3, 7));


}

