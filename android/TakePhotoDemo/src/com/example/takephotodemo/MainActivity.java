package com.example.takephotodemo;
//import com.example.postdemo.*;
//import java.io.DataOutputStream;  
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.InputStream;

import com.example.picupload.MultipartEntity;


 
  
import java.io.IOException;  
//import java.util.HashMap;
//import java.util.Map;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;


import android.media.ExifInterface;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
//import android.os.Handler;
//import android.os.Message;
import android.provider.MediaStore;
import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.PopupWindow;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener {
	private static ImageView mimageViewPhotoShow;
	private PopupWindow mPopupWindow;
	private View mpopview;
	private Bitmap photo;
	private File mPhotoFile;
	private int CAMERA_RESULT = 100;
	private int RESULT_LOAD_IMAGE = 200;
	private String saveDir = Environment.getExternalStorageDirectory()
			.getPath() + "/temp_image";
	private static final String TAG = "upload";
	private String filepath;
	private static String filename;
	public static String responseImageUrl = "";//回复图片的地址
	
	
//	private static Handler myHandler = new Handler() {  
//        public void handleMessage(Message msg) {   
//             switch (msg.what) {   
//                  case 1:   
//                	  mimageViewPhotoShow.setImageURI(Uri.parse(responseImageUrl));  
//                       break;   
//             }   
//             super.handleMessage(msg);   
//        }   
//   };

   private void sendPhoto(Bitmap bitmap,String urll) throws Exception {
		new UploadTask().execute(bitmap);
		urll=UploadTask.url;
	}
   //added by zzq
   private void setPic() {
		// Get the dimensions of the View
	    int targetW = mimageViewPhotoShow.getWidth();
	    int targetH = mimageViewPhotoShow.getHeight();

	    // Get the dimensions of the bitmap
	    BitmapFactory.Options bmOptions = new BitmapFactory.Options();
	    bmOptions.inJustDecodeBounds = true;
	    BitmapFactory.decodeFile(filepath, bmOptions);
	    int photoW = bmOptions.outWidth;
	    int photoH = bmOptions.outHeight;

	    // Determine how much to scale down the image
	    int scaleFactor = Math.min(photoW/targetW, photoH/targetH);

	    // Decode the image file into a Bitmap sized to fill the View
	    bmOptions.inJustDecodeBounds = false;
	    bmOptions.inSampleSize = scaleFactor << 1;
	    bmOptions.inPurgeable = true;

	    Bitmap bitmap = BitmapFactory.decodeFile(filepath, bmOptions);
	    
	    Matrix mtx = new Matrix();
	    mtx.postRotate(0);
	    // Rotating Bitmap
	 
	    Bitmap rotatedBMP = Bitmap.createBitmap(bitmap, 0, 0, bitmap.getWidth(), bitmap.getHeight(), mtx, true);

	    if (rotatedBMP != bitmap)
	    	bitmap.recycle();
	    
	    mimageViewPhotoShow.setImageBitmap(rotatedBMP);
	    
	    try {
			sendPhoto(rotatedBMP,responseImageUrl);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
   
   
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		InitUI();
	}

	private void InitUI() {
		View buttonChoosePhoto = (Button) findViewById(R.id.buttonChoosePhoto);
		if (buttonChoosePhoto != null) {
			buttonChoosePhoto.setOnClickListener(this);
		}
		View buttonPost = (Button) findViewById(R.id.buttonPost);
		if (buttonPost != null) {
			buttonPost.setOnClickListener(this);
		}
		View buttonresult = (Button) findViewById(R.id.buttonresult);
		if (buttonresult != null) {
			buttonresult.setOnClickListener(this);
		}

		mimageViewPhotoShow = (ImageView) findViewById(R.id.imageViewPhotoShow);
		
	}

	@Override
	public void onClick(View arg0) {
		if(arg0.getId()==R.id.buttonChoosePhoto)
		{
		
			LayoutInflater inflater = LayoutInflater.from(this);
			mpopview = inflater.inflate(R.layout.layout_login_choose_photo,
					null);

			mPopupWindow = new PopupWindow(mpopview, 300, 400, true);
			mPopupWindow.setBackgroundDrawable(getResources().getDrawable(
					R.drawable.tekephoto_dialog_background));

			mPopupWindow.showAtLocation(mimageViewPhotoShow, Gravity.CENTER, 0,
					0);
			Button mbuttonTakePhoto = (Button) mpopview
					.findViewById(R.id.button_take_photo);
			Button mbuttonChoicePhoto = (Button) mpopview
					.findViewById(R.id.button_choice_photo);
			Button mbuttonChoicecannce = (Button) mpopview
					.findViewById(R.id.button_choice_cancer);

			// 锟斤拷锟斤拷洗锟�
			mbuttonChoicePhoto.setOnClickListener(new OnClickListener() {
				@Override
				public void onClick(View v) {
					mPopupWindow.dismiss();
					Intent i = new Intent(
							Intent.ACTION_PICK,
							android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
					startActivityForResult(i, RESULT_LOAD_IMAGE);
				}
			});

			File savePath = new File(saveDir);
			if (!savePath.exists()) {
				savePath.mkdirs();
			}


			mbuttonTakePhoto.setOnClickListener(new OnClickListener() {
				@Override
				public void onClick(View v) {
					mPopupWindow.dismiss();
					destoryImage();
					String state = Environment.getExternalStorageState();
					if (state.equals(Environment.MEDIA_MOUNTED)) {
						
						filepath=saveDir + System.currentTimeMillis() +".png";
						mPhotoFile = new File(filepath);
						filename=mPhotoFile.getName();
						mPhotoFile.delete();
						if (!mPhotoFile.exists()) {
							try {
								mPhotoFile.createNewFile();
							} catch (IOException e) {
								e.printStackTrace();
								Toast.makeText(getApplication(), "锟斤拷片锟斤拷锟斤拷失锟斤拷!",
										Toast.LENGTH_LONG).show();
								return;
							}
						}
						Intent intent = new Intent(
								"android.media.action.IMAGE_CAPTURE");
						intent.putExtra(MediaStore.EXTRA_OUTPUT,
								Uri.fromFile(mPhotoFile));
						startActivityForResult(intent, CAMERA_RESULT);
					} else {
						Toast.makeText(getApplication(), "sdcard锟斤拷效锟斤拷没锟叫诧拷锟斤拷!",
								Toast.LENGTH_SHORT).show();
					}
				}
			});

			mbuttonChoicecannce.setOnClickListener(new OnClickListener() {
				@Override
				public void onClick(View v) {
					// TODO Auto-generated method stub
					mPopupWindow.dismiss();
				}
			});
		
			
		}
		if (arg0.getId()==R.id.buttonPost)
//		{
//			UploadUtil up=new UploadUtil();
//			
//			Map<String, String> paramMap = new HashMap<String, String>();
//			paramMap.put("keyName", "value");
//			
//			up.uploadFile(saveDir, "imageKey", URL, paramMap, myHandler);
//		}	
		{
			setPic();
		}
		if(arg0.getId()==R.id.buttonresult){
			mimageViewPhotoShow.setImageURI(Uri.parse(responseImageUrl)); 
		}
	}


	public static class UploadTask extends AsyncTask<Bitmap, Void, Void> {
		public static String url;
		protected Void doInBackground(Bitmap... bitmaps) {
			if (bitmaps[0] == null)
				return null;
//			setProgress(0);
			
			Bitmap bitmap = bitmaps[0];
			ByteArrayOutputStream stream = new ByteArrayOutputStream();
			bitmap.compress(Bitmap.CompressFormat.PNG, 100, stream); // convert Bitmap to ByteArrayOutputStream
			//将图片文件进行压缩成png文件
			InputStream in = new ByteArrayInputStream(stream.toByteArray()); // convert ByteArrayOutputStream to ByteArrayInputStream

			DefaultHttpClient httpclient = new DefaultHttpClient();
			try {
				HttpPost httppost = new HttpPost(
						"http://192.168.31.101:8080/hackathon/api/upload"); // server

				MultipartEntity reqEntity = new MultipartEntity();//实例化
				reqEntity.addPart("myFile",
						filename, in);
				httppost.setEntity(reqEntity);

				Log.i(TAG, "request " + httppost.getRequestLine());
				HttpResponse response = null;
				try {
					response = httpclient.execute(httppost);
				} catch (ClientProtocolException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				try {
					if (response != null)
					{
						
						Log.i(TAG, "response " + response.getStatusLine().toString());
						url=response.getStatusLine().toString();
						
						}
				} finally {

				}
			} finally {

			}

			if (in != null) {
				try {
					in.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}

			if (stream != null) {
				try {
					stream.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}

			return null;
		}
		
		@Override
		protected void onProgressUpdate(Void... values) {
			// TODO Auto-generated method stub
			super.onProgressUpdate(values);
		}
		
		@Override
		protected void onPostExecute(Void result) {
			// TODO Auto-generated method stub
			super.onPostExecute(result);
//			Toast.makeText(MainActivity.this, "successfully uploaed", Toast.LENGTH_LONG).show();
		}
	}

	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (requestCode == CAMERA_RESULT && resultCode == RESULT_OK) {
			if (mPhotoFile != null && mPhotoFile.exists()) {
				BitmapFactory.Options bitmapOptions = new BitmapFactory.Options();
				bitmapOptions.inSampleSize = 8;
				int degree = readPictureDegree(mPhotoFile.getAbsolutePath());
				Bitmap bitmap = BitmapFactory.decodeFile(mPhotoFile.getPath(),
						bitmapOptions);
				bitmap = rotaingImageView(degree, bitmap);
				mimageViewPhotoShow.setImageBitmap(bitmap);
			}
		}
		if (requestCode == RESULT_LOAD_IMAGE && resultCode == RESULT_OK
				&& null != data) {
			Uri selectedImage = data.getData();
			String[] filePathColumn = { MediaStore.Images.Media.DATA };

			Cursor cursor = getContentResolver().query(selectedImage,
					filePathColumn, null, null, null);
			cursor.moveToFirst();

			int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
			String picturePath = cursor.getString(columnIndex);
			cursor.close();

			mimageViewPhotoShow.setImageBitmap(BitmapFactory
					.decodeFile(picturePath));
		}
	}

	private static int readPictureDegree(String path) {
		int degree = 0;
		try {
			ExifInterface exifInterface = new ExifInterface(path);
			int orientation = exifInterface.getAttributeInt(
					ExifInterface.TAG_ORIENTATION,
					ExifInterface.ORIENTATION_NORMAL);
			switch (orientation) {
			case ExifInterface.ORIENTATION_ROTATE_90:
				degree = 90;
				break;
			case ExifInterface.ORIENTATION_ROTATE_180:
				degree = 180;
				break;
			case ExifInterface.ORIENTATION_ROTATE_270:
				degree = 270;
				break;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		return degree;
	}

	private static Bitmap rotaingImageView(int angle, Bitmap bitmap) {
		// 锟斤拷转图片 锟斤拷锟斤拷
		Matrix matrix = new Matrix();
		matrix.postRotate(angle);
		System.out.println("angle2=" + angle);
		// 锟斤拷锟斤拷锟铰碉拷图片
		Bitmap resizedBitmap = Bitmap.createBitmap(bitmap, 0, 0,
				bitmap.getWidth(), bitmap.getHeight(), matrix, true);
		return resizedBitmap;
	}

	
	@Override
	protected void onDestroy() {
		destoryImage();
		super.onDestroy();
	}

	private void destoryImage() {
		if (photo != null) {
			photo.recycle();
			photo = null;
		}
	}
}
