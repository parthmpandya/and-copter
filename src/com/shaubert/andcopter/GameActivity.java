package com.shaubert.andcopter;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

public class GameActivity extends Activity {

    private GLSurfaceView glSurface;
    
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
        glSurface.setRenderer(new GameRenderer(this));
    }
}
