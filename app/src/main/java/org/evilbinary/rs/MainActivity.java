package org.evilbinary.rs;
/**
 * 作者:evilbinary on 3/17/16.
 * 邮箱:rootdebug@163.com
 */
import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import org.evilbinary.util.ZipUtil;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.zip.ZipException;

public class MainActivity extends Activity implements View.OnClickListener {
    private String TAG = getClass().getSimpleName();

    private EditText mEditText;
    private TextView mTextView;
    private Button mButton;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mEditText = (EditText) findViewById(R.id.editText);
        mTextView = (TextView) findViewById(R.id.textView);
        mButton = (Button) findViewById(R.id.runButton);
        mButton.setOnClickListener(this);



        extractZipFile(this, "sys.img",this.getFilesDir().getPath());

    }


    private  void run(){
        new Handler().post(new Runnable() {
            @Override
            public void run() {
                Rs rs = new Rs();
                rs.init(getFilesDir().getPath(), "");
                String exp = mEditText.getText().toString();
                String ret = rs.eval(exp);
                mTextView.setText(ret);
                //Log.d(TAG, ret);
            }
        });
    }

    @Override
    public void onClick(View v) {
        run();
    }



    private void extractZipFile(Context context, String name,String filesDir) {
        String zipFileDir = filesDir + "/" + name;
        File file = new File(zipFileDir);
        if (!file.exists()) {
            try {
                String src = name + ".zip";
                InputStream is = context.getAssets().open(src);
                extract(context, src, filesDir);
            } catch (Exception e) {
                Log.d(TAG, e.getMessage());
            }
        } else {
            Log.d(TAG, "Dir " + zipFileDir + " exist will not extract.");
        }
    }

    private void extract(Context context, String src, String des) {

        try {
            Log.d(TAG, "Begin extract " + src + " to " + des + ".");
            InputStream is = context.getAssets().open(src);
            ZipUtil.upZipFile(is, des);
            Log.d(TAG, "Extract " + src + " to " + des + " finished.");

        } catch (ZipException e) {
            Log.d(TAG, e.getMessage());
        } catch (IOException e) {
            Log.d(TAG, e.getMessage());
        } catch (Exception e) {
            Log.d(TAG, e.getMessage());
        } catch (Error e) {
            Log.d(TAG, e.getMessage());
        } catch (Throwable e) {
            Log.d(TAG, e.getMessage());
        }
    }

}
