package com.shaubert.andcopter;

import com.shaubert.andcopter.jni.BabyEngineJNI;

import android.opengl.GLSurfaceView.Renderer;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnKeyListener;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class NativeRenderer implements Renderer, OnKeyListener {

    private BabyEngineJNI jni;
    
    public NativeRenderer() {
        jni = new BabyEngineJNI();
    }
    
    @Override
    public boolean onKey(View v, int keyCode, KeyEvent event) {
        return false;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        jni.onSurfaceCreate();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        jni.onSurfaceChange(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        jni.onDraw();
    }
    
    public boolean onTrackballEvent(MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_MOVE && event.getHistorySize() > 1) {
            float dy = event.getY();
            if (dy != 0) {
                if (dy < 0) {
                    jni.moveHelicopter(0.005f);
                } else {
                    jni.moveHelicopter(-0.005f);
                }
                return true;
            }
        }
        return false;
    }
    
    public void release() {
        jni.release();
    }
}
