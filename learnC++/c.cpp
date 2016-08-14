/*************************************************************************
    > File Name: c.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年08月06日 星期六 10时15分28秒
 ************************************************************************/

#include<iostream>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#define num_input 3//输入层个数
#define num_pattern 4//相当于多个通道图
#define num_hidden 5//隐藏层个数
#define epoch 500//计算的次数
#define lr_ih 0.5//学习率
#define lr_ho 0.05
using namespace std;
int initweights();//初始化权值
int initdata();//初始化数据
double getrand();//获取随机数
int calnet();//计算残差
int weightchangeih();//改变权值,input_hidden
int weightchangeho();//改变权值,hidden_output
int errorcal();//计算error
int display();//显示结果
double hidden_val[num_hidden];//定义hiddenval
double weights_ih[num_input][num_hidden];
double weights_ho[num_hidden];
double train_inputs[num_pattern][num_input];
double train_outputs[num_pattern];
int patum=0;
double error_this=0.0;//在每一次迭代中的error
double rms_error=0.0;//均方根误差
double out_put=0.0;//网络的实际输出值

//初始化完毕
double getrand(){
	return ((double)rand())/(double)RAND_MAX;
}


int initweights(){
	for(int i=0;i<num_hidden;i++){
		weights_ho[i]=(getrand()-0.5)/2;
		for(int j=0;j<num_input;j++){
			weights_ih[j][i]=(getrand()-0.5)/5;
		}
	}
	return 0;
}

int initdata(){
	cout<<"初始化数据"<<endl;
	train_inputs[0][0]= 1;
	train_inputs[0][1]= -1;
	train_inputs[0][2]= 1;   //bias  偏置项全为1
	train_outputs[0]= 1;     //解决异或问题,不相同就为1


	train_inputs[1][0]= 1;
	train_inputs[1][1]= 1;
	train_inputs[1][2]= 1;
	train_outputs[1]= -1;
	

	train_inputs[2][0]= -1;
	train_inputs[2][1]= -1;
	train_inputs[2][2]= 1;
	train_outputs[2]= -1;

	train_inputs[3][0]= -1;
	train_inputs[3][1]= 1;
	train_inputs[3][2]= 1;
	train_outputs[3]= 1;
	return 0;
}

int calnet(){
	for(int i=0;i<num_hidden;i++){
		hidden_val[i]=0.0;
		for(int j=0;j<num_input;j++){
			hidden_val[i]=hidden_val[i]+weights_ih[j][i]*train_inputs[patum][j];//这里的patum被局部变量覆盖
		}
		hidden_val[i]=tanh(hidden_val[i]);//激活函数
	}
	out_put=0.0;
	for(int i=0;i<num_hidden;i++){
		out_put = out_put+hidden_val[i]*weights_ho[i];
	}
	error_this=out_put-train_outputs[patum];
	return 0;
}

int weightchangeih(){
	for(int i=0;i<num_hidden;i++){
		for(int j=0;j<num_input;j++){
			double x=1-(hidden_val[i]*hidden_val[i]);//tanh的导函数
			x=x*error_this*weights_ho[i]*lr_ih;//这上面的两步每次循环都会做,都会初始化为同样的值
			x=x*train_inputs[patum][j];//这一步才根据input层的不同才有所区别
			double weight_change =x;
			weights_ih[j][i]=weights_ih[j][i]-weight_change;//更新权重
		}
	}
	return 0;
}

int weightchangeho(){
	for(int i=0;i<num_hidden;i++){
		double weight_change=error_this*lr_ho*hidden_val[i];
		weights_ho[i]=weights_ho[i]-weight_change;
		if(weights_ho[i]>5)  weights_ho[i]=5;
		else if(weights_ho[i]<-5) weights_ho[i]=-5;
	}
	return 0;
}
int display(){
	for(int i=0;i<num_pattern;i++){
		patum=i;//局部变量覆盖全局变量
		calnet();//调用计算
		cout<<"patum="<<patum+1<<endl;
		cout<<"实际值是"<<train_outputs[patum]<<endl;
		cout<<"网络计算值是"<<out_put<<endl;
	}
	return 0;
}
int errorcal(){
	rms_error=0.0;
	for(int i=0;i<num_pattern;i++){
		patum=i;
		calnet();
		rms_error+=(error_this*error_this);//将所有的error相加
	}
	rms_error=rms_error/num_pattern;
	rms_error=sqrt(rms_error);
	return 0;
}
int main(){
	srand(time(NULL));//使用系统时间产生的随机数
	initweights();
	initdata();
	for(int i=0;i<epoch;i++){
		for(int j=0;j<num_pattern;j++){
			patum = rand()%num_pattern;//随机选取一个patum
			calnet();
			weightchangeho();
			weightchangeih();
		}
		errorcal();
		cout<<"epoch="<<i<<endl;
		cout<<"rms_error="<<rms_error<<endl;
	}
	display();
	return 0;
}
