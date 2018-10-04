package strategyPattern.quackBehavoir;

import util.utility;

public class GeGeQuackBehavoir implements IQuackBehavior {
    @Override
    public void quack() {
        utility.println("GeGe~~");
    }
}
