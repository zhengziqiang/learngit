#include <QCoreApplication>
#include "/home/zzq/gurobi702/linux64/include/gurobi_c++.h"
#include <iostream>
#include "test.cpp"
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int n_8_1=2;
    int n_6_1=3;
    vector <vector <int> > m_data;
    vector <vector <int> > aim_data;
    vector <int> sub(n_6_1,1);
    for(int i=0;i<n_8_1;i++){
        m_data.push_back(sub);
    }
    vector <int> arrange;
    arrange.push_back(1);
    arrange.push_back(1);
    arrange.push_back(10);
    for(int i=0;i<n_6_1;i++){
        aim_data.push_back(arrange);
    }
    vector <double> x_data;
    vector <vector <int> >m0_data(n_8_1,vector<int>(1,0));
    bool has_if=sub_train(m_data,m0_data,aim_data,n_8_1,n_6_1,x_data);
    if(has_if){
        cout<<"there is answer"<<endl;
    }else{
        cout<<"there is no answer"<<endl;
    }
    cout<<"debug"<<endl;
    return a.exec();
}
