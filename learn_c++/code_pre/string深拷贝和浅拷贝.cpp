/*==============================================================================
    > File Name: string深拷贝和浅拷贝.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月11日 星期日 21时22分03秒
 ==========================================================================*/

#include<iostream>
#include "String.h"
#include<string>
#include<string.h>
using namespace std;
char *String::allocandcpy(char *str){
	int len=strlen(str)+1;//包括字符串最后的'\0'
	char *tmp=new char[len];
	memset(tmp,0,len);//将tmp的每个字符都设置为0
	//函数样本
	//void memset(char *ptr,int  value,size_t num)
	//num指定长度
	//value设置要设定的值
	//ptr指定要设置哪些目标
	strncpy(tmp,str,len);
	//将str中的所有内容全都拷贝到tmp中去
	//void strncpy(char *destination,char *source,size_t num)
	//num指定长度,一般为str.length()+1
	return tmp;

}
String::String(const String &other){
	str_=allocandcpy(other.str_);
}
String &String::operator=(const String &other){
	if(this==&other){
		return *this;
	}
	delete []str_;
	str_=allocandcpy(other.str_);
	return *this;
}
String::String(char *str){
	str_=allocandcpy(str);
}
String::~String(){
	delete []str_;
}
void String::display(){
	cout<<str_<<endl;
}
int main(){
	String a1("aaa");
	a1.display();
	String a2=a1;//调用默认的拷贝构造函数但是我对默认的拷贝构造函数进行了重写,现在执行的是一个深层次的一个拷贝.
	String a3;
	a3=a2;//这里调用的就是我写的那个重载的函数而不是那个默认的拷贝构造函数.
	a3.display();
}
