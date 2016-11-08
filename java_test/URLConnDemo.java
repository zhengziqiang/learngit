/*==============================================================================
    > File Name: URLConnDemo.java
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月09日 星期日 15时48分34秒
 ==========================================================================*/
import java.net.*;
import java.io.*;
public class URLConnDemo
{
	private static final String CHARSET="GBK";
   public static void main(String [] args)
   {
      try
      {
         URL url = new URL("http://www.w3cschool.cc");
         URLConnection urlConnection = url.openConnection();
         HttpURLConnection connection = null;
         if(urlConnection instanceof HttpURLConnection)
         {
            connection = (HttpURLConnection) urlConnection;
         }
         else
         {
            System.out.println("Please enter an HTTP URL.");
            return;
         }
		 connection.setRequestProperty("Charset", CHARSET); // 设置编码  
         BufferedReader in = new BufferedReader(
         new InputStreamReader(connection.getInputStream()));
         String urlString = "";
         String current;
         while((current = in.readLine()) != null)
         {
            urlString += current;
         }
         System.out.println(urlString);
      }catch(IOException e)
      {
         e.printStackTrace();
      }
   }
}
