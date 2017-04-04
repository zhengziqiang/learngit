/*==============================================================================
    > File Name: main.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年01月14日 星期六 21时11分50秒
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
	imshow("origin",img);
	string str[7]={"k=7.jpg","k=6.jpg","k=5.jpg","k=4.jpg","k=3.jpg","k=2.jpg","k=1.jpg"};
	int a[7]={2,4,8,16,32,64,128};
	for(int i=0;i<7;i++){
		int nr=img.rows;
		int nc=img.cols;
		Mat new_img;
		new_img.create(img.size(),img.type());
		for(int x=0;x<nr;x++){
			for(int y=0;y<nc;y++){
				new_img.at<Vec3b>(x,y)[0]=img.at<Vec3b>(x,y)[0]/a[i];
				new_img.at<Vec3b>(x,y)[1]=img.at<Vec3b>(x,y)[1]/a[i];
				new_img.at<Vec3b>(x,y)[2]=img.at<Vec3b>(x,y)[2]/a[i];
			}
		}
		imwrite(str[i],new_img);
	}

	waitKey(0);
	return 0;
}
