/*==============================================================================
    > File Name: color_reduce.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年01月01日 星期日 14时19分38秒
 ==========================================================================*/

#include<iostream>
#include<vector>

using namespace std;
void color_reduce(Mat &image,int div){
	for(int i=0;i<image.rows;i++){
		for(int j=0;j<image.cols;j++){
			image.at<Vec3b>(i,j)[0]=image.at<Vec3b>(i,j)[0]/div*div+div/2;
			image.at<Vec3b>(i,j)[1]=image.at<Vec3b>(i,j)[1]/div*div+div/2;
			image.at<Vec3b>(i,j)[2]=image.at<Vec3b>(i,j)[2]/div*div+div/2;
		}
	}
}
void color_reduce(const Mat &iamge,Mat &out,int div){
	out.create(image.size(),image.type());
	int nr=image.rows;
	int nl=image.cols*image.channels();

}
