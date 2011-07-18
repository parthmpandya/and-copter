package com.shaubert.andcopter.jni;

public class BabyEngineJNI {

    static {
        System.loadLibrary("baby-engine");
    }
    
    private native void nativeOnSurfaceCreate();
    private native void nativeOnSurfaceChange(int width, int height);
    private native void nativeOnDraw();
    private native void nativeRelease();
    private native void nativeSetLogging(boolean on);
    
    public synchronized void onSurfaceCreate() {
        nativeOnSurfaceCreate();
    }
    
    public synchronized void onSurfaceChange(int width, int height) {
        nativeOnSurfaceChange(width, height);
    }
    
    public synchronized void onDraw() {
        nativeOnDraw();
    }
    
    public synchronized void release() {
        nativeRelease();
    }
    
    public void setLogging(boolean on) {
        nativeSetLogging(on);
    }

}
