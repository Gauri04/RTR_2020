package com.example.myhelloworld;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatTextView;
import android.view.Gravity;
import android.graphics.Color;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

	
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
		
		AppCompatTextView myTextView = new AppCompatTextView(this);
		
		getWindow().getDecorView().setBackgroundColor(Color.rgb(0, 0, 0));
        //setContentView(R.layout.activity_main);
		myTextView.setText("Hello World !!");
		myTextView.setTextSize(32);
		myTextView.setTextColor(Color.rgb(0, 255, 0));
		myTextView.setGravity(Gravity.CENTER);
		myTextView.setBackgroundColor(Color.rgb(0, 0, 0));
		setContentView(myTextView);
    }
}