
/*************************************************************************
    > File Name: one.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年08月11日 星期四 14时23分01秒
 ************************************************************************/
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<fstream>
#include<time.h>
#include<string.h>
#include<vector>
using namespace std;
//double getrand(){
//	double x=((double)rand())/(double)RAND_MAX;
//	return x;
//}
//生成随机数函数
//
double getrand(){
    static double V1, V2, S;
    static int phase = 0;
    double X;
    if (phase == 0) {
        do {
            double U1 = (double) rand() / RAND_MAX;
            double U2 = (double) rand() / RAND_MAX;
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while (S >= 1 || S == 0);
        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);
    phase = 1 - phase;
    double x=X*0.1;
    return x;
}

//sigmoid函数
inline double sigmoid(double x){
    return 1.0/(1.0+exp(-x));
}
//sigmoid的导函数
inline double fsigmoid(double x){
    return x*(1-x);
}
//主类,layer
class layer{
    public:
        int num_node;
        int patum;
        vector <double> weights;
        vector <double> delta;
        vector <double> delta_weight;
        vector <double> delta_weightall;
        int set_numnode(int m){
            num_node=m;
            return 0;
        }
        int get_numnode(){
            return num_node;
        }
        int set_patum(int m){
            patum=m;
            return 0;
        }
        int get_patum(){
            return patum;
        }
        int init_weight(int first,int end,vector <double> &weights);
        int init_delta(int num_node,vector <double> &delta);
        int init_deltaweight(int first,int end,vector <double> &delta_weight);
        int init_deltaweightall(int end,int first,vector <double> &delta_weightall);
        int zero_deltaweight(int end,int first,vector <double> &delta_weight);
        int zero_deltaweightall(int end,int first,vector <double> &delta_weightall);
};
int layer::zero_deltaweight(int end,int first,vector <double> &delta_weight){
    for(int i=0;i<end;i++){
        for(int j=0;j<first;j++){
            delta_weight[i*end+j]=0.0;
        }
    }
    return 0;
}
int layer::zero_deltaweightall(int end,int first,vector <double> &delta_weightall){
    for(int i=0;i<end;i++){
        for(int j=0;j<first;j++){
            delta_weightall[i*end+j]=0.0;
        }
    }
    return 0;
}
int layer::init_delta(int num_node,vector <double> &delta){
        for(int j=0;j<num_node;j++){
            delta.push_back(0.0);
        }
        return 0;
}
int layer::init_deltaweight(int first,    int end,   vector <double> &delta_weight){
    for(int i=0;i<end;i++){
        for(int j=0;j<first;j++){
            delta_weight.push_back(0.0);
        }
    }
    return 0;
}
int layer::init_deltaweightall(int end,int first,vector <double> &delta_weightall){
    for(int i=0;i<end;i++){
        for(int j=0;j<first;j++){
            delta_weightall.push_back(0.0);
        }
    }
    return 0;
}
int layer::init_weight(int first,int end,vector <double> &weights){
    for(int i=0;i<end;i++){
        for(int j=0;j<first;j++){
            double a;
            a=getrand();
            weights.push_back(a);
        }
    }
    return 0;
}
//
//
//这是输入层的类
class Ilayer:public layer{
    public:
        vector <double> input_data;
        int init_inputdata(int num_node,vector <double> &input_data,vector <double> chuan);
        int change_inputdata(int num_node,vector <double> &input_data,vector <double> chuan);
};
int Ilayer::change_inputdata(int num_node,vector <double> &input_data,vector <double> chuan){
    for(int i=0;i<num_node;i++){
        input_data[i]=chuan[i];
    }
    return 0;
}
int Ilayer::init_inputdata(int num_node,vector <double> &input_data,vector <double> chuan){
    for(int i=0;i<num_node;i++){
        input_data.push_back(chuan[i]);
    }
    return 0;
}
int change_inputdata(int num_node,vector <double> &input_data,vector <double> chuan){
	for(int i=0;i<num_node;i++){
		input_data[i]=chuan[i];
	}
	return 0;
}
class Hlayer:public layer{
    public:
        vector <double> hidden_val;
        vector <double> sigmoid_val;
        vector <double> bias;
        vector <double> delta_bias;
        vector <double> delta_biasall;
        int init_deltabias(int num_node,vector <double> &delta_bias);
        int init_hiddenval(int num_node,vector <double> &hidden_val);
        int init_sigmoidval(int num_node,vector <double> &sigmod_val);
        int init_bias(int num_node,vector <double> &bias);
        int init_deltabiasall(int num_mode,vector <double> &delta_biasall);
		int zero_deltabias(int num_node,vector <double> &delta_bias);
		int zero_deltabiasall(int num_node,vector <double> &delta_biasall);
};
//初始化biasall
//
int Hlayer::zero_deltabias(int num_node,vector <double> &delta_bias){
	for(int i=0;i<num_node;i++){
		delta_bias[i]=0.0;
	}
	return 0;
}
int Hlayer::zero_deltabiasall(int num_node,vector <double> &delta_biasall){
	for(int i=0;i<num_node;i++){
		delta_biasall[i]=0.0;
	}
	return 0;
}
int Hlayer::init_deltabias(int num_node,vector <double> &delta_bias){
    for(int i=0;i<num_node;i++){
        delta_bias.push_back(0.0);
    }
    return 0;
}
//初始化deltabiasall
//
int Hlayer::init_deltabiasall(int num_node,vector <double> &delta_biasall){
    for(int i=0;i<num_node;i++){
        delta_biasall.push_back(0.0);
    }
    return 0;
}
//初始化bias
//
int Hlayer::init_bias(int num_node,vector <double> &bias){
        for(int j=0;j<num_node;j++){
            double m=getrand();
            bias.push_back(m);
        }
        return 0;
}
//初始化hidden_val
//
int Hlayer::init_hiddenval(int num_node,vector <double> &hidden_val){
        for(int j=0;j<num_node;j++){
            hidden_val.push_back(0.0);
        }
        return 0;
}
//初始化sigmoidval
//
int Hlayer::init_sigmoidval(int num_node,vector <double> &sigmoid_val){
        for(int j=0;j<num_node;j++){
            sigmoid_val.push_back(0.0);
        }
        return 0;
}


//output_layer的类
class Olayer:public layer{
    public:
        vector <double> output;
        vector <double> label;
        int init_output(int num_node,vector <double> &output);
        int init_label(int patum,int num_node,vector <double> &label);
};
int Olayer::init_output(int num_node,vector <double> &output){
        for(int j=0;j<num_node;j++){
            output.push_back(0.0);
        }
        return 0;
}
//获取epoch
//
int get_epoch(){
    int epoch;
    cout<<"请输入epoch"<<endl;
    cin>>epoch;
    return epoch;
}
//获取batchsize
//
int get_patum(){
    int patum;
    cout<<"请输入patum"<<endl;
    cin>>patum;
    return patum;
}
//获取学习率
//
double get_lr(){
    double lr;
    cout<<"请输入学习率"<<endl;
    cin>>lr;
    return lr;
}
//隐藏层层数
//
int init_numhiddenlayer(){
    int num_hiddenlayer;
    cout<<"请输入隐藏层层数"<<endl;
    cin>>num_hiddenlayer;
    return num_hiddenlayer;
}
//初始化input_layer
//初始化output_layer
Olayer init_outputlayer(){
    cout<<"请输入输出层的节点数"<<endl;
    int onum=2;
    Olayer output_layer;
    output_layer.set_numnode(onum);
    output_layer.init_output(onum,output_layer.output);
    return output_layer;
}
//初始化隐藏层参数
int init_hiddenparam(Hlayer &hidden_layer){
    hidden_layer.init_hiddenval(hidden_layer.num_node,hidden_layer.hidden_val);
    hidden_layer.init_sigmoidval(hidden_layer.num_node,hidden_layer.sigmoid_val);
    hidden_layer.init_bias(hidden_layer.num_node,hidden_layer.bias);
    hidden_layer.init_deltabias(hidden_layer.num_node,hidden_layer.delta_bias);
    hidden_layer.init_deltabiasall(hidden_layer.num_node,hidden_layer.delta_biasall);
    return 0;
}
int zero_hiddenparam(Hlayer &hidden_layer){
    for(int i=0;i<hidden_layer.num_node;i++){
        hidden_layer.delta_bias[i]=0.0;
    }
    for(int i=0;i<hidden_layer.num_node;i++){
        hidden_layer.delta_biasall[i]=0.0;
    }
    for(int i=0;i<hidden_layer.num_node;i++){
        hidden_layer.delta[i]=0.0;
    }
    return 0;
}
int zero_outputdelta(Olayer &output_layer){
    for(int i=0;i<output_layer.num_node;i++){
        output_layer.delta[i]=0.0;
    }
    return 0;
}
//input_layer和hidden_layer之间的连接
int data_trainIH(int first,
        int end,
        vector <double> &data,
        vector <double> &weights,
        vector <double> &hidden_val,
        vector <double> &sigmoid_val,
        vector <double> &bias)
{
        for(int j=0;j<end;j++){//相当于后一个节点的个数,weight节点
            hidden_val[j]=0.0;
            for(int k=0;k<first;k++){//相当于前一个节点的个数,数据节点点
                hidden_val[j]=hidden_val[j]+data[k]*weights[j*end+k];
            }
        hidden_val[j]=hidden_val[j]+bias[j];
        sigmoid_val[j]=sigmoid(hidden_val[j]);
        }
    return 0;
}
//隐藏层之间的连接
int data_trainHH(int first,
        int end,
        vector <double> &sig1,
        vector <double> &val,
        vector <double> &weights,
        vector <double> &sig2,
        vector <double> &bias)
{
        for(int j=0;j<end;j++){//相当于后一个节点的个数,weight节点
            val[j]=0.0;
            for(int k=0;k<first;k++){//相当于前一个节点的个数,数据节点点
                val[j]=val[j]+sig1[k]*weights[k+j*end];
            }
        val[j]+=bias[j];
        sig2[j]=sigmoid(sig1[j]);
        }
    return 0;
}
//隐藏层和输出层之间的连接
int data_trainHO(int first,
        int end,
        vector <double> &sig1,
        vector <double> &weights,
        vector <double> &output)
{
        for(int j=0;j<end;j++){//相当于后一个节点的个数,weight节点
        output[j]=0.0;
            for(int k=0;k<first;k++){//相当于前一个节点的个数,数据节点点

                output[j]=output[j]+sig1[k]*weights[j*end+k];
            }
        output[j]=sigmoid(output[j]);//就是yn
    }
    return 0;
}
int cal_delta(int num_node,
        vector <double> &delta,
        vector <double> &output,
        vector <double> &label)
{
	//cout<<output[0]<<"\t\t\t\t\t"<<output[1]<<endl;
        for(int j=0;j<num_node;j++){
            delta[j]=output[j]-label[j];
        }
        return 0;
}
int delta_bias_weight(int first,
        int end,
        vector <double> &deltafirst,
        vector <double> &sigmoid_val,
        vector <double> &weights,
        vector <double> &deltalast,
        vector <double> &delta_bias,
        vector <double> &delta_weight,
        vector <double> &delta_weightall,
        vector <double> &delta_biasall,
		vector <double> &output)
{
        for(int j=0;j<end;j++){
            for(int k=0;k<first;k++){
                deltalast[j]=weights[k*end+j]*deltafirst[k];//在这里deltalast又给该层的delta赋值.
                delta_weight[k*end+j]=sigmoid_val[j]*deltafirst[k]*fsigmoid(output[k]);
                delta_weightall[k*end+j]+=delta_weight[k*end+j];
            }
            delta_bias[j]=fsigmoid(sigmoid_val[j])*deltalast[j];//在这里
            delta_biasall[j]+=delta_bias[j];
        }
//		cout<<"weights="<<weights[3]<<endl;
//没问题,delta_weight和delta_weightall都没有问题
//	cout<<"delta_weight="<<delta_weight[1]<<endl;
//	cout<<"delta_weightall="<<delta_weightall[1]<<endl;
    return 0;

}
//计算delta_weight
//
int delta_weight(//第几个patum
        int first,
        int end,
        vector <double> &delta,
        vector <double> &data,
        vector <double> &delta_weight,
        vector <double> &delta_weightall)
{
    for(int j=0;j<end;j++){
        for(int k=0;k<first;k++){
            delta_weight[k*end+j]=data[j]*delta[k];
            delta_weightall[k*end+j]+=delta_weight[k*end+j];
        }
    }
//	cout<<"delta="<<delta[0]<<endl;delta没有问题
//		cout<<"delta_weight="<<delta_weight[0]<<endl;
//		cout<<"delta_weightall="<<delta_weightall[0]<<endl;
//		hidden层和input层之间的weightdelta有问题
    return 0;
}
//改变input层和hidden层之间的权值
//
int weight_changeIH(double lr,
        int patum,
        Ilayer &input_layer)
{
    int m=input_layer.weights.size();
    for(int i=0;i<m;i++){
        input_layer.weights[i]=input_layer.weights[i]-lr*(input_layer.delta_weightall[i])/patum;
    }
    return 0;
}
//改变隐藏层之间的权值连接
//
int weight_changeHH(double lr,
        int patum,
        Hlayer &hidden_layer){
    int m=hidden_layer.weights.size();
    for(int i=0;i<m;i++){
        hidden_layer.weights[i]=hidden_layer.weights[i]-lr*(hidden_layer.delta_weightall[i]/patum);
    }
    return 0;
}
int weight_changeHO(double lr,
		int patum,
		Hlayer &hidden_layer){
	int m=hidden_layer.weights.size();
	for(int i=0;i<m;i++){
		hidden_layer.weights[i]=hidden_layer.weights[i]-lr*hidden_layer.delta_weightall[i]/patum;
	}
	return 0;
}
//计算bias_change
//
int bias_change(double lr,
        int patum,
        Hlayer &hidden_layer)
{
    int m=hidden_layer.num_node;
    for(int i=0;i<m;i++){
        hidden_layer.bias[i]=hidden_layer.bias[i]-lr*(hidden_layer.delta_biasall[i]/patum);
    }
    return 0;
}
//写入权值到文件中去

template <typename Dtype>
int writeweight(Dtype layerparam){
    ofstream ofile;
    ofile.open("param.txt",ios::app);
    int m=layerparam.weights.size();
    for(int i=0;i<m;i++){
        ofile<<layerparam.weights[i]<<endl;
    }
    ofile<<flush;
    ofile.close();
    return 0;
}
//写入bias到文件中去
//*

template <typename Dtype>
int writebias(Dtype layerparam){
    ofstream ofile;
    ofile.open("param.txt",ios::app);
    int m=layerparam.bias.size();
    for(int i=0;i<m;i++){
        ofile<<layerparam.bias[i]<<endl;
    }
    ofile<<flush;
    ofile.close();
    return 0;
}

int display(Olayer output_layer){
	double error=0.0;
	for(int i=0;i<output_layer.num_node;i++){
		error+=(output_layer.output[i]-output_layer.label[i])*(output_layer.output[i]-output_layer.label[i]);
	}
//	cout<<"error="<<error<<"\t";
	return 0;
}

int test(Ilayer input_layer,Hlayer hidden_layer,Olayer output_layer){
    ifstream ifile;
    ifile.open("valdata");
    int val_patum=28;
    int inum=input_layer.num_node;
    double data[val_patum][inum];
    for(int i=0;i<val_patum;i++){
        for(int j=0;j<inum;j++){
            ifile>>data[i][j];
        }
    }
    ifile.close();
    ifstream lfile;
    lfile.open("vallabel");
    int label[28];
    for(int i=0;i<28;i++){
        lfile>>label[i];
    }
    lfile.close();
    vector <double> chuan;
    for(int i=0;i<inum;i++){
        chuan.push_back(data[0][i]);
    }
    int correct=0;
//	cout<<"验证集error"<<endl;
	for(int m=0;m<28;m++){
		for(int po=0;po<inum;po++){
			chuan[po]=data[m][po];
		}
        input_layer.change_inputdata(inum,input_layer.input_data,chuan);
        data_trainIH(input_layer.num_node,
                hidden_layer.num_node,
                input_layer.input_data,
                input_layer.weights,
                hidden_layer.hidden_val,
                hidden_layer.sigmoid_val,
                hidden_layer.bias);
/*        for(int i=0;i<num_hidden-1;i++){
            data_trainHH(hidden_layer[i].num_node,
                    hidden_layer[i+1].num_node,
                    hidden_layer[i].sigmoid_val,
                    hidden_layer[i].weights,
                    hidden_layer[i+1].hidden_val,
                    hidden_layer[i+1].sigmoid_val,
                    hidden_layer[i+1].bias);*/
      //  }
        data_trainHO(hidden_layer.num_node,
                output_layer.num_node,
                hidden_layer.sigmoid_val,
                hidden_layer.weights,
                output_layer.output);
        int max=-10000;
        int flag;
        for(int k=0;k<output_layer.num_node;k++){
            if(max<output_layer.output[k]){
                max=output_layer.output[k];
                flag=k;
            }
        }
	//	display(output_layer);
        if(flag==label[m]){
            correct+=1;
        }
    }
    double acc;
    double dc;
    dc=(double)correct;
//    acc=dc/val_patum;
//    cout<<"正确率为"<<acc<<endl;
    return 0;

}//主函数
int traintest(Ilayer input_layer,Hlayer hidden_layer,Olayer output_layer){
    ifstream ifile;
    ifile.open("traindata");
    int train_patum=170;
    int inum=input_layer.num_node;
    double data[train_patum][inum];
    for(int i=0;i<train_patum;i++){
        for(int j=0;j<inum;j++){
            ifile>>data[i][j];
        }
    }
    ifile.close();
    ifstream lfile;
    lfile.open("trainlabel");
    int label[170];
    for(int i=0;i<170;i++){
        lfile>>label[i];
    }
    lfile.close();
    vector <double> chuan;
    for(int i=0;i<inum;i++){
        chuan.push_back(data[0][i]);
    }
    int correct=0;
	for(int m=0;m<170;m++){
		for(int po=0;po<inum;po++){
			chuan[po]=data[m][po];
		}
        input_layer.change_inputdata(inum,input_layer.input_data,chuan);
        data_trainIH(input_layer.num_node,
                hidden_layer.num_node,
                input_layer.input_data,
                input_layer.weights,
                hidden_layer.hidden_val,
                hidden_layer.sigmoid_val,
                hidden_layer.bias);
        data_trainHO(hidden_layer.num_node,
                output_layer.num_node,
                hidden_layer.sigmoid_val,
                hidden_layer.weights,
                output_layer.output);
        int max=-10000;
        int flag;
        for(int k=0;k<output_layer.num_node;k++){
            if(max<output_layer.output[k]){
                max=output_layer.output[k];
                flag=k;
            }
        }
        if(flag!=label[m]){
            correct+=1;
        }
    }
    double acc;
    double dc;
    dc=(double)correct;
    acc=dc/train_patum;
	display(output_layer);
//  cout<<"\t"<<"acc="<<acc<<endl;
    return 0;
}
int main(){
    int epoch=50000;
    int patum=170;
    double lr=0.01;
    Ilayer input_layer;
    int inum=30;
    input_layer.set_numnode(inum);
    ifstream ifile;
    ifile.open("traindata");
    double fileparam[patum][inum];
    for(int i=0;i<patum;i++){
        for(int j=0;j<inum;j++){
            ifile>>fileparam[i][j];
        }
    }
    ifile.close();
    vector <double> chuan;
        for(int j=0;j<inum;j++){
            chuan.push_back(fileparam[0][j]);
        }
    input_layer.init_inputdata(inum,input_layer.input_data,chuan);
	Hlayer hidden_layer;
//    int num_hiddenlayer=2;//隐藏层层数
//    Hlayer hidden_layer[num_hiddenlayer];
        int hnum=30;
		int num_hiddenlayer=1;
        hidden_layer.set_numnode(hnum);
//		hidden_layer[1].set_numnode(3);
    int onum=2;
    Olayer output_layer;
    output_layer.set_numnode(onum);
    output_layer.init_output(onum,output_layer.output);//初始化output,全设为0
   output_layer.init_delta(onum,output_layer.delta);//初始化delta
   hidden_layer.init_delta(hnum,hidden_layer.delta);
    ifstream lfile;
    lfile.open("trainlabel");
    int flag[170];
    for(int i=0;i<patum;i++){
        lfile>>flag[i];
    }
    lfile.close();
    output_layer.label.push_back(1.0);
    output_layer.label.push_back(0.0);
//初始化权值
    input_layer.init_weight(input_layer.num_node,
            hidden_layer.num_node,
            input_layer.weights);
    hidden_layer.init_weight(hidden_layer.num_node,
            output_layer.num_node,
            hidden_layer.weights);
	init_hiddenparam(hidden_layer);
    hidden_layer.init_deltaweight(hidden_layer.num_node,
            output_layer.num_node,
            hidden_layer.delta_weight);
    hidden_layer.init_deltaweightall(output_layer.num_node,
            hidden_layer.num_node,
            hidden_layer.delta_weightall);
    input_layer.init_deltaweight(input_layer.num_node,
            hidden_layer.num_node,
            input_layer.delta_weight);
    input_layer.init_deltaweightall(hidden_layer.num_node,
            input_layer.num_node,
            input_layer.delta_weightall);

//前向计算
    for(int i=0;i<epoch;i++){
		cout<<i+1<<"\t\t\t";
//		cout<<hidden_layer.sigmoid_val[1]<<endl;
        for(int j=0;j<patum;j++){
	//		cout<<j+1<<"\t\t\t\t";
        for(int l=0;l<inum;l++){
            chuan[l]=fileparam[j][l];
        }
        input_layer.change_inputdata(inum,input_layer.input_data,chuan);//改变数据的
        if(flag[j]==0){
            output_layer.label[0]=1.0;
            output_layer.label[1]=0.0;
        }
        else{
            output_layer.label[0]=0.0;
            output_layer.label[1]=1.0;

        }
		//数据读入没有问题,输入层数据没有问题
        data_trainIH(
                input_layer.num_node,
                hidden_layer.num_node,
                input_layer.input_data,
                input_layer.weights,
                hidden_layer.hidden_val,
                hidden_layer.sigmoid_val,
                hidden_layer.bias);

        //计算隐藏层与输出层之间的数据传输
        data_trainHO(hidden_layer.num_node,
                output_layer.num_node,
                hidden_layer.sigmoid_val,
                hidden_layer.weights,
                output_layer.output);
//后向计算
        //计算残差
        cal_delta(output_layer.num_node,
                output_layer.delta,
                output_layer.output,
                output_layer.label);
        delta_bias_weight(output_layer.num_node,
                hidden_layer.num_node,
                output_layer.delta,
                hidden_layer.sigmoid_val,
                hidden_layer.weights,
                hidden_layer.delta,
                hidden_layer.delta_bias,
                hidden_layer.delta_weight,
                hidden_layer.delta_weightall,
                hidden_layer.delta_biasall,
				output_layer.output);//计算输出层与隐藏层之间的delta_weight,delta__bias

		delta_weight(
                hidden_layer.num_node,
                input_layer.num_node,
                hidden_layer.delta,
                input_layer.input_data,
                input_layer.delta_weight,
                input_layer.delta_weightall);//改变隐藏层和输入层之间的连接
        }
		//delta_weightall出了问题,全为0
//		for(int cc=0;cc<input_layer.delta_weightall.size();cc++){
//			cout<<input_layer.delta_weightall[cc]<<endl;
//
//}
        weight_changeIH(lr,patum,input_layer);
  /*      for(int n=0;n<num_hiddenlayer;n++){
            weight_changeHH(lr,patum,hidden_layer[n]);
            bias_change(lr,patum,hidden_layer[n]);
            }*/
		weight_changeHO(lr,patum,hidden_layer);
		bias_change(lr,patum,hidden_layer);
		//display(output_layer);
        //这是在将其中一些元素清零处理
		cout<<"weights="<<hidden_layer.weights[3]<<endl;
    for(int p=0;p<num_hiddenlayer;p++){
        zero_hiddenparam(hidden_layer);
    }
    zero_outputdelta(output_layer);
    input_layer.zero_deltaweight(input_layer.num_node,
            hidden_layer.num_node,
            input_layer.delta_weight);
    input_layer.zero_deltaweightall(input_layer.num_node,
            hidden_layer.num_node,
            input_layer.delta_weightall);//input层

    hidden_layer.zero_deltabias(hidden_layer.num_node,
            hidden_layer.delta_bias);
    hidden_layer.zero_deltabiasall(hidden_layer.num_node,
            hidden_layer.delta_biasall);
	  hidden_layer.zero_deltaweight(hidden_layer.num_node,
            output_layer.num_node,
            hidden_layer.delta_weight);
    hidden_layer.zero_deltaweightall(hidden_layer.num_node,
            output_layer.num_node,
            hidden_layer.delta_weightall);
	traintest(input_layer,hidden_layer,output_layer);
    }

     test(input_layer,hidden_layer,output_layer);
    ofstream ofile;
    ofile.open("param.txt");
    ofile<<epoch<<endl;
    ofile<<patum<<endl;
    ofile<<lr<<endl;
    ofile<<num_hiddenlayer<<endl;
    ofile<<input_layer.num_node<<endl;
	writeweight(input_layer);
	writeweight(hidden_layer);
	writebias(hidden_layer);
    return 0;
}

