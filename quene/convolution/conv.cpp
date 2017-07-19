#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include "utili.cpp"
using namespace std;
double relu(double x){
    return max(x,0.0);
}
void conv(double *pix,int n,vector <double> &pix_contain){
    for(int i=0;i<n;i++){
        pix_contain.push_back(pix[i]);
    }
}
double matmul(vector <double> pix,double **weight,int kernel_size){
    double sum=0.0;
    for(int i=0;i<kernel_size;i++){
        for(int j=0;j<kernel_size;j++){
            sum+=(weight[i][j]*pix[i*kernel_size+j]);
        }
    }
    return sum;
}

double **conv_pix(double **pix,double **weight,int kernel_size,int stride,int h,int w){
    vector <double> pix_container;
    int conved_h=(h-kernel_size)/stride+1;
    int conved_w=(w-kernel_size)/stride+1;
    double **conv_pix;
    conv_pix=new double*[conved_h];
    for(int i=0;i<conved_h;i++){
        conv_pix[i]=new double[conved_w];
    }
    for(int i=0;i<conved_h;i++){
        for(int j=0;j<conved_w;j++){
            int index_i;
            int index_j;
            index_i=i*stride;
            index_j=j*stride;
            for(int k=0;k<kernel_size;k++){
                conv(&pix[index_i][index_j],kernel_size,pix_container);
                index_i++;
            }
            conv_pix[i][j]=matmul(pix_container,weight,kernel_size);
            pix_container.clear();
        }
    }
    return conv_pix;
}
