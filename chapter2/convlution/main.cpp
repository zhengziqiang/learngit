/*==============================================================================
    > File Name: main.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年04月04日 星期二 21时31分21秒
 ==========================================================================*/


#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<math.h>
#include<time.h>
using namespace cv;
using namespace std;
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
float get_rng(){
	srand(time(NULL));
	float a=rand()/(float)(RAND_MAX);
	return a;
}
int main(int argc,char* argv[]){
	Mat img=imread(argv[1]);
	Mat new_img;
	int nr=img.rows;
	int nc=img.cols;
	int kernel_size=3;
	int stride=1;
	int conv_h;
	int conv_w;
	conv_h=(nr+1-kernel_size)/stride;
	conv_w=(nc+1-kernel_size)/stride;
	float  **image;
	image=new float*[nr];
	for(int i=0;i<nr;i++){
		image[i]=new float[nc];
		for(int j=0;j<nc;j++){
			image[i][j]=img.at<Vec3b>(i,j)[0];
		}
	}
	float **weight;
	weight=new float*[kernel_size];
	for(int i=0;i<kernel_size;i++)
	{
		weight[i]=new float[kernel_size];
		for(int j=0;j<kernel_size;j++)
			weight[i][j]=get_rng();
	}
	float **conv_image;
	conv_image=new float*[conv_h];
	for(int i=0;i<conv_h;i++){
		conv_image[i]=new float[conv_w];
		for(int j=0;j<conv_w;j++){
			multi(image,weight,&conv_image[i][j],i,j,conv_h,conv_w);		
		}
	}
	new_img.create(conv_h,conv_w,img.type());
	for(int i=0;i<conv_h;i++){
		for(int j=0;j<conv_w;j++){
			new_img.at<Vec3b>(i,j)[0]=conv_image[i][j];
			new_img.at<Vec3b>(i,j)[1]=0;
			new_img.at<Vec3b>(i,j)[2]=0;
		}
	}
	imwrite("result.jpg",new_img);
	waitKey(0);
	return 0;
}
