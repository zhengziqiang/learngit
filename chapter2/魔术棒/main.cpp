/*==============================================================================
    > File Name: main.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年01月15日 星期日 10时45分11秒
 ==========================================================================*/

#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<math.h>
#include<time.h>
using namespace cv;
using namespace std;
class color_detect{
	private:
		int mindist;
		Vec3b target;
		Mat result;
	public:
		color_detect();
		void set_mindistance(int dist);
		void set_targetcolor(uchar red,uchar green,uchar blue);
		void set_targetcolor(Vec3b color);
		Mat process(const Mat &img);

};
Mat color_detect::process(const Mat &img){
	Mat new_img=img.clone();
	result.create(img.size(),CV_8U);
	cvtColor(img,new_img,CV_BGR2lab);
	Mat temp(1,1,CV_BGR2lab);
	temp.at<Vec3b>(0,0)=target;
	cvtColor(temp,temp,CV_BGR2lab);
	target = temp.at<Vec3b>(0,0);
	Mat_<Vec3b>::iterator it=img.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend=img.end<Vec3b>();
	Mat_<uchar>::iterator itout=result.begin<uchar>();
	while(it!=itend){
		int dist=static_cast<int>(norm<int,3>(Vec3i((*it)[0]-target[0],
            (*it)[1]-target[1],(*it)[2]-target[2])));
        if(dist<minDist)
            (*itout)=255;
        else
            (*itout)=0;
        it++;
        itout++;
	}
	return result;
}
int main(int argc,char* argv[]){
	

	waitKey(0);
	return 0;
}
