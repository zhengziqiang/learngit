/*==============================================================================
    > File Name: easy_卷积.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月10日 星期六 22时46分26秒
 ==========================================================================*/

#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;
float get_rng(){
	srand(time(NULL));
	float a=rand()/(float)(RAND_MAX);
	return a;
}
int get_rng_int(){
	srand(time(NULL));
	int a=rand()%255;//产生一个范围内的随机值的操作是 r=rand()(n-m+1)+m,产生[m,n]之间的随机值
	return a;
}
void multi(float **image,float **weight,float *m,int i,int j,int conv_h,int conv_w){
	for(int k=0;k<conv_h;k++){
	float *tmp_image=&image[i+k][j];
	float *tmp_weight=weight[k];
		for(int l=0;l<conv_w;l++){
			*m+=*tmp_image * *tmp_weight;
			tmp_image++;
			tmp_weight++;
			
		}

	}
}
int main(){
	int height;
	int width;
	cout<<"please input the height of the image"<<endl;
	cin>>height;
	cout<<"please input the width of the image"<<endl;
	cin>>width;
	float  **image;
	image=new float*[height];
	for(int i=0;i<height;i++){
		image[i]=new float[width];
		for(int j=0;j<width;j++){
			image[i][j]=get_rng_int();
		}
	}
	float **weight;
	int m;
	cout<<"please input the number of the weight"<<endl;
	cin>>m;
	weight=new float*[m];
	for(int i=0;i<m;i++)
	{
		weight[i]=new float[m];
		for(int j=0;j<m;j++)
			weight[i][j]=get_rng();
	}
	int stride;
	cout<<"please input the stride"<<endl;
	cin>>stride;
	int conv_h;
	int conv_w;
	conv_h=(height+1-m)/stride;
	conv_w=(width+1-m)/stride;
	float **conv_image;
	conv_image=new float*[conv_h];
	for(int i=0;i<conv_h;i++){
		conv_image[i]=new float[conv_w];
		for(int j=0;j<conv_w;j++){
			multi(image,weight,&conv_image[i][j],i,j,conv_h,conv_w);		
		}
	}
	return 0;
}
