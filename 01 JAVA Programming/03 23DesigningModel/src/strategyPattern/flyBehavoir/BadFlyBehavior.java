package strategyPattern.flyBehavoir;

import util.utility;

public class BadFlyBehavior implements IFlyBehavior {

    @Override
    public void fly() {
        utility.println("just bad fly!");
    }
}
