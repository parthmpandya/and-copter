package com.shaubert.andcopter;

import java.util.Iterator;
import java.util.Random;

import javax.microedition.khronos.opengles.GL10;

public class Game extends Group {

    private static final float PIECE_WIDTH = 0.1f;

    private Random random = new Random();
    private float lastTopHeight;
    private float lastBottomHeight;

    private float width;
    private float height;
    
    public Game(float width, float height) {
        this.width = width;
        this.height = height;
    }
    
    public void setup(GL10 gl) {
    }
    
    @Override
    public void draw(GL10 gl) {
        createObjects();
        moveObjects();
        cleanUpObjects();        
        super.draw(gl);
    }
    
    private void createObjects() {
        Plane plane = createNewPlane(lastTopHeight);
        lastTopHeight = plane.getHeight();
        plane.translate(width / 2, (height / 2) - (lastTopHeight / 2), 0);
        add(plane);
        
        plane = createNewPlane(lastBottomHeight);
        lastBottomHeight = plane.getHeight();
        plane.translate(width / 2, -(height / 2) + (lastBottomHeight / 2), 0);
        add(plane);
    }
    
    private Plane createNewPlane(float lastHeight) {
        float height = lastHeight + (random.nextInt(3) - 1) * 0.05f;
        if (height < 0) {
            height = 0;
        } else if (height > 0.5f) {
            height = 0.5f;
        }
        Plane plane = new Plane(PIECE_WIDTH, height);        
        return plane;
    }

    private void moveObjects() {
        for (Mesh mesh : meshs) {
            mesh.move(-PIECE_WIDTH, 0, 0);
        }
    }

    private void cleanUpObjects() {
        for (Iterator<Mesh> iterator = meshs.iterator(); iterator.hasNext();) {
            Mesh next = iterator.next();
            if (next.x < - (width / 2)) {
                iterator.remove();
            }
        }
    }
}
