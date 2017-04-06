#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<math.h>
#include<time.h>
#include<vector>

using namespace cv;
using namespace std;
void get_midmum(const Mat &img,Mat &new_img,int n=3){
	int nr=img.rows;
	int nc=img.cols;
	float data[3][nr+2][nc+2];
	for(int i=0;i<3;i++){
		for(int j=0;j<nr+2;j++){
			for(int k=0;k<nc+2;k++){
				if(j>=1&&j<=nr&&k>=1&&k<=nc){
					data[i][j][k]=img.at<Vec3b>(j-1,k-1)[i];
				}else{
					data[i][j][k]=0;
				}
			}
		}
		for(int j=1;j<=nr;j++){
			for(int k=1;k<=nc;k++){
				float result;
				vector <float> temp;
				temp.push_back(data[i][j][k]);
				temp.push_back(data[i][j-1][k-1]);
				temp.push_back(data[i][j-1][k]);
				temp.push_back(data[i][j][k-1]);
				temp.push_back(data[i][j][k+1]);
				temp.push_back(data[i][j+1][k]);
				temp.push_back(data[i][j+1][k+1]);
				temp.push_back(data[i][j-1][k+1]);
				temp.push_back(data[i][1+j][k-1]);
				sort(temp.begin(),temp.end());
				new_img.at<Vec3b>(j-1,k-1)[i]=temp[4];
			}
		}
	}
}
int main(int argc,char* argv[]){
	Mat img=imread(argv[1]);
	int a=3;//边框长宽
	Mat new_img;
	int nr=img.rows;
	int nc=img.cols;
	new_img.create(img.size(),img.type());
	get_midmum(img,new_img,3);
	imwrite("result.jpg",new_img);
	imshow("result",new_img);
	waitKey(0);
	return 0;
}
