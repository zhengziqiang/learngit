/*==============================================================================
    > File Name: main.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年01月14日 星期六 22时42分30秒
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
	Mat new_img;
	float nr=img.rows;
	float nc=img.cols;
	float f=1.5;
	float a=f*nr;
	float b=f*nc;
	new_img.create(a,b,img.type());
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			int m,n;
			float l=i/f;
			float k=j/f;
			m=(int)(l+0.5)>(int)l?(int)(l+0.5):(int)l;//确保了m,n在nr,nc这个范围内
			n=(int)(k+0.5)>(int)k?(int)(k+0.5):(int)k;
			new_img.at<Vec3b>(i,j)[0]=img.at<Vec3b>(m,n)[0];
			new_img.at<Vec3b>(i,j)[1]=img.at<Vec3b>(m,n)[1];
			new_img.at<Vec3b>(i,j)[2]=img.at<Vec3b>(m,n)[2];
		}
	}
	imwrite("result.jpg",new_img);
	waitKey(0);
	return 0;
}
