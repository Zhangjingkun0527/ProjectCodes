package com.zjk1800022769.weatherforecast.utils;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.support.v4.app.ActivityCompat;
import android.telephony.TelephonyManager;

import java.lang.reflect.Method;

public class NetUtil {
    public static final int NETWORK_NONE = 0;
    public static final int NETWORK_WIFI = 1;
    public static final int NETWORK_MOBILE = 2;

    public static final int OPEN_SUCCESS = 3;
    public static final int AUTHORITY_NOTALLOWED = 4;
    public static final int OPEN_FAILED = 5;

    /**
     * open mobile network, if failed then return the corresponding result;
     * @param currentContext
     * @return
     */
    public static int openMobileNetWork(Context currentContext){
        TelephonyManager telephonyManager = (TelephonyManager)currentContext.getSystemService(Context.TELEPHONY_SERVICE);
        if (isNetWorkAuthorityAllowed(currentContext)){
            try {
                Method setDataEnabled = telephonyManager.getClass().getMethod("setDataEnabled",boolean.class);
                setDataEnabled.invoke(telephonyManager, true);
                return OPEN_SUCCESS;
            } catch (Exception e){
                e.printStackTrace();
                return OPEN_FAILED;
            }
        } else {
            return AUTHORITY_NOTALLOWED;
        }
    }

    /**
     * check the network authority, and if false then open it, finally return whether network is opened
     * @param currentContext
     * @return is network opened
     */
    public static boolean isNetWorkAuthorityAllowed(Context currentContext){
        int state = ActivityCompat.checkSelfPermission(currentContext, "ACCESS_NETWORK_INTERNET");
        return state == 0;
    }

    /**
     * check network state
     * for api 22 and before
     * @param currentContext context
     * @return int
     */
    public static int getNetWorkState(Context currentContext){
        ConnectivityManager connectivityManager = (ConnectivityManager) currentContext.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo = connectivityManager.getActiveNetworkInfo();
        if (networkInfo == null){
            return NETWORK_NONE;
        }

        int nType = networkInfo.getType();
        if (nType == ConnectivityManager.TYPE_MOBILE){
            return NETWORK_MOBILE;
        } else if (nType == ConnectivityManager.TYPE_WIFI){
            return NETWORK_WIFI;
        }
        return  NETWORK_NONE;
    }
}
