package com.shaubert.andcopter;

import android.graphics.Bitmap;

import java.util.ArrayList;
import java.util.List;

import javax.microedition.khronos.opengles.GL10;

public class Group extends Mesh{

    protected List<Mesh> meshs;
    
    public Group() {
        meshs = new ArrayList<Mesh>();
    }    
    
    public void add(Mesh mesh) {
        meshs.add(mesh);
    }
    
    public void add(int location, Mesh mesh) {
        meshs.add(location, mesh);
    }
    
    public void remove(Mesh mesh) {
        meshs.remove(mesh);
    }
    
    public void remove(int location) {
        meshs.remove(location);
    }
    
    public void clear() {
        meshs.clear();
    }

    public int size() {
        return meshs.size();
    }
    
    @Override
    protected void setColor(float red, float green, float blue, float alpha) {
        super.setColor(red, green, blue, alpha);
        for (Mesh mesh : meshs) {
            mesh.setColor(red, green, blue, alpha);
        }
    }
    
    @Override
    public void setBitmap(Bitmap bitmap) {
        for (Mesh mesh : meshs) {
            mesh.setBitmap(bitmap);
        }
    }

    @Override
    public float getLeft() {
        if (meshs.isEmpty()) {
            return x;
        }
        minX = meshs.get(0).getLeft();
        for (Mesh mesh : meshs) {
            minX = Math.min(minX, mesh.getLeft());
        }
        return minX + x;
    }
    
    @Override
    public float getRight() {
        if (meshs.isEmpty()) {
            return x;
        }
        maxX = meshs.get(0).getRight();
        for (Mesh mesh : meshs) {
            maxX = Math.max(maxX, mesh.getRight());
        }
        return maxX + x;    }
    
    @Override
    public float getBottom() {
        if (meshs.isEmpty()) {
            return y;
        }
        minY = meshs.get(0).getBottom();
        for (Mesh mesh : meshs) {
            minY = Math.min(minY, mesh.getBottom());
        }
        return minY + y;
    }
    
    @Override
    public float getTop() {
        if (meshs.isEmpty()) {
            return y;
        }
        maxY = meshs.get(0).getTop();
        for (Mesh mesh : meshs) {
            maxY = Math.max(maxY, mesh.getTop());
        }
        return maxY + y;
    }
    
    @Override
    public void draw(GL10 gl) {
        gl.glPushMatrix();
        
        gl.glTranslatef(x, y, z);
        gl.glRotatef(rx, 1f, 0, 0);
        gl.glRotatef(ry, 0, 1f, 0);
        gl.glRotatef(rz, 0, 0, 1f);
        for (Mesh mesh : meshs) {
            mesh.draw(gl);
        }
        
        gl.glPopMatrix();
    }
}
