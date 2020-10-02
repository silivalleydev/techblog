# TypeScript

TypeScript 는 Microsoft에서 개발 및 유지 관리 하며 오픈 소스 프로그래밍 언어입니다. 

JavaScript 의 모든 구문과 의미를 지원 하는 동시에 정적 유형 지정 및  
ECMAScript의 상위 집합 인 더 풍부한 구문과 같은 몇 가지 추가 기능을 제공합니다.  

## TypeScript 설치하기

````
npm install -g typescript
````

## 트랜스파일링 실험

Typescript 컴파일러가 Typescript파일을 자바스크립트 파일로 변환하는 것을 트랜스파일링이라고 하는데,  
이를 실행해보기 위해 아래와 같은 파일을 작성해본다.  

- person.ts

````
class Person {
  private name: string;

  constructor(name: string) {
    this.name = name;
  }

  sayHello() {
    return "Hello, " + this.name;
  }
}

const person = new Person('Lee');

console.log(person.sayHello());
````

이때 트랜스파일링된 person.js의 자바스크립트 버전은 ES3입니다.  
이는 TypeScript 컴파일 타겟 자바스크립트 기본 버전이 ES3이기 때문입니다.  

만약, 자바스크립트 버전을 변경하려면 컴파일 옵션에 --target 또는 -t를 사용하면 됩니다.  
ES6 버전으로 트랜스파일링을 실행하려면 아래와 같이 옵션을 추가하면 됩니다.  
````
tsc person -t ES2015
````

````
// person.js
class Person {
    constructor(name) {
        this.name = name;
    }
    sayHello() {
        return "Hello, " + this.name;
    }
}
const person = new Person('Lee');
console.log(person.sayHello());
````

트랜스파일링이 성공하여 자바스크립트 파일이 생성되었으면, Node.js REPL을 이용해 트랜스파일링된 person.js를 실행해봅시다.  

````
node person.js
Hello, Lee
````

매번 옵션을 지정하는 것은 번거로운 일이기 때문에 tsc 옵션 설정 파일을 생성합니다.  
````
tsc --init
````

이렇게 하면 아래와 같이 tsconfig.json이 생성됩니다.  
````
{
  "compilerOptions": {
    /* Visit https://aka.ms/tsconfig.json to read more about this file */

    /* Basic Options */
    // "incremental": true,                   /* Enable incremental compilation */
    "target": "es5",                          /* Specify ECMAScript target version: 'ES3' (default), 'ES5', 'ES2015', 'ES2016', 'ES2017', 'ES2018', 'ES2019', 'ES2020', or 'ESNEXT'. */
    "module": "commonjs",                     /* Specify module code generation: 'none', 'commonjs', 'amd', 'system', 'umd', 'es2015', 'es2020', or 'ESNext'. */
    ...
  }
}

````

tsc 명령어 뒤에 파일명을 지정하면 tsconfig.json이 무시되기 때문에 조심해야합니다.  
````
tsc person
````

만약 파일명을 지정하지 않는다면 프로젝트 폴더 내의 모든 Typescript 파일이 모두 트랜스파일링 됩니다.  
````
tsc
````

상속관계에 있는 두개의 Typescript class 작성해봅시다.  
````
// person.ts
export class Person {
  protected name: string;

  constructor(name: string) {
    this.name = name;
  }
  sayHello() {
    return "Hello, " + this.name;
  }
}
````

````
// student.ts
import { Person } from './person';

class Student extends Person {
  study(): string {
    return `${this.name} is studying.`;
  }
}

const student = new Student('Lee');

console.log(student.sayHello());
console.log(student.study());
````

그러면 이제 두개의 파일을 한꺼번에 트랜스파일링 해보겠습니다.  
````
$ tsc
$ node student
Hello, Lee
Lee is studying.
````

--watch 또는 -w 옵션을 사용하면 트랜스파일링 대상 파일의 내용이 변경되었을 때  
이를 감지하여 자동으로 트랜스파일링이 실행됩니다.  
````
$ tsc --watch
[오후 4:47:31] File change detected. Starting incremental compilation...
````

또는 아래와 같이 tsconfig.json에 watch 옵션을 추가할 수도 있습니다.  
````
{
  // ...
  "watch": true
}
````

student.ts를 변경해 watch 기능이 동작하는지 확인해 봅시다.  
````
import { Person } from './person';

class Student extends Person {
  study(): string {
    return `${this.name} is studying!!`; // studying. → studying!!
  }
}

const student = new Student('Lee');

console.log(student.sayHello());
console.log(student.study());
````

## 변수

typescript에는 number, string, boolean, any 네 가지 타입이 있습니다.  
````
// variable
let isSuccess: boolean = true;
let firstName: string = "KIM";
let height: number = 185;
let initValue: any = 10;// any타입의 변수에는 아무거나 들어올 수 있습니다.
````

## 컬렉션

````
// collection
let list: number[] = [1,2,3];
let list2: Array<String> = ["1","2","3"];
````

## 함수

````
function addNumber(a: number, b: number) {
    return a + b;
}

let f1 = function(i: number): number { return i * i }
let f2 = (i: number):number => { return i * i }
````

## 인터페이스

인터페이스를 사용하면 인터페이스에서 선언한 값들은 사용해야합니다.  
다만, 이름뒤에 ?를 사용하면 옵셔널한 형태로 사용해도 안해도되게 할 수 있습니다.  

````
// Object interface
interface Person {
    name: string;
    age: number;
    height?: number; //optional
    move(): void;
}

let dylee: Person = {
    name: "leedayoung",
    age: 28,
    move: () => {}
}

// Function interface
interface SearchFunc {
    (src: string, substring: string):boolean;
}

let mySerchFunction:SearchFunc = (src: string, sub: string) => {
    return src.search(sub) != -1;
}
````

