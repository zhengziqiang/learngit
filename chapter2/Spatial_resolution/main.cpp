/*==============================================================================
    > File Name: main.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年01月14日 星期六 20时19分52秒
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

	imshow("original",img);
	Mat new_img;
	int a[3]={4,8,16};
	int nr=img.rows;
	int nc=img.cols;
	String str[3]={
		"300dpi.jpg",
		"150dpi.jpg",
		"72dpi.jpg"
	};
	for(int i=0;i<3;i++){
		int m=nr/a[i];
		int n=nc/a[i];
		new_img.create(m,n,img.type());
		CvScalar sum;
		for(int x=0;x<m;x++){
			for(int y=0;y<n;y++){
				sum.val[0]=sum.val[1]=sum.val[2]=0;
				for(int l=a[i]*x;l<a[i]*(x+1);l++){
					for(int k=a[i]*y;k<a[i]*(y+1);k++){
						sum.val[0]+=img.at<Vec3b>(l,k)[0];
						sum.val[1]+=img.at<Vec3b>(l,k)[1];
						sum.val[2]+=img.at<Vec3b>(l,k)[2];
					}
				}
				new_img.at<Vec3b>(x,y)[0]=sum.val[0]/(a[i]*a[i]);
				new_img.at<Vec3b>(x,y)[1]=sum.val[1]/(a[i]*a[i]);
				new_img.at<Vec3b>(x,y)[2]=sum.val[2]/(a[i]*a[i]);
			}
		}
		imwrite(str[i],new_img);
	}

	waitKey(0);
	return 0;
}
