package com.example.volumebooster;

import android.media.audiofx.LoudnessEnhancer;
import android.os.Bundle;
import android.widget.SeekBar;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private LoudnessEnhancer enhancer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        enhancer = new LoudnessEnhancer(0);
        enhancer.setEnabled(true);

        SeekBar seekBar = findViewById(R.id.seekBar);

        seekBar.setMax(2000);

        seekBar.setOnSeekBarChangeListener(
            new SeekBar.OnSeekBarChangeListener() {

                @Override
                public void onProgressChanged(
                        SeekBar seekBar,
                        int progress,
                        boolean fromUser
                ) {
                    enhancer.setTargetGain(progress);
                }

                @Override
                public void onStartTrackingTouch(SeekBar seekBar) {}

                @Override
                public void onStopTrackingTouch(SeekBar seekBar) {}
            }
        );
    }

    @Override
    protected void onDestroy() {
        enhancer.release();
        super.onDestroy();
    }
}