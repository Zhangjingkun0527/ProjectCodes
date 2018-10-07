package strategyPattern.duck;

import strategyPattern.flyBehavoir.IFlyBehavior;
import strategyPattern.quackBehavoir.IQuackBehavior;

public abstract class Duck {
    protected Duck(){}
    protected IFlyBehavior iFlyBehavior;
    protected IQuackBehavior iQuackBehavior;

    public void fly(){
        iFlyBehavior.fly();
    }

    public void quack(){
        iQuackBehavior.quack();
    }

    public abstract void display();

    public void setIFlyBehavior(IFlyBehavior ifb){iFlyBehavior = ifb;}

    public void setIQuackBehavior(IQuackBehavior iqb){iQuackBehavior = iqb;}

}
