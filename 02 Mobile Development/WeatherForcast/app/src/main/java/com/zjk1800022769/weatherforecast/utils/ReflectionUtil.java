package com.zjk1800022769.weatherforecast.utils;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class ReflectionUtil {

    /**
     * 通过反射设置变量值
     * @param classType
     * @param fieldName
     * @param value
     */
    public static void setFieldValueThroughReflection(Class<?> classType, String fieldName, String value){
        try {
            Field field = classType.getField(fieldName);
            field.setAccessible(true);
            field.set(classType, value);
        } catch (Exception ignored){}
    }

    /**
     *  通过反射获得set方法设置变量值
     * @param classType
     * @param fieldName
     * @param value
     */
    public static void setFieldValueThroughtSetter(Class<?> classType, String fieldName, String value){
        StringBuilder sb = new StringBuilder();
        char firstLetter = fieldName.charAt(0);
        sb.append("set").append(fieldName.toUpperCase()).append(fieldName.substring(1));
        try {
            Method method = classType.getMethod(sb.toString(), String.class);
            method.invoke(classType, value);
        } catch (Exception ignored) {}
    }
}
