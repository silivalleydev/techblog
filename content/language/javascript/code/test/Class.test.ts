import { User, Rabbit } from '../Class';

const user = new User("John");

const rabbit = new Rabbit("Tomas");

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
})