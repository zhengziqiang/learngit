/*==============================================================================
    > File Name: main.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年01月14日 星期六 21时56分55秒
 ==========================================================================*/

#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<math.h>
#include<time.h>
using namespace cv;
using namespace std;
int main(int argc,char* argv[]){

	Mat img=imread(argv[1]);
	int nr=img.rows;
	int nc=img.cols;
	double x=2;//缩小倍数
	float nrow=(float)nr/x;
	float ncol=(float)nc/x;
	Mat dst=Mat::zeros(nrow,ncol,CV_8UC3);//代表三通道
	for(int i=0;i<(int)nrow;i++){//这里不加int会报错,会导致数组下标越界
		for(int j=0;j<(int)ncol;j++){
			int X=cvRound(i*x);
			int Y=cvRound(j*x);
			if(X>=0&&x<nr&&Y>=0&&Y<nc){
				dst.at<Vec3b>(i,j)[0]=img.at<Vec3b>(X,Y)[0];
				dst.at<Vec3b>(i,j)[1]=img.at<Vec3b>(X,Y)[1];
				dst.at<Vec3b>(i,j)[2]=img.at<Vec3b>(X,Y)[2];
			}
		}
	}
	imwrite("result.jpg",dst);
	waitKey(0);
	return 0;
}
