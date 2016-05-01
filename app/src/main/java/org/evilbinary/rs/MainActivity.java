package org.evilbinary.rs;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity implements View.OnClickListener {
    private String TAG=getClass().getSimpleName();

    private EditText mEditText;
    private TextView mTextView;
    private Button mButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mEditText= (EditText) findViewById(R.id.editText);
        mTextView= (TextView) findViewById(R.id.textView);
        mButton= (Button) findViewById(R.id.runButton);
        mButton.setOnClickListener(this);

    }

    @Override
    public void onClick(View v) {
        Rs rs=new Rs();
        rs.init(this.getFilesDir().getPath(), "");
        String exp=mEditText.getText().toString();
        String ret=rs.eval(exp);
        mTextView.setText(ret);
        Log.d(TAG, ret);
    }
}
