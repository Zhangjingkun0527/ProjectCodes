package strategyPattern.ducks;

import strategyPattern.duck.Duck;
import strategyPattern.quackBehavoir.*;
import strategyPattern.flyBehavoir.*;


public class RedDuck extends Duck {

    public RedDuck(){
        iFlyBehavior = new NoFlyBehavoir();
        iQuackBehavior = new GaGaQuackBehavoir();
    }

    @Override
    public void display() {

    }
}

