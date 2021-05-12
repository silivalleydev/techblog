---
title: "C언어 - 7강"
metaTitle: "C언어 - 7강"
metaDescription: "This is the meta description for this page"
---

## 매개변수 사이의 자료전달 방법

### 값에의한 자료전달(call by value)
- 기본적인 자료전달 방법
- 실 매개변수와 형식 매개변수 사이에 값의 전달
- 호출한 함수의 실행이 끝난 다음 전달 받은 값을 되돌려 받지는 못한다.

### 참조에 의한 자료전달(call by reference)
- 호출함수와 피 호출함수의 매개변수 값을 서로 교환할 수 있는 자료 전달 방법
- 값을 전달하는 것이 아니라 실 매개변수의 값이 들어있는 주소 값이 전달된다.

### 값에 의한 자료전달 방법

``` 
// 함수정의(형식 매개변수) <== int x,int y가 형식 매개변수로 함수 호출시 매개변수 자료전달(값전달)
int fcn1(int x, int y)

// 함수호출 <== 10, 20이 실 매개변수
fnc1(10, 20);
```

### 매개변수사이의 자료전달 방법

```
void swap(int x, int y);

int main() {
   int a=3, b=5;

   // 주소값 전달시 변수명 앞에 &을 붙힌다.
   swap(&a, &b);
}

// *을 표시하여 주소값을 전달받음
void swap(int *x, int *y) {
   int temp;
   temp = *x;
   *x = *y;
   *y = temp;
}

//a=5, b=3으로 바뀜.. 주소값을 참조했기때문
```


### 기억클래스(storage class)
- 변수를 기억공간의 특정 영역에 할당하는 방법
- 즉, 각 변수의 유효범위와 존속기간을 설정
   - 변수의 사용위치에 따라
      - 지역변수
      - 전역변수
   - 변수의 존속기간에 따라
      - 자동변수
      - 정적변수
      - 외부변수
      - 레지스터변수


### 지역변수
- 특정범위 내에서만 통용되는 변수
- 선언된 블록이나 함수 내에서만 사용가능
- 함수에서 사용되는 매개변수도 해당

### 전역변수
- 함수밖이나 외부파일에서 선언되어 프로그램 전체에 걸쳐 사용될 수 있는 변수

### 전역변수와 지역변수의 비교
- 동일 범위 내에서는 지역변수가 우선
- 전역변수의 선언은 프로그램 선두에 위치
- 가급적 지역변수를 사용하는 것이 효율적
   - 함수의 독립성 향상
   - 디버깅 효율 향상
   - 기억공간 절약

## 기억클래스의 종류

### 변수의 기억클래스 종류
- 변수의 초기화, 존속기간, 유효범위에 따라 구별
   - 자동변수(auto)
   - 정적변수(static)
   - 외부변수(extern)
   - 레지스터 변수(register)

### 선언방법
- 기억클래스 자료형 변수명
```
auto int a;
static int b;
extern int c;
register int d;
```

### 자동변수
- 함수 실행시 만들어지고, 실행이 끝나면 기억공간이 제거됨
- 예약어 auto를 사용(생략가능)
- 통용 범위는 변수가 선언된 블록이나 함수 내로 한정
- 초기화가 필요

### 정적변수
- 기억영역이 프로그램 끝날때까지 유지
- 예약어 static을 사용
- 전역변수에 해당
- 변수의 값은 프로그램 실행중 계속 유지
- 초기화가 없으면 0으로 초기화됨

### 외부변수
- 함수의 외부에서 선언
- 예약어 extern을 사용
- 전역변수에 해당
- 초기화가 없으면 0으로 초기화됨
- 다른 파일에서 외부변수로 선언된 변수의 값을 참조할 수 있다.

### 레지스터변수
- CPU 내의 레지스터에 자료를 저장하고자할때
- 예약어 register를 사용
- 자동 변수와 동일한 속성
- 프로그램의 실행속도 증가를 목적으로 사용(주로 반복문에서 카운터 변수로 사용)