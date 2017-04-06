
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
	cvtColor(img,img,CV_BGR2GRAY);
	const int* channels={0};
	int histsize[2]={0,25};
	const int *hist_size={histsize};
	float hranges[2]={0,255};
	const float *ranges[1]={hranges};
	Mat hist;
	calcHist(&img,1,channels,Mat(),hist,1,hist_size,ranges);//这里的histsize必须要加取址符，不然会出错
	//img是原图像
	//1代表着是一个图
	//channel是通道数，1为灰度图，3为彩色图像
	//Mat()是一个空位像，是一个遮罩图像用于确定哪些点参与计算
	//hist是计算得到的直方图
	//histsize是得到直方图的维数，灰度为1，彩色为3
	//ranges是像素的变化范围
	imshow("result",hist);
	imwrite("result.jpg",hist);
	waitKey(0);
	return 0;
}

//彩色直方图
//int main()
//{
//    Mat Image=imread("../cat.png");
//
//    const int channels[3]={0,1,2};
//    const int histSize[3]={256,256,256};
//    float hranges[2]={0,255};
//    const float* ranges[3]={hranges,hranges,hranges};
//    MatND hist;
//    calcHist(&Image,1,channels,Mat(),hist,3,histSize,ranges);
//
//    return 0;
//}
//
//
//统计
//int main()
//{
//    Mat Image=imread("../cat.png");
//    cvtColor(Image,Image,CV_BGR2GRAY);
//
//    const int channels[1]={0};
//    int histSize[1]={5};
//    float hranges[6]={0,50,80,150,230,255};
//    const float* ranges[1]={hranges};
//
//    MatND hist;
//    calcHist(&Image,1,channels,Mat(),hist,1,histSize,ranges,false);
//
//    return 0;
//}
//
//直方图的显示
Mat getHistImg(const MatND& hist)
{
    double maxVal=0;
    double minVal=0;

    //找到直方图中的最大值和最小值
    minMaxLoc(hist,&minVal,&maxVal,0,0);
    int histSize=hist.rows;
    Mat histImg(histSize,histSize,CV_8U,Scalar(255));
    // 设置最大峰值为图像高度的90%
    int hpt=static_cast<int>(0.9*histSize);

    for(int h=0;h<histSize;h++)
    {
        float binVal=hist.at<float>(h);
        int intensity=static_cast<int>(binVal*hpt/maxVal);
        line(histImg,Point(h,histSize),Point(h,histSize-intensity),Scalar::all(0));
    }

    return histImg;
}
