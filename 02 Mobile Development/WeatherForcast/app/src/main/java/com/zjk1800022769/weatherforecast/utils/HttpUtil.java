package com.zjk1800022769.weatherforecast.utils;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.Xml;

import com.zjk1800022769.weatherforecast.R;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpUtil extends Thread{
    public static final int RESPONSE = 1;
    private static final String urlOfWeatherInfoApiThroughCityCode = "http://wthrcdn.etouch.cn/WeatherApi?citykey=";

    public Xml getWeatherInformationByCityName(String cityName){
        Xml xmlResult = null;
        String strResult = getXmlStringByCityCode(cityName);

        return xmlResult;
    }

    private String getXmlStringByCityCode(String cityCode){
        final String strOfUrl = urlOfWeatherInfoApiThroughCityCode + cityCode;
        final StringBuilder result = new StringBuilder();
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    URL url = new URL(strOfUrl);
                    HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                    conn.setConnectTimeout(8000);
                    conn.setReadTimeout(8000);
                    conn.setRequestMethod("GET");
                    InputStream inputStream = conn.getInputStream();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
                    String temp;
                    while ((temp = reader.readLine()) != null){
                        result.append(temp);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }).start();
        return result.toString();
    }
}
