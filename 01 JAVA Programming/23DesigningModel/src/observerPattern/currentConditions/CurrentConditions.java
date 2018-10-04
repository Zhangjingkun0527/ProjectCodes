package observerPattern.currentConditions;

import observerPattern.observer.Observer;
import util.utility;

public class CurrentConditions implements Observer {

    private double mTemperature;
    private double mPressure;
    private double mHumidity;

    @Override
    public void update(double mTemperature, double mPressure, double mHumidity) {
        this.mTemperature = mTemperature;
        this.mPressure = mPressure;
        this.mHumidity = mHumidity;
        display();
    }

    public void display(){
        utility.println("***Today temperature:" + mTemperature + "***");
        utility.println("***Today Pressure:" + mPressure + "***");
        utility.println("***Today Humidity:" + mHumidity + "***");
    }
}
