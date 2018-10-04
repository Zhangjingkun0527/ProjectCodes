package strategyPattern.quackBehavoir;

import util.utility;

public class GaGaQuackBehavoir implements IQuackBehavior {
    @Override
    public void quack() {
        utility.println("GaGa~~~");
    }
}
