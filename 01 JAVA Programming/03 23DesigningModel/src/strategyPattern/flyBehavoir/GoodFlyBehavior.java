package strategyPattern.flyBehavoir;

import util.utility;

public class GoodFlyBehavior implements IFlyBehavior {

    @Override
    public void fly() {
        utility.println("just good fly");
    }
}
