/*==============================================================================
    > File Name: list_test.java
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月01日 星期六 11时27分04秒
 ==========================================================================*/
package com.imooc.collection
import java.util.ArrayList
import java.util.Arrays
import java.util.Iterator
import java.util.List

public class list_test{
	public List courses_to_select;
	public list_test(){
		this->courses_to_select=new ArrayList();
	}
	public void test_add(){
		Course cr1=new Course("1","数据结构");
		courses_to_select.add(cr1);
		Course tmp(Course)courses_to_select.get(0);
		System.out.println("添加了课程:"+temp.id+":"+temp.name);

		Course cr2=new Course ("2","C语言");
		courses_to_select.add(1,cr2);

	}
}
