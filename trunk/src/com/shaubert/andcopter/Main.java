package com.shaubert.andcopter;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class Main extends Activity {
    
    private Button newGameButton;
    private Button scoresButton;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        findViews();
        setHandlers();
    }

    private void findViews() {
        newGameButton = (Button)findViewById(R.id.button_new_game);
        scoresButton = (Button)findViewById(R.id.button_score);
    }
    
    private void setHandlers() {
        newGameButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                startActivity(new Intent(Main.this, GameActivity.class));
            }
        });
    }
}