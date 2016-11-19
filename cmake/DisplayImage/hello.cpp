/*==============================================================================
    > File Name: hello.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月19日 星期六 23时46分49秒
 ==========================================================================*/
#include <stdio.h>  
#include <opencv2/opencv.hpp>  
  
using namespace cv;  
  
int main( int argc, char** argv )  
{  
Mat image;  
image = imread("lena.jpg");  
  
namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );  
imshow( "Display Image", image );  
  
waitKey(0);  
  
return 0;  
}  
