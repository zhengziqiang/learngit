/*==============================================================================
    > File Name: main.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年01月14日 星期六 18时45分24秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<time.h>
#include<math.h>
using namespace std;
using namespace cv;
void fun(Mat &img,int div){
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			img.at<Vec3b>(i,j)[0]=img.at<Vec3b>(i,j)[0]/div*div+div/2;
			img.at<Vec3b>(i,j)[1]=img.at<Vec3b>(i,j)[1]/div*div+div/2;
			img.at<Vec3b>(i,j)[2]=img.at<Vec3b>(i,j)[2]/div*div+div/2;
		}
	}
}

void fun2(const Mat &img,Mat & out,int div){
	out.create(img.size(),img.type());
	int nr=img.rows;
	int nl=img.cols*img.channels();
	for(int k=0;k<nr;k++){
		const uchar *in_data=img.ptr<uchar>(k);//uchar 是一个数据类型，只占8个字节，是为了与int相比省略内存的
		uchar *out_data=out.ptr<uchar>(k);
		for(int j=0;j<nl;j++){
			out_data[j]=in_data[j]/div*div + div/2;
		}
	}
}

//CvScalar pt；
//
//如果使用的图像是1通道的，则pt.val[0]中存储数据
//
//如果使用的图像是3通道的，则pt.val[0]，pt.val[1]，pt.val[2]中存储数据
//
//==============================
//
//cvGet2D 获得某个点的值, idx0=hight 行值, idx1=width 列值。
//CVAPI(CvScalar) cvGet2D( const CvArr* arr, int idx0, int idx1 );
// -----------------------------------------------
//cvSet2D 给某个点赋值。
//CVAPI(void) cvSet2D( CvArr* arr, int idx0, int idx1, CvScalar value );
// -----------------------------------------------
//由上可见，cvGet2D的返回类型和cvSet2D中value的类型都是CvScalar，这样定义一个CvScalar变量再调用函数就OK了。
//
//
//效率最高的一种访问方式
void color_reduce(const Mat &img,Mat &out,int div){
	int nr=img.rows;
	int nc=img.cols;
	out.create(img.size(),img.type());
	if(img.isContinuous()&&out.isContinuous()){
		nr=1;
		nc=nc*img.rows*img.channels();
	}
	for(int i=0;i<nr;i++){
		const uchar *in_data=img.ptr<uchar>(i);
		uchar *out_data=out.ptr<uchar>(i);
		for(int j=0;j<nc;j++){
			*out_data++=*in_data++/div*div+div/2;//指针的自加运算，自加运算优先级更先
		}
	}
}
//使用迭代器进行访问
void fun_iterator(const Mat &img,Mat &out,int div){
	out.create(img.size(),img.type());
	MatConstIterator_<Vec3b> it_in=img.begin<Vec3b>();
	MatConstIterator_<Vec3b> itend_in=img.end<Vec3b>();
	MatIterator_<Vec3b> it_out=out.begin<Vec3b>();
	MatIterator_<Vec3b> itend_out=out.end<Vec3b>();
	while(it_in!=itend_in){
		(*it_out)[0]=(*it_in)[0]/div*div+div/2;
		(*it_out)[1]=(*it_in)[1]/div*div+div/2;
		(*it_out)[2]=(*it_in)[2]/div*div+div/2;
		it_in++;
		it_out++;
	}
}

int main(int argc,char *argv[]){
	if(argc!=3){
		cout<<"Wrong arguments input"<<endl;
		cout<<"usage:"<<endl;
		cout<<argv[0]<<" image name "<<" output image"<<endl;
		exit(1);
	}
	string img1=argv[1];
	string img2=argv[2];
	Mat img=imread(img1);
	Mat out;
	if(!img.data){
		cout<<"can't read image properly"<<endl;
		exit(2);
	}
	imshow("show",img);
	fun(img,4);
	fun2(img,out,4);
	imshow("Processed",img);
	imwrite(img2,out);
	waitKey(0);
	return 0;
}
