package strategyPattern.ducks;

import strategyPattern.duck.Duck;
import strategyPattern.flyBehavoir.*;
import strategyPattern.quackBehavoir.*;

public class GreenDuck extends Duck {

    public GreenDuck(){
        iFlyBehavior = new GoodFlyBehavior();
        iQuackBehavior = new GeGeQuackBehavoir();
    }

    @Override
    public void display() {

    }
}
