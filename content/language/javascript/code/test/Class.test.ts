import { User, Rabbit, Cat } from '../Class';

const user = new User("John");

const rabbit = new Rabbit("Tomas");

const cat = new Cat("God");

describe('Class getter setter test', () => {
    it('getter', () => {
        console.log(user.name);
    });

    it('setter', () => {
        new User("man");
        user.name = "fe"
    });
});

describe('Class Extends test', () => {
    it('run', () => {
        console.log(rabbit.name)
        rabbit.run(100)
    })
    it('stop', () => {
        console.log(rabbit.speed)
        rabbit.stop()
    })
    it('hide', () => {
        rabbit.hide()
    })

    it('sound', () => {
        console.log(cat.name)
    })
})