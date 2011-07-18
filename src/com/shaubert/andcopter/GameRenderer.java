package com.shaubert.andcopter;

import android.content.Context;
import android.opengl.GLSurfaceView.Renderer;
import android.opengl.GLU;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnKeyListener;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GameRenderer implements Renderer, OnKeyListener {

    private static final float FOV_Y = 45.0f;
    private static final int CAMERA_Z = -2; 
    
    private Game game;
    
    public GameRenderer(Context context) {        
    }
    
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        gl.glClearColor(0, 0, 0, 0.5f);
        gl.glClearDepthf(1.0f);
        gl.glEnable(GL10.GL_DEPTH_TEST);
        gl.glDepthFunc(GL10.GL_LEQUAL);
        gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT, GL10.GL_NICEST);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        gl.glViewport(0, 0, width, height);
        gl.glMatrixMode(GL10.GL_PROJECTION);
        gl.glLoadIdentity();
        float aspect = (float) width / (float) height;
        GLU.gluPerspective(gl, FOV_Y, aspect, 0.1f, 10.0f);
        gl.glMatrixMode(GL10.GL_MODELVIEW);
        gl.glLoadIdentity();
        
        float gameHeight = (float)(-CAMERA_Z * Math.tan(Math.toRadians(FOV_Y / 2))) * 2; 
        game = new Game(gameHeight * aspect, gameHeight);
    }
    
    @Override
    public void onDrawFrame(GL10 gl) {
        gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        
        gl.glTranslatef(0, 0, CAMERA_Z);
        game.draw(gl);
        gl.glLoadIdentity();
    }

    @Override
    public boolean onKey(View v, int keyCode, KeyEvent event) {
        if (game != null && event.getAction() == KeyEvent.ACTION_DOWN) {
            switch (keyCode) {
                case KeyEvent.KEYCODE_DPAD_UP:
                    game.moveHelicopterUp();
                    return true;
                case KeyEvent.KEYCODE_DPAD_DOWN:
                    game.moveHelicopterDown();
                    return true;
            }
        }
        return false;
    }

    public boolean onTrackballEvent(MotionEvent event) {
        if (game != null && event.getAction() == MotionEvent.ACTION_MOVE && event.getHistorySize() > 1) {
            float dy = event.getY();
            if (dy != 0) {
                if (dy < 0) {
                    game.moveHelicopterUp();
                } else {
                    game.moveHelicopterDown();
                }
                return true;
            }
        }
        return false;
    }
}
