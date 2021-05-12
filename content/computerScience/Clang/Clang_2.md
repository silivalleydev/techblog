---
title: "C언어 - 2강"
metaTitle: "C언어 - 2강"
metaDescription: "This is the meta description for this page"
---

## 상수와 변수

### 자료형
- 프로그램에서 사용하는 자료의 형태
- 상수와 변수로 구분하여 사용

#### 프로그램에서 자료(data) 처리를 위해서는
- 자료의 생성과 저장, 처리과정이 필요

#### C 프로그램은
- 수 많은 명령어와 자료들로 구성
- 이들 자료의 정확한 처리와 효율적인 활용이 필요

#### C언어는 여러가지 종류의 자료형(data type)을 지원

### 상수(constant)
- 항상 고정된 값을 갖는 자료
- 값이 한번 정해지면 프로그램 도중 그 값을 변경할 수 없는 수
   - 정수형 상수
   - 실수형 상수
   - 문자형 상수
   - 문자열 상수

#### 정수형 상수
- 10진수, 8진수, 16진수로 표현

- 10진 상수
   - 예: 10, -10, 999
   - 0~9의 숫자를 사용하며 0으로 시작할 수 없다
- 8진 상수
   - 예: 011, 055
   - 0~7까지의 숫자를 사용하며 숫자앞에 0을 붙힌다.
- 16진 상수
   - 예: 0xac, 0X2A
   - 0~9와 A~F를 사용하며, 숫자앞에 0x나 0X를 붙인다.
- unsigned형 상수
   - 예: 12u, 067u, 0XFAU
   - 부호 없는 상수를 표현하며, 숫자뒤에 u나 U가 붙는다.
- long형 상수
   - 예: 12345l, 0XFFL
   - 큰길이의 정수를 표현하며, 숫자뒤에 l이나 L을 붙인다.

#### 실수형 상수
- 부동소수점 형 상수
- double형을 기본 자료형으로 사용
- 소수형식
   - 예: 12.345, 3.14, .5
   - 소수점을 사용하여 표현
- 지수형식
   - 예: 12E3(=12000), 5e-2(=0.05)
   - 10진수와 e(E)를 사용하여 표현
- float형 상수
   - 예: 3.14f, 3.14E-3F
   - 숫자뒤에 f나 F를 붙인다.
- long double형 상수
   - 예: 3.14l, 3.14E-3L
   - 숫자뒤에 l이나 L을 붙인다.

#### 문자형 상수
- 단일 인용부호('')로 묶여있는 1개의 영문자나 숫자문자
- 내부적으로는 해당문자의 ASC|| 코드값이 사용
   - 예를 들어 'A'는 내부적으로 65(아스키코드값)가 사용된다.
- Escape 문자: 키보드에 나타나있지 않은 문자
   - \a: 경고음(alert) 출력
   - \b: 백스페이스
   - \f: 새페이지
   - \n: 출력시 줄바꿈
   - \r: 커서를 행의 시작위치로 이동
   - \t: 수평탭
   - \0: 아스키코드값이 0인 문자(null문자)

#### 문자열 상수
- 이중 인용부호("")로 묶여있는 복수개의 영문자나 숫자
- 기억공간에 보관될 때는 문자열 끝에 null문자(\0)가 추가
   - 예를 들어 문자열 "SEOUL KOREA"의 기억 공간 보관 형태  
   "SEOUL KOREA" => |S|E|O|U|L| |K|O|R|E|A|\0|

### 변수(variable)
- 변할 수 있는값
- 프로그램에서 변수는
   - 프로그램 실행 도중 변할 수 있는 값이 저장되는 기억 공간을 의미
   - 예를들어 i=10;은 i는 변수명이고 10이란 값을 i라는 이름으로 정의된 기억공간에 저장한다는 의미
- 이러한 변수속에 들어가는 값은 수시로 변경될 수 있다.
- 따라서 변수는 사용 전에 반드시 선언하여 컴파일러가 기억공간에 일정 공간을 확보할 수 있도록 해야함

#### 변수의 특징
- 모든 변수는 이름이 있다.(변수명)
- 모든 변수는 정해진 자료형이 있다.
- 모든 변수는 할당된 값을 갖는다.

