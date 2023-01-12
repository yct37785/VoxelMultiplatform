package com.voxel;
import androidx.annotation.NonNull;

import com.facebook.react.ReactPackage;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.ViewManager;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/*
consolidate all our custom native modules to pass to ReactNativeHost's getPackages()
 */
public class MyAppPackage implements ReactPackage {
    @NonNull
    @Override
    public List<NativeModule> createNativeModules(@NonNull ReactApplicationContext reactContext) {
        List<NativeModule> modules = new ArrayList<>();
        // add our custom modules here
        // modules.add(new AppInstallDate(reactContext));
        return modules;
    }

    @NonNull
    @Override
    public List<ViewManager> createViewManagers(@NonNull ReactApplicationContext reactContext) {
        // managers are singletons so no duplicate issues
        // ViewManager[] sourceArray = { new ReactCanvas(reactContext) };
        ViewManager[] sourceArray = { };
        return Arrays.asList(sourceArray);
    }
}
