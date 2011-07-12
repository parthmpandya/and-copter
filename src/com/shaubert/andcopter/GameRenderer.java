package com.shaubert.andcopter;

import android.content.Context;
import android.opengl.GLSurfaceView.Renderer;
import android.opengl.GLU;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GameRenderer implements Renderer {

    private static final float FOV_Y = 45.0f;
    private static final int CAMERA_Z = -2; 
    
    private Mesh mesh;
    private float angle;
    private Light light;
    
    public GameRenderer(Context context) {        
//        mesh = new Cube(1, 1, 1);        
//        mesh.setBitmap(BitmapFactory.decodeResource(context.getResources(), R.drawable.icon));
//        light = new Light(1f, 1f, -2f, 1f);
    }
    
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        gl.glClearColor(0, 0, 0, 0.5f);
        gl.glClearDepthf(1.0f);
        gl.glEnable(GL10.GL_DEPTH_TEST);
        gl.glDepthFunc(GL10.GL_LEQUAL);
        gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT, GL10.GL_NICEST);
        
        if (light != null) {
            light.apply(gl);
        }
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
        mesh = new Game(gameHeight * aspect, gameHeight);
    }
    
    @Override
    public void onDrawFrame(GL10 gl) {
        gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        
        gl.glTranslatef(0, 0, CAMERA_Z);
//        gl.glRotatef(angle, 1.0f, 0.3f, 1.0f);
        mesh.draw(gl);
        gl.glLoadIdentity();
//        angle += 5f;
    }

}