#### 변수명의 정의 규칙
- 모든 변수는 사용되기 전에 선언되어야한다.
- 변수명은 반드시 영문자나 밑줄(_)로 시작해야한다.
- 변수명은 중간에 숫자, 밑줄(_)을 섞어서 명명할 수 있다.
- 변수명은 중간에 밑줄(_) 이외의 특수문자($,#,?)를 섞어서 명명할 수없다.
- 변수명은 대, 소문자를 구별하여 사용한다.
- 변수명으로 예약어들은 사용할 수 없다.

## 자료형과 변수선언
### 변수
- 자료를 저장할 기억공간을 확보하고 이 공간에 이름을 붙여준것

#### 변수선언
- 확보된 기억공간에 이름을 부여하는 것

#### 이러한 변수선언을 위해 자료형이 필요

### 자료형

#### 기본형
- 정수형: int, short, long, unsigned
- 실수형: float, double, long double
- 문자형: char, unsigned char
- 열거형: enum
- 형없음: void

#### 확장형
- 배열형
- 함수형
- 포인터형
- 구조체형


## 기본자료형의 크기와 범위

### 정수형
- int형, short형, long형, unsigned형
- 운영체제에 따라 표현범위가 다름

#### 종류
- short int 
   - 표현범위: -32768 ~ 32767
   - 크기: 2byte
- long int 
   - 표현범위: -2147483648 ~ 2147483647
   - 크기: 4byte
- int 
   - 표현범위: -2147483648 ~ 2147483647
   - 크기: 2byte
- unsigned short int 
   - 표현범위: 0 ~ 65535
   - 크기: 2byte
- unsigned long int
   - 표현범위: 0 ~ 4294967295
   - 크기: 4byte
- unsigned int
   - 표현범위: 0 ~ 4294967295
   - 크기: 4byte

### 실수형
- float, double, long double
- 기본형은 double형

#### 종류
- float
   - 표현범위: 3.4*10 ~
   - 크기: 4byte
- double
   - 표현범위: 1.7*10 ~
   - 크기: 8byte
- long double
   - 표현범위: 1.7*10 ~
   - 크기: 8byte

### 문자형
- char형, unsigned char형
- 아스키코드를 사용하여 처리
- -128 ~ 127까지의 값 표현

#### 종류
- char
   - 표현범위: -128 ~ 127
   - 크기: 1byte
- unsigned char
   - 표현범위: 0 ~ 255
   - 크기: 1byte

### 열거형
- 숫자 대신 단어를 사용
- 형식: enum 태그명 {열거자1, 열거자2}

## 변수선언
- 변수명과 변수가 가질 자료형을 저장하여 변수를 위한 기억 공간을 할당하는 것
- 형식: 자료형 변수명

### 변수선언 시 고려사항
- 변수에 저장될 값 크기(범위)
- 변수의 선언 위치
- 변수의 초기화

## 선행처리기
- 컴파일에 앞서 프로그램 선두에 선언된 지시자들을 미리 처리하는 역할 수행

### 선행처리기의 종류

#### #include
- 기능: 파일포함

#### #define
- 기능: 매크로 정의

#### #if #else #elif #endif
- 기능: 조건부 컴파일

### 선행처리기를 사용할때 주의할 점
- 반드시 #으로 시작해야한다.
- 명령문 끝에는 세미콜론을 붙이지 않는다.
- 한줄에 하나의 명령만 쓴다.
- 소스 프로그램의 첫 부분에 위치한다.

### 파일포함
- #include
   - #include는 C언어에서 제공되는 헤더파일(*.h)를 자신의 소스파일에 읽어들여 함께 컴파일 하고자 할 때 사용
- C프로그램에서 표준함수인 printf(), scanf() 등을 사용하려면
   - 이 함수들의 원형(prototype)이 선언되어 있는 표준 입출력 헤더파일인 studio.h를 #include 시켜야함

### 매크로 정의
- #define
   - #define은 매크로를 정의할 때 사용
- 매크로
   - 선행처리기 #define을 사용하여 단순 치환되는 자료
   - 프로그램 작성 시에 명령어나 수식 또는 상수 값이 자주 사용될 떄 이들을 대표하는 이름을 붙여 사용하는 대상
- 매크로 정의
   - 매크로 상수 정의
   - 매크로 함수 정의

### 매크로 상수 정의
- #define ADDR "사평대로"

### 매크로 함수 정의
- #define PLUS(x, y)(x + y)

### 조건부 컴파일
-  #if #else #elif #endif
   - 조건에 따라 프로그램을 컴파일 하는 명령
   - 최적의 코드로 프로그램을 작성할 수 있기 떄문에 시스템 성능향상
- #if와 #elif 다음에는 컴파일 여부를 결정하는 조건문 필요
   - 조건문은 선행 처리과정에서 진위 여부를 판단할 수 있어야함
   - 변수지정이나 함수 호출 불가
   - 주로 매크로 값이 사용

