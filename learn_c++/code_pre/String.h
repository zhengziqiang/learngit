/*==============================================================================
    > File Name: string深拷贝和浅拷贝.h
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月11日 星期日 21时16分18秒
 ==========================================================================*/
#include<string>
#ifndef STRING_H
#define STRING_H
class String{
	public:
		String(char *str="");
		~String();
		void display();
		String(const String &other);
		String & operator =(const String &other);
	private:
		char *str_;
		char *allocandcpy(char *str);
};
#endif
