/*==============================================================================
    > File Name: FileDemo.java
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月09日 星期日 23时26分11秒
 ==========================================================================*/
import java.io.File;
import java.io.IOException;

public class FileDemo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// 了解构造函数的情况  查帮助
		File file = new File("/home/zzq/imprave/java_test/test");
		//System.out.println(file.exists());
		if(!file.exists())
			file.mkdir(); //file.mkdirs()
		else
			file.delete();
		//是否是一个目录  如果是目录返回true,如果不是目录or目录不存在返回的是false
		System.out.println(file.isDirectory());
		//是否是一个文件
		System.out.println(file.isFile());
		
		//File file2 = new File("e:\\javaio\\日记1.txt");
		File file2 = new File("/home/zzq/imprave/java_test/hehe");
		if(!file2.exists())
			try {
				file2.createNewFile();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		else 
			file2.delete();
         //常用的File对象的API
		System.out.println(file);//file.toString()的内容
		System.out.println(file.getAbsolutePath());
		System.out.println(file.getName());
		System.out.println(file2.getName());
		System.out.println(file.getParent());
		System.out.println(file2.getParent());
		System.out.println(file.getParentFile().getAbsolutePath());
	}

}
