#include <QCoreApplication>
#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<math.h>
#include<time.h>
#include "utili.cpp"
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    string filename="";
    Mat img=imread(filename);
    int nr,nc;
    nr=img.rows;
    nc=img.cols;
    double ***pix_org=convert_rgb(img);
    double ***conv1_weight=kernel_weight(96,11);

    return a.exec();
}
