/*==============================================================================
    > File Name: 类型转换.java
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月09日 星期日 11时05分15秒
 ==========================================================================*/
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
public class HelloWorld {
    public static void main(String[] args) {
        
		double m = 78.5;
		//将基本类型转换为字符串
		String str1 =Double.toString(m);
        
		System.out.println("m 转换为String型后与整数20的求和结果为： "+(str1+20));
		
		String str = "180.20";
	    // 将字符串转换为基本类型
		Double a =Double.parseDouble(str);
	
		System.out.println("str 转换为double型后与整数20的求和结果为： "+(a+20));
	}
}
