/*************************************************************************
    > File Name: mlp.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年08月06日 星期六 19时42分37秒
 ************************************************************************/

#include<iostream>
#include<math.h>
#include<time.h>
#include<vector>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<math.h>
using namespace std;

//sigmoid内联函数
inline double sigmoid(double x){
	return 1./(1.+exp(-x));
}

//tanh内联函数
inline double tanh(double x){
	return (exp(x)-exp(-x))/(exp(x)+exp(-x);
}

//sigmoid函数导数
double delta_sigmoid(double x){
	return sigmoid(x)*(1-sigmoid(x));
}

//tanh函数导数
double delta_tanh(double x){
	return 1-tanh(x)*tanh(x)
}

//随机数函数
double getrand(){
	return ((double)rand())/(double)RAND_MAX;
}

//每个层的节点
struct Node{
	vector error_patum;
	vector weight_change_this;
	vector weight_change_patum;
	vector error_thisi;
};


//layer类
class layer{
	public:
		int patum;
		int num_node;
		vector <Node> nodes
		double lr;
		double setlr(double m){
			lr=m;
		}
		double getlr(){
			return lr;
		}
		int set_patum(int m){
			patum=m;
		}
		int get_patum(){
			return patum;
		}
		void set_numnode(int x){
			num_node=x;
		}
		int get_numnode(){
			return num_node;
		}
};
class Ilayer:public layer{
	public:
		double weightih[];
		double input_data[];
		int init_weight(double *weightih){//使用数组进行初始化
			int m=get_patum();
			int n=get_numnode();
			for(int i=0;i<m;i++){
				for(int j=0;j<n;j++){
					*(weightih+(i*m+j))=getrand();
				}
			}
			return 0;
		}

		int init_inputdata(double *input_data){
		int n=get_numnode();
		int m=get_patum();
		cout<<"please input the data"<<endl;
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				int data;
				cin>>data;
				*(input_data+(i*m+j))=data;
			}
		}
		}
};
class Hlayer:public layer{
	public:
		double hidden_val[];
		double sigmoid_hiddenval[];
		double tanh_hiddenval[];
		double weighthh[];
		double init_hiddenval(double *hidden_val){//初始化hidden_val
			int m=get_numnode();
			for(int i=0;i<m;i++){
				*(hidden_val+i)=0.0;
			}
			return 0;
		}

		double sigmoid_hiddenval(double *hidden_val){
			int m=get_nunnode();
			for(int i=0;i<m;i++){
				*(hidden_val+i)=sigmoid(*(hidden_val+i));
			}
			return 0;
		}
		double tanh_hiddenval(double *hidden_val){
			int m=get_numnode();
			for(int i=0;i<m;i++){
				*(hidden_val+i)=tanh(*(hidden_val+i));
			}
		}

};

class Olayer:public layer{
	public:
		double  out_put[];
		double desire_output[];
		double init_desireoutput(double *desire_output){
			int m=get_numnode();
			int n=get_patum();
			cout<<"please input the data"<<endl;
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){
					int data;
					cin>>data;
					*(desire_output+(i*n+j))=data;
				}
			}
		return 0;
		}
		double init_output(double *out_put);
}


template<typename Dtype> 
double Ilayer<Dtype>::init_output(vector<Dtype> &out_put){
	int n=get_numnode();
	int m=get_patum();
	for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
					out_put.push_back(0.0);
					out_put[i*n+j]=0.0;
					//*(out_put+(i*n+j))=0.0;
				}
			}
}

// ****** Non-template ****** //
// double Ilayer::init_output(vector<double> &output)  {
//
//
// }


int init_net(){
	int patum;
	cout<<"please input the patum"<<endl;
	cin>>patum;
	double lr;
	cout<<"please input the learning rate"<<endl;
	cin>>lr;


	//input layer
	Ilayer input_layer;
	cout<<"please input the number of the node for input layer"<<endl;
	int input;
	cin>>input;
	input_layer.set_numnode(input);
	input_layer.set_patum(patum);
	input_layer.init_inputdata(input_layer.input_data);
	input_layer.init_weightih(input_layer.weightih);
	input_layer.init_node(input_layer.node);
	input_layer.setlr(lr);
	//hidden layer
	int num_hiddenlayer;
	cout<<"please input the number of hidden layer"<<endl;
	cin>>num_hiddenlayer;
	Hlayer hidden_layer[num_hiddenlayer];
	for(int i=0;i<num_hiddenlayer;i++){
		cout<<"please input the number of the node"<<endl;
		int num;
		cin>>num;
		hidden_layer[i].set_patum(patum);
		hidden_layer[i].set_numnode(num);
		hidden_layer[i].init_node(hidden_layer[i].node);
		cout<<"this is the "<<i+1<<"th hidden layer"<<endl;
		hidden_layer[i].setlr(lr);
	}
	for(int i=0;i<num_hiddenlayer;i++){
		hidden_layer[i].init_hiddenval(hidden_layer[i].hidden_val);
	}
	for(int i=0;i<num_hiddenlayer;i++){
		init_weighthh(hidden_layer[i].num_node,hidden_layer[i+1].num_node,hidden_layer.weighthh);
	}


	//output layer
	Olayer output_layer;
	int out;
	cout<<"please input the number of the node for output layer"<<endl;
	cin>>out;
	output_layer.set_numnode(out);
	output_layer.set_patum(patum);
	output_layer.init_output(output_layer.out_put);
	output_layer.set_desireoutput(output_layer.desire_output);
	output_layer.init_node(output_layer.node);
	return patum;
}

int calnet(){
	for(int 
}

int init_weighthh(int m,int n,double *weight){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
		*(weight+(i*m+j))=getrand();
		}
	}
	return 0;
}

int weight_change(double *
int main(){
	int patum_layer=init_net();
		
}


