package org.evilbinary.rs;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Rs rs=new Rs();
        rs.init(this.getFilesDir().getPath(), "");
        String ret=rs.eval("(display \"Hello, RScheme!\\n\")");
//        ret=rs.eval("(+ 1 2 3 )");
        ret=rs.eval("(format #t \"a\")");

        System.out.println("ret="+ret);


    }
}
