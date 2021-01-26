const el = document.getElementById("test");

const Parent = (function (){
    function Parent(name) {
        this.name = name
    }

    Parent.prototype.sayHI = function(){
        return `Hi, ${this.name}`;
    }

    return Parent;
})()

// const Child = (function() {
    
//     // 자식 생성자 함수
//     function Child (name) {
//     this.name = name
//     }

//     // 자식 생성자 함수의 프로토 타입 객체를 부모 생성자 함수의 인스턴스로 교체(상속)
//     Child.prototype = new Parent();

//     // 자식 생성자 함수의 메서드를 정의
//     Child.prototype.bow = function() {
//         return 'Bow Wow!';
//     }

//     return Child;
// })();


const Child = (function() {
    
    function Child(name) {
        Parent.call(this, name);
    }

    Child.prototype = Object.create(Parent.prototype);
    Child.prototype.constructor = Child;
    Child.prototype.bow = function() {
        return 'Bow Wow!';
    }
    return Child;
})();

const ch = new Child('jack');


const div1 = document.createElement("div");

div1.innerHTML = ch.sayHI();

const div2 = document.createElement("div");

div2.innerHTML = ch.bow();

el.appendChild(div1); // Hi, jack
el.appendChild(div2); // Bow Wow!



