package com.shaubert.andcopter;

import java.util.Iterator;
import java.util.Random;

import javax.microedition.khronos.opengles.GL10;

public class Rocks extends Group {

    private static final float PIECE_HEIGHT_STEP = 0.05f;
    private static final float PIECE_MIN_HEIGHT = PIECE_HEIGHT_STEP;
    private static final float PIECE_MAX_HEIGHT = PIECE_HEIGHT_STEP * 8;
    private static final float PIECE_WIDTH = 0.07f;
    private static final int STEPS_IN_WIDTH = 5; 
    private static final float STEP = PIECE_WIDTH / STEPS_IN_WIDTH;

    private Random random = new Random();
    private float lastTopHeight;
    private float lastBottomHeight;
    
    private final float pieceMinHeight;
    private final float pieceMaxHeight;
    private final float pieceWidth;
    private final float step;

    private boolean paused;
    
    private float width;
    private float height;
    private int distance;
    
    public Rocks(float screenWidth, float screenHeight) {
        this.width = screenWidth;
        this.height = screenHeight;
        this.pieceMinHeight = screenHeight/2 * PIECE_MIN_HEIGHT;
        this.pieceMaxHeight = screenHeight/2 * PIECE_MAX_HEIGHT;
        this.pieceWidth = screenWidth/2 * PIECE_WIDTH;
        this.step = screenWidth/2 * STEP;
        
        createNewSurfacePart(true);
        createNewSurfacePart(false);
    }
    
    public int getDistance() {
        return distance;
    }
    
    public void setup(GL10 gl) {
    }
    
    @Override
    public void draw(GL10 gl) {
        if (!paused) {
            if (distance % STEPS_IN_WIDTH == 0) {
//                createNewSurfacePart(true);
//                createNewSurfacePart(false);
//                cleanUpObjects();        
            }
            moveObjects();
        }
        super.draw(gl);
    }
    
    public void pause() {
        paused = true;
    }
    
    public void resume() {
        paused = false;
    }
    
    private void createNewSurfacePart(boolean top) {
        float lastHeight = top ? lastTopHeight : lastBottomHeight;
        float height = lastHeight + ((random.nextInt(3) - 1) * PIECE_HEIGHT_STEP) * this.height/2;
        if (height < pieceMinHeight) {
            height = pieceMinHeight;
        } else if (height > pieceMaxHeight) {
            height = pieceMaxHeight;
        }
        
        final Mesh result;
        
        if (height > lastHeight) {
            result = new Quad(1, 
                   -pieceWidth/2, top ? (height/2) : (lastHeight - height/2), 0,
                   -pieceWidth/2, top ? (height/2 - lastHeight) : (-height/2) , 0,
                    pieceWidth/2, -height/2, 0,
                    pieceWidth/2, height/2, 0);
            result.translate(width / 2 + pieceWidth, (top ? 1 : -1) * ((this.height / 2) - (height / 2)), 0);
        } else {
            result = new Quad(1, 
                    -pieceWidth/2, lastHeight/2, 0,
                    -pieceWidth/2, -lastHeight/2, 0,
                     pieceWidth/2, top ? (lastHeight/2 - height) : (-lastHeight/2), 0,
                     pieceWidth/2, top ? (lastHeight/2) : (height - lastHeight/2), 0);
            result.translate(width / 2 + pieceWidth, (top ? 1 : -1) * ((this.height / 2) - (lastHeight / 2)), 0);
        }
        
        if (top) {
            lastTopHeight = height;
        } else {
            lastBottomHeight = height;
        }
        add(result);
    }

    private void moveObjects() {
        for (Mesh mesh : meshs) {
            mesh.move(-step, 0, 0);
        }
        distance++;
    }

    private void cleanUpObjects() {
        for (Iterator<Mesh> iterator = meshs.iterator(); iterator.hasNext();) {
            Mesh next = iterator.next();
            if (next.getRight() < -(width / 2)) {
                iterator.remove();
            }
        }
    }
    
    @Override
    public boolean has2DCollision(Mesh mesh) {
        for (Mesh rock : meshs) {
            if (rock.has2DCollision(mesh)) {
                return true;
            }
        }
        return false;
    }
    
}
