---
title: "C언어 - 8강"
metaTitle: "C언어 - 8강"
metaDescription: "This is the meta description for this page"
---

## 배열의 개념

### 배열의 정의
- 동일한 자료형을 갖는 자료들의 리스트
- 배열의 각 요소는 하나의 변수로 취급
- 배열은 배열명과 첨자로 구분

### 배열의 선언 형태
- 1차원 배열
- 2차원 배열
- 3차원 배열

### 1차원 배열
- 배열의 첨자가 하나만 있는 배열
- 첨자의 개수는 배열 전체의 구성요소의 개수를 의미
- 배열의 각 요소는 배열명과 첨자로 구분
   - 첨자는 0부터 시작
- 배열의 각 요소는 배열명과 첨자로 구분
   - 자료형과 기억 클래스는 갖는다.

### 선언방법
- 자료형 배열명[개수]
- int a[10]

### 저장되는방식
- int a[3]; 으로 선언하면 메모리공간에 자료형 크기 만큼의 공간을 기억해놓는다.
- [ 4byte, 4byte, 4byte] 이런식으로

### 1차원 배열의 초기화
- 배열을 선언하면 기억공간을 초기화 해야함

#### 초기화 방법
- 배열선언 후 초기값 할당
- 배열 선언과 동시에 초기값 할당
- 외부로부터 자료를 입력받아 초기화

### 2차원 배열 선언
- 자료형 배열명[행의수][열의수]
- int a[3][4];
- int a[2][2] = {{1,2}, {3,4}};

### 3차원 배열 선언
- 자료형 배열명[면의수][행의수][열의수]
- int a[2][3][4];
- int a[2][2][2] = {{{1, 2},{2, 3}}, {{1, 2},{2, 3}}};

### char형 배열과 문자열
- 형식: char 배열명[문자열길이+1]
- char str[12]