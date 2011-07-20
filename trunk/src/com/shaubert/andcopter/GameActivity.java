package com.shaubert.andcopter;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;

public class GameActivity extends Activity {

    private GLSurfaceView glSurface;
    private NativeRenderer gameRenderer;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.game);

        findViews();
        setup();
    }

    private void findViews() {
        glSurface = (GLSurfaceView)findViewById(R.id.game_surface);
    }
    
    private void setup() {
        gameRenderer = new NativeRenderer();
        glSurface.setRenderer(gameRenderer);
//        glSurface.setOnKeyListener(gameRenderer);
    }
    
    @Override
    public boolean onTrackballEvent(MotionEvent event) {
        return gameRenderer.onTrackballEvent(event) || super.onTrackballEvent(event);
    }
    
    @Override
    protected void onPause() {
        if (isFinishing()) {
            gameRenderer.release();
        }
        super.onPause();
    }
}