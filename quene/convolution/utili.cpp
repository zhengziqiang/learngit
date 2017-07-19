#include <iostream>
#include <vector>
#include <math.h>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include <time.h>
using namespace cv;
using namespace std;
double ***convert_rgb(const Mat &img){
    int nr=img.rows;
    int nc=img.cols;
    double ***matrix;
    matrix=new double**[3];
    for(int i=0;i<3;i++){
        matrix[i]=new double *[nr];
        for(int j=0;j<nr;j++){
            matrix[i][j]=new double[nc];
            for(int k=0;k<nc;k++){
                matrix[i][j][k]=img.at<Vec3b>(j,k)[i];
            }
        }
    }
    return matrix;
}

double get_rand(){
    static double v1,v2,s;
    static int phase=0;
    double x;
    if(phase==0){
        do{
            double u1=(double)rand()/RAND_MAX;
            double u2=(double)rand()/RAND_MAX;
            v1=2*u1-1;
            v2=2*u2-1;
            s=v1*v1-v2*v2;
        }while(s>=1||s==0);
        x=v1*sqrt(-2*log(s)/s);
    }else{
       x=v2*sqrt(-2*log(s)/s);
    }
    phase=1-phase;
    double ans=x*0.1;
    return ans;
}

double ***kernel_weight(int num,int kernel_size){
    double ***weight;
    weight=new double**[num];
    for(int i=0;i<num;i++){
        weight[i]=new double*[kernel_size];
        for(int j=0;j<kernel_size;j++){
            weight[i][j]=new double[kernel_size];
            for(int k=0;k<kernel_size;k++){
                weight[i][j][k]=get_rand();
            }
        }
    }
    return weight;
}
double get_max(int n,vector <double> pixes){
    double tmp_max=-99999;
    for(int i=0;i<n;i++){
        if(tmp_max<pixes[i]){
            tmp_max=pixes[i];
        }
    }
    return tmp_max;
}

double get_average(int n,vector <double> pixes){
    double sum=0.0;
    for(int i=0;i<n;i++){
        sum+=pixes[i];
    }
    return sum/n;
}
void con_pool(double *pix,int n,vector <double> &pix_contain){
    for(int i=0;i<n;i++){
        pix_contain.push_back(pix[i]);
    }
}

double **get_pool(int h,int w,double **pix,int kernel_size,int stride,int pool_method){
    //pool_method
    //0   max pool
    //1   average pool
    double **pooled_pix;
    int n_pix=kernel_size*kernel_size;
    int pooled_h=(h-kernel_size)/stride+1;
    int pooled_w=(w-kernel_size)/stride+1;
    vector <double> pix_container;
    pooled_pix=new double*[pooled_h];
    for(int i=0;i<pooled_h;i++){
        pooled_pix[i]=new double[pooled_w];
    }
    for(int i=0;i<pooled_h;i++){
        for(int j=0;j<pooled_w;j++){
            int index_i;
            int index_j;
            index_i=i*stride;
            index_j=j*stride;
            for(int k=0;k<kernel_size;k++){
                con_pool(&pix[index_i][index_j],kernel_size,pix_container);
                index_i++;
            }
            if(pool_method){
                pooled_pix[i][j]=get_average(n_pix,pix_container);
            }else{
                pooled_pix[i][j]=get_max(n_pix,pix_container);
            }
            pix_container.clear();
        }
    }

}
