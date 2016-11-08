/*==============================================================================
    > File Name: url_demo.java
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月09日 星期日 15时23分38秒
 ==========================================================================*/
import java.net.*;
import java.io.*;

public class URLDemo
{
   public static void main(String [] args)
   {
      try
      {
         URL url = new URL("http://www.w3cschool.cc/index.html?language=cn#j2se");
         System.out.println("URL is " + url.toString());
         System.out.println("protocol is "
                                    + url.getProtocol());
         System.out.println("authority is "
                                    + url.getAuthority());
         System.out.println("file name is " + url.getFile());
         System.out.println("host is " + url.getHost());
         System.out.println("path is " + url.getPath());
         System.out.println("port is " + url.getPort());
         System.out.println("default port is "
                                   + url.getDefaultPort());
         System.out.println("query is " + url.getQuery());
         System.out.println("ref is " + url.getRef());
      }catch(IOException e)
      {
         e.printStackTrace();
      }
   }
}
