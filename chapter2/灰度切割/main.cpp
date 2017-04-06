/*==============================================================================
    > File Name: main.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年01月21日 星期六 22时19分57秒
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


	waitKey(0);
	return 0;
}
