/*==============================================================================
    > File Name: main.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年01月14日 星期六 21时46分32秒
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
	double x=128;
	cvtColor(img,img,CV_BGR2GRAY);//将原图转换成灰度图
	int nr=img.rows;
	int nc=img.cols;
	Mat dst=Mat::zeros(nr,nc,CV_8UC1);
	for(int i=0;i<nr;i++){
		for(int j=0;j<nc;j++){
			dst.at<uchar>(i,j)=cvRound(img.at<uchar>(i,j)/x);//地板函数，取整函数,这里之所以是uchar是因为已经转化为灰度图了
		}
	}
	imwrite("dst.jpg",dst);
	waitKey(0);
	return 0;
}
