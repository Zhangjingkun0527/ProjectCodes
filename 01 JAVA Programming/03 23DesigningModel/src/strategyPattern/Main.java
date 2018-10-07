package strategyPattern;

import strategyPattern.ducks.*;
import strategyPattern.flyBehavoir.BadFlyBehavior;
import strategyPattern.quackBehavoir.NoQuackBehavoir;

public class Main {
    public static void main(String args[]){
        var rd =  new RedDuck();
        var gd = new GreenDuck();

        rd.fly();
        rd.quack();

        gd.fly();
        gd.quack();

        rd.setIFlyBehavior(new BadFlyBehavior());
        rd.setIQuackBehavior(new NoQuackBehavoir());
        rd.fly();
        rd.quack();

    }
}
