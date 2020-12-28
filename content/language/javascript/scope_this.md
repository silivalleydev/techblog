---
title: "스코프 & 함수 호출 방식에 의해 결정되는 this"
metaTitle: "스코프 & 함수 호출 방식에 의해 결정되는 this"
metaDescription: "This is the meta description"
---

## 스코프란?
스코프는 참조 대상 식별자(변수, 함수 이름과 같은 것)를 찾아내기 위한 규칙입니다.   자바스크립트는 이 규칙대로 식별자를 찾습니다.

### 지역변수, 전역변수 구분

전역에 선언된 변수는 전역 스코프를 갖는 전역 변수이고,  
자바스크립트의 경우에는 함수 내부에서 선언된 변수가 지역 스코프를 갖는 지역변수입니다.

```js
var a = 0; // 전역 변수

function abc(){
    var a = 2; // 지역변수
    console.log(a);
}

abc(); // a = 2
console.log(a); // a = 0;
```

### 스코프 체인

자바스크립트 엔진은 식별자(변수 또는 함수 이름)을 찾을때 자신이 속한 스코프 부터 찾고  
상위 스코프에서 찾습니다.  
스코프 체인은 스코프가 중첩되어있는 모든 상황에서 발생합니다.

```js
var x = 1;

function foo(){
    console.log(x); // -> 현재 자신의 스코프(foo 함수 내부)에 x가 없지만 상위 스코프인 전역에서 x를 찾는다.
}

console.log(x); // 1
foo(); // 1
```

### 렉시컬 스코프

함수를 어디에서 호출했는지가 아닌, 어디에서 선언했는지에 따라 결정되는 것을 렉시컬 스코프라고 합니다.  

자바 스크립트를 렉시컬 스코프를 따르고 있습니다.  

```js
var x = 1;

function foo() {
  var x = 10;
  bar();
}

function bar() {
  console.log(x);
}

foo(); // 1
bar(); // 1
```
  
따라서 같은 x라는 변수를 전역 변수와 foo 함수 내에서 선언하고,  
x 값을 찍는 함수 bar을 선언했을때  
foo함수와 bar함수를 전역에서 실행하면 콘솔에 찍히는 x값은 1이 되게 됩니다.  
왜냐하면 함수 bar를 선언한 시점에 해당 함수의 상위 스코프가 결정되는데,  
함수 bar는 전역스코프에서 선언됐기 때문에 bar의 상위 스코프는 전역 객체가됩니다.  
foo 함수 내에서 bar 함수가 실행되어도 bar 함수는 전역 스코프를 참조하기 때문에  
전역 스코프의 x값인 1이 되게됩니다.  
  

```js
var x = 1;

function foo() {
  var x = 10;
  
  function bar() {
    console.log(x);
  }
  
  bar();
}

foo(); // 10
console.log(x); // 1
```

만약 foo 함수 내에서 bar 함수를 선언했다면  
선언을 foo 함수 내에서 했기 때문에 bar 함수의 상위 스코프는 foo 함수가 되고  
foo 함수 스코프 내에서 선언된 x 값을 참조하여 10이 됩니다.

## 자바스크립트의 this

자바스크립트의 this는 함수를 호출할 때 함수가 어떻게 호출되었는지에 따라  
this에 바인딩할 객체가 동적으로 결정됩니다.  

### 전역 객체의 이해

먼저, 전역객체는 브라우저에서는 `window` 노드 서버에서는 `global`을 의미합니다.  
전역 객체는 전역 스코프를 갖는 전역 변수를 프로퍼티로 가지고 있습니다.  
전역 함수는 전역 객체에서 프로퍼티로 접근 할 수 있는 전역 변수의 메서드가 됩니다.  

```js
var x = 1;
function foo(){
    console.log('hi')
}

// 프로퍼티로 접근가능
window.x

// 프로퍼티로 접근 가능한 메서드
window.foo()

/*

전역 객체 안에 프로퍼티로 접근 가능하도록

Global Object

window = {
    ...,
    x: 1,
    foo: function(){
        console.log('hi)
    }        
}

*/
```

### 함수 호출의 this

기본적으로 전역함수와 내부함수의 this는 전역객체에 바인딩 됩니다.  

따라서 전역함수와 그 안의 내부함수의 this는 전역객체가 되게됩니다.  
```js
function foo() {
  console.log("foo's this: ",  this);  // window
  function bar() {
    console.log("bar's this: ", this); // window
  }
  bar();
}
foo();

```

메서드의 내부 함수의 this 또한 전역 객체가 됩니다.  
```js
var value = 1;

var obj = {
  value: 100,
  foo: function() {
    console.log("foo's this: ",  this);  // obj
    console.log("foo's this.value: ",  this.value); // 100
    function bar() {
      console.log("bar's this: ",  this); // window
      console.log("bar's this.value: ", this.value); // 1
    }
    bar();
  }
};

obj.foo();
```

콜백함수의 this도 전역 객체가 됩니다.  
```js
var value = 1;

var obj = {
  value: 100,
  foo: function() {
    setTimeout(function() {
      console.log("callback's this: ",  this);  // window
      console.log("callback's this.value: ",  this.value); // 1
    }, 100);
  }
};

obj.foo();
```

### 메소드 호출 this

함수가 객체의 프로퍼티 값이면 메서드로서 호출이되게 되는데, 이때 `this`는 해당 메서드를 소유한 객체가 됩니다.  

```js
var obj1 = {
  name: 'Lee',
  sayName: function() {
    console.log(this.name);
  }
}

var obj2 = {
  name: 'Kim'
}

// obj2에 sayName 메서드를 넣어줌
obj2.sayName = obj1.sayName;

obj1.sayName(); // this는 obj1이고 그 name값은 'Lee'
obj2.sayName(); // this는 obj2이고 그 name값은 'Kim'
```


### 생성자 함수 호출 this

자바스크립트에서 생성자 함수는 말 그대로 객체를 생성하는 역할을 합니다.  
기존 함수에 new 연산자를 붙여서 호출하면 해당 함수는 생성자 함수로 동작하는데,  
이때 new 연산자와 함께 생성자 함수를 호출하면 this 바인딩이 메소드나 함수 호출 때와는 다르게 동작합니다.  

생성자 함수의 this는 새로 생성한 객체를 가리킵니다.  
생성자 함수에 new 연산자를 붙이지 않고 호출할 경우 일반함수로서 호출되기 때문에 this는 전역 객체가됩니다.  

```js
// 생성자 함수 방식
function Person(name, gender) {
  this.name = name;
  this.gender = gender;
}

var me  = new Person('Lee', 'male');
console.dir(me);

var you = new Person('Kim', 'female');
console.dir(you);
```
