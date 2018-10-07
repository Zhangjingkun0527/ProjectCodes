package strategyPattern.quackBehavoir;

import util.utility;

public class NoQuackBehavoir implements IQuackBehavior {
    @Override
    public void quack() {
        utility.println("I can not quack!!OH!shit!");
    }
}
