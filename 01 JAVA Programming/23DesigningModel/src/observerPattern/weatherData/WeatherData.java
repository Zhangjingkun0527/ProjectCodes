package observerPattern.weatherData;

import observerPattern.observer.Observer;
import observerPattern.subject.Subject;

import java.util.ArrayList;

public class WeatherData implements Subject {
    private double mTemperature;
    private double mPressure;
    private double mHumidity;
    private ArrayList<Observer>  mObservers;

    public WeatherData(){
        mObservers = new ArrayList<>();
    }

    private double getTemperature(){
        return mTemperature;
    }

    private double getPressure(){
        return mPressure;
    }


    private double getHumidity(){
        return mHumidity;
    }

    public void dataChange(){
        notifyObserver();
    }

    @Override
    public void registerObserver(Observer observer) {
        mObservers.add(observer);
    }

    @Override
    public void notifyObserver() {
        for(Observer ob : mObservers){
            ob.update(getTemperature(), getPressure(), getHumidity());
        }
    }

    @Override
    public void removeObserver(Observer observer) {
        mObservers.remove(observer);
    }
}
