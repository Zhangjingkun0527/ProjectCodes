package com.zjk1800022769.weatherforecast;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Date;


public class FirstPage_Activity extends Activity {

    @Override
    public void onCreate(Bundle forSaveInstance) {
        super.onCreate(forSaveInstance);
        setContentView(R.layout.firstpage);

        TextView cityWeather1_textView = findViewById(R.id.cityWeather_textView);
        TextView cityWeather2_textView = findViewById(R.id.city_TextView);
        cityWeather1_textView.setText(" 北京天气");
        cityWeather2_textView.setText("北京");

        TextView publishTime_textView = findViewById(R.id.publishTime_TextView);
        Date date = new Date();
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("HH:mm");
        publishTime_textView.setText("今天" + simpleDateFormat.format(date)+ "发布");

    }
}
