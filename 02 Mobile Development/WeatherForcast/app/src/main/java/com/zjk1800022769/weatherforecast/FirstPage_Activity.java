package com.zjk1800022769.weatherforecast;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Date;


public class FirstPage_Activity extends Activity {

    private String strOfToday = (String)this.getResources().getText(R.string.strOfToday);
    private String strOfPublish = (String)this.getResources().getText(R.string.strOfPublish);

    @Override
    public void onCreate(Bundle forSaveInstance) {
        super.onCreate(forSaveInstance);
        setContentView(R.layout.firstpage);

        TextView cityWeather1_textView = findViewById(R.id.cityWeather_textView);
        TextView cityWeather2_textView = findViewById(R.id.city_TextView);
        cityWeather1_textView.setText(" 北京天气");
        cityWeather2_textView.setText("北京");


        Date date = new Date();
        SimpleDateFormat simpleDateFormat;
        //设置发布时间
        TextView publishTime_textView = findViewById(R.id.publishTime_textView);
        simpleDateFormat = new SimpleDateFormat("HH:mm");
        StringBuilder sb = new StringBuilder();
        sb.append(strOfToday).append(simpleDateFormat.format(date))
                .append(strOfPublish);
        publishTime_textView.setText(sb.toString());
        //设置当天星期几
        TextView weekDay = findViewById(R.id.weekDay_textView);
        simpleDateFormat = new SimpleDateFormat("EEEE");
        System.out.println(simpleDateFormat.format(date));
        sb.append(strOfToday).append(" ").append(simpleDateFormat.format(date));
        weekDay.setText(sb.toString());
    }
}
