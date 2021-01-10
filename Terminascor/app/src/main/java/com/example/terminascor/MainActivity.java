package com.example.terminascor;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;




public class MainActivity extends AppCompatActivity {
    //EditText editText1, editText2;

    Button getInfo;
    DatabaseReference rootRef, demoRef;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        getInfo = findViewById(R.id.btnGet);

        //Database pointing
        rootRef = FirebaseDatabase.getInstance().getReference();

        demoRef = rootRef.child("Location");


        Button getInfo = findViewById(R.id.btnGet);
        final TextView latitude = findViewById(R.id.tValue1);
        //final TextView longitude = findViewById(R.id.tValue2);

        getInfo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
            demoRef.addListenerForSingleValueEvent(new ValueEventListener() {
                @Override
                public void onDataChange(@NonNull DataSnapshot dataSnapshot) {

                    String value1 = dataSnapshot.getValue(String.class);
                    latitude.setText(value1);

                    //String value2 = dataSnapshot.getValue(String.class);
                    //longitude.setText(value2);
                }

                @Override
                public void onCancelled(@NonNull DatabaseError error) {
                    Toast.makeText(MainActivity.this, "Error fetching data", Toast.LENGTH_LONG).show();
                }
            });
            }
        });
    }
}