
// getter setter
export class User {
    private _name: string;

    constructor(name:string) {
        this._name = name;
    }

    get name(): string {
        return this._name
    }

    set name(value) {
        console.log('호출')
        this._name = value
    }
}

export class Animal {
    speed: number;
    name: string;

    constructor(name:string) {
        this.name = name;
        this.speed = 0;
    }

    run(speed: number) {
        this.speed = speed;
        console.log(`${this.name}은/는 속도 ${this.speed}로 달립니다.`);
    }

    stop() {
        this.speed = 0;
        console.log(`${this.name}이/가 멈췄습니다.`);
    }
}

export class Rabbit extends Animal {
    hide() {
        console.log(`${this.name}이/가 숨었습니다!`)
    }

    // 오버라이드 
    stop() {
        console.log('오버라이드 된 메서드');
        super.stop();
        this.hide();
    }
}

export class Cat extends Animal {
    sound: String;

    constructor(name: string) {
        super(name);
        this.sound = "Meow";
    }
}