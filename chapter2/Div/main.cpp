#include <iostream> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <time.h>

using namespace cv;
using namespace std;

int main(int argc , char *argv[])
{
	//输入语句报错
	if(argc != 3)
	{
		cout << "Wrong arguments input" << endl;
		cout << "usage:" << endl;
		cout << "\t" << argv[0] << "Image name" << endl;
		exit(1);
	}
	//读入图像
	string image1 = argv[1];
	string image2 = argv[2];
	Mat SEM = imread(image1);
	Mat shadow = imread(image2);
	//读入图像报错
  	if(!SEM.data )
	{
		cout << "Can't read image properly" << endl;
		exit(2);
	}
	//显示输入图像
	imshow("SEM" , SEM);
	imshow("shadow" , shadow);
	//建立输出图像
CvScalar A,F;
	Mat dst = Mat::zeros(SEM.rows , SEM.cols , CV_8UC3);
	for(int i = 0;i < SEM.rows;i ++)
	{	
		for(int j = 0;j < SEM.cols;j ++)
		{
			A.val[0] = shadow.at<cv::Vec3b>(i,j)[0] / 255.0;
			A.val[1] = shadow.at<cv::Vec3b>(i,j)[1] / 255.0;
			A.val[2] = shadow.at<cv::Vec3b>(i,j)[2] / 255.0;
			F.val[0] = SEM.at<cv::Vec3b>(i,j)[0] / A.val[0];
			F.val[1] = SEM.at<cv::Vec3b>(i,j)[1] / A.val[1];
			F.val[2] = SEM.at<cv::Vec3b>(i,j)[2] / A.val[2];
			if(F.val[0] > 255) F.val[0] = 255;
			if(F.val[1] > 255) F.val[1] = 255;
			if(F.val[2] > 255) F.val[2] = 255;
			dst.at<cv::Vec3b>(i,j)[0] = (int)F.val[0];
			dst.at<cv::Vec3b>(i,j)[1] = (int)F.val[1];
			dst.at<cv::Vec3b>(i,j)[2] = (int)F.val[2];
		}	
	}
	imshow("result",dst);
	imwrite("result.jpg",dst);
	waitKey(0);    
	return 0;    
}  


