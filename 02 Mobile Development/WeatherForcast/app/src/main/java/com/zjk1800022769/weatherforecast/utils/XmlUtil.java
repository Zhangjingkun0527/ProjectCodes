package com.zjk1800022769.weatherforecast.utils;

import com.zjk1800022769.weatherforecast.Entity.TodayWeatherDetailInfoEntity;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserFactory;

import java.io.StringReader;

public class XmlUtil {

    public static TodayWeatherDetailInfoEntity[] convertWeatherXmlStringToEntity(String xml){
        TodayWeatherDetailInfoEntity[] wie = new TodayWeatherDetailInfoEntity[4];
        try {
            XmlPullParserFactory fac = XmlPullParserFactory.newInstance();
            XmlPullParser xmlPullParser = fac.newPullParser();
            xmlPullParser.setInput((new StringReader(xml)));
            int eventType = xmlPullParser.getEventType();
            int count = 0;
            while (eventType != XmlPullParser.END_DOCUMENT){
                switch (eventType){
                    case XmlPullParser.START_DOCUMENT:
                        break;

                    case XmlPullParser.START_TAG:
                        String tagName = xmlPullParser.getName();
                        eventType = xmlPullParser.next();
                        if (tagName.equals("weather")){
                            count++;
                            continue;
                        }
                        break;

                    case XmlPullParser.END_TAG:
                        break;
                }
            }
        } catch (Exception e) {

        }
        return wie;
    }
}
