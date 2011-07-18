package com.shaubert.andcopter.trial;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.opengles.GL10;

public class Light {

    public static final float[] AMBIENT = { 0.5f, 0.5f, 0.5f, 1.0f };
    public static final float[] DIFFUSE = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    private int glLightIndex;
    private FloatBuffer position;
    private FloatBuffer confAmbient;
    private FloatBuffer confDiffuse;
    
    public Light() {
        this(GL10.GL_LIGHT1, AMBIENT, DIFFUSE, new float[] {0f, 0f, -2f, 1f});
    }
    
    public Light(float ... pos4x) {
        this(GL10.GL_LIGHT1, pos4x);
    }
    
    public Light(int glLightIndex, float ... pos4x) {
        this(glLightIndex, AMBIENT, DIFFUSE, pos4x);   
    }
    
    public Light(int glLightIndex, float[] confAmbient, float[] confDiffuse, float[] pos) {
        this.glLightIndex = glLightIndex;
        this.confAmbient = convertFloatArrayToBuffer(confAmbient);
        this.confDiffuse = convertFloatArrayToBuffer(confDiffuse);
        this.position = convertFloatArrayToBuffer(pos);
    }
    
    private FloatBuffer convertFloatArrayToBuffer(float[] array) {
        ByteBuffer vbb = ByteBuffer.allocateDirect(array.length * 4);
        vbb.order(ByteOrder.nativeOrder());
        FloatBuffer result = vbb.asFloatBuffer();
        result.put(array);
        result.position(0);
        return result;
    }
    
    public void apply(GL10 gl) {
        gl.glLightfv(GL10.GL_LIGHT1, GL10.GL_AMBIENT, confAmbient);
        gl.glLightfv(GL10.GL_LIGHT1, GL10.GL_DIFFUSE, confDiffuse);
        gl.glLightfv(GL10.GL_LIGHT1, GL10.GL_POSITION, position);
        gl.glEnable(GL10.GL_LIGHTING);
        gl.glEnable(glLightIndex);
    }
}
