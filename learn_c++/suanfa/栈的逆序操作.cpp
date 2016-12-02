/*==============================================================================
    > File Name: 栈的逆序操作.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月08日 星期二 20时04分22秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
class ReverseStack {
public:
     vector<int> reverseStackRecursively(vector<int> &stack, int top) {
        if(top==1)//只有一个数的时候直接返回
            return stack;
        int temp;
        temp=stack.back();
        stack.pop_back();//最上面的数出栈
        stack=reverseStackRecursively(stack,top-1);//递归调用
        stack=insertToBottom(stack,temp);  //用一个函数实现将一个数插入到最底层
        return stack;
    }
    vector<int> insertToBottom(vector<int> stack,int num)//将一个数插入到栈的最底层的函数
    {
        if(stack.size()==0)//栈空
         {
            stack.push_back(num);
            return stack;
        }
        int top=stack.back();
        stack.pop_back();//将最上面的数出栈保存
        stack=insertToBottom(stack,num);//把数插入到最底层
        stack.push_back(top);//再把原先的最上面的数入栈
		return stack;
        
    }
};
int main(){
	vector <int> exa;
	exa.push_back(1);
	exa.push_back(2);
	exa.push_back(3);
	exa.push_back(4);
	exa.push_back(5);
	ReverseStack stack;
	stack.reverseStackRecursively(exa,5);
	for(int i=0;i<5;i++){
		cout<<exa[i]<<endl;
	}
	return 0;
}
