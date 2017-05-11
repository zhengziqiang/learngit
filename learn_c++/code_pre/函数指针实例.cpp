/*************************************************************************
    > File Name: 函数指针实例.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2016年07月13日 星期三 21时00分35秒
 ************************************************************************/

#include <iostream>
using namespace std;

class test
{
public:
    test()
    {
        cout<<"constructor"<<endl;
    }
    int fun1(int a, char c)
    {
        cout<<"this is fun1 call:"<<a<<" "<<c<<endl;
        return a;
    }
    void fun2(double d)const
    {
        cout<<"this is fun2 call:"<<d<<endl;
    }
    static double fun3(char buf[])
    {
        cout<<"this is fun3 call:"<<buf<<endl;
        return 3.14;
    }
};

int main()
{
    // 类的静态成员函数指针和c的指针的用法相同
    double (*pstatic)(char buf[]) = NULL;//不需要加类名
    pstatic = test::fun3; //可以不加取地址符号，静态成员函数可以不加取址符号
    pstatic("myclaa");
    pstatic = &test::fun3;
    (*pstatic)("xyz");

    //普通成员函数
    int (test::*pfun)(int, char) = NULL; //一定要加类名
    pfun = &test::fun1; //一定要加取地址符号
    test mytest;
    (mytest.*pfun)(1, 'a'); //调用是一定要加类的对象名和*符号

    //const 函数（基本普通成员函数相同）
    void (test::*pconst)(double)const = NULL; //一定要加const
    pconst = &test::fun2;
    test mytest2;
    (mytest2.*pconst)(3.33);

//    //构造函数或者析构函数的指针，貌似不可以，不知道c++标准有没有规定不能有指向这两者的函数指针
//    (test::*pcon)() = NULL;
//    pcon = &test.test;
//    test mytest3;
//    (mytest3.*pcon)();

    return 0;
}
