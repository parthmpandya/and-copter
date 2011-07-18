package com.shaubert.andcopter;

import android.util.Log;

import javax.microedition.khronos.opengles.GL10;

public class Game extends Group {

    private Rocks rocks;
    private Quad helicopter;
    
    private float width;
    private float height;
    
    public Game(float width, float height) {
        this.width = width;
        this.height = height;
        this.rocks = new Rocks(width, height);
        
        this.helicopter = new Quad(0.3f, 1);
        this.helicopter.translate(-(width/2) + helicopter.getWidth()/2 + 0.1f, height/2 - helicopter.getHeight()/2, 0);
        
        add(rocks);
        add(helicopter);
    }
    
    public void setup(GL10 gl) {
    }
    
    @Override
    public void draw(GL10 gl) {
        if (rocks.has2DCollision(helicopter)) {
            rocks.pause();
            remove(rocks);
            
            rocks = new Rocks(width, height);
        }
        super.draw(gl);
    }
    
    public void moveHelicopterUp() {
        helicopter.move(0, 0.05f, 0);
        logHelicopterBounds();
    }

    public void moveHelicopterDown() {
        helicopter.move(0, -0.05f, 0);
        logHelicopterBounds();
    }
    
    private void logHelicopterBounds() {
        Log.d(this.getClass().getSimpleName(), String.format("new helicopter bounds[l=%f,t=%f,r=%f,b=%f]", 
                helicopter.getLeft(), helicopter.getTop(), helicopter.getRight(), helicopter.getBottom()));
    }
}
