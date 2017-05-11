#include <stdio.h>
#include <stdlib.h>

int fun1()
{
    printf("this is fun1 call\n");
    return 1;
}

void fun2(int k, char c)
{
    printf("this is fun2 call:%d %c\n", k, c);
}

int main()
{
    int (*pfun1)() = NULL;//定义一个新的函数指针指向NULL
    void (*pfun2)(int, char) = NULL;//定义一个新的指针里面有两个参数分别是int和char型的
    int a,b;
    pfun1 = fun1; //第一种赋值方法，并且指向函数
    a = pfun1();  //第一种调用方法（推荐）只要有返回值且返回值为整数都能用一个整数值去接受
    printf("整数=%d\n",a);//打印返回的整数值
    b = (*pfun1)();//第二种调用方法(*pfun1)=fun,在这里调用的还是函数1,返回值为1被b接收
    printf("第二个整数=%d\n",b);
    pfun2 = &fun2;//第二种赋值方法（推荐，因为和其他数据指针赋值方法一致）取址赋值相当于引用
    pfun2(1,'a');
    (*pfun2)(2,'b');//函数的引用后调用时就要将它加上指针，具体格式是(*pfun2)
    return 0;
}
