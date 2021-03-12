---
title: "C언어 - 5강"
metaTitle: "C언어 - 5강"
metaDescription: "This is the meta description for this page"
---

## 제어문

### 프로그램 언어의 제어 구조
- 순차적 제어: 특별한 지정이 없는 한 위에서 아래로 수행되는 제어구조
- 선택적 제어: 주어진 조건에 따라 특정 부분으로 수행을 옮기는 분기 제어구조
- 반복적 제어: 특정 부분을 일정한 횟수 만큼 반복 수행하는 반복 제어구조

### 선택제어문의 종류
- if 문

```
if (조건)
   명령문1;
else if (조건)
   명령문2;
else
   명령문3;
```

- switch ~ case 문

```
switch(수식) {
   case 값1: 명령문1;
   case 값2: 명령문2;
   default: 명령문3;
}
```

- goto문(무조건 분기)
   - 프로그램 수행도중에 원하는 곳으로 제어를 무조건적으로 옮긴다.
```
Label:

goto Label; 
```

### 반복 제어문
- for문
- while문
- do~while문
```
do {
   반복실행 문장;
} while(조건식);
```

### 기타제어문
- break문: 반복명령 실행도중 강제적으로 반복문을 빠져나오는데 사용
- continue문: 루프 실행중에 루프를 다시 실행하고자 할때 사용