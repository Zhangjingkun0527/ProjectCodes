package strategyPattern.flyBehavoir;

import util.utility;

public class NoFlyBehavoir implements IFlyBehavior {

    @Override
    public void fly() {
        utility.println("I can not fly!fuck!");
    }
}
