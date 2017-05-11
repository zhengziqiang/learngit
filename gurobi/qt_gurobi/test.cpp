#include<iostream>
#include<vector>
#include "gurobi_c++.h"
#include <stdlib.h>
#include <time.h>
#include <sstream>
using namespace std;

bool sub_train(vector <vector <int> > &m_data,vector <vector <int> >&m0_data,vector <vector <int> > aim_data,int n_8_1,int n_6_1,vector<double> &ans){
    GRBEnv env=GRBEnv();
    GRBModel model=GRBModel(env);
    GRBVar vars[n_6_1];
    for(int i=0;i<n_6_1;i++){
        double lower=double(aim_data[i][1]);
        double upper=double(aim_data[i][2]);
        string name;
        stringstream stream;
        stream<<i;
        stream>>name;
        vars[i]=model.addVar(lower,upper,0.0,GRB_INTEGER,name);
    }
    GRBLinExpr con_left;
    GRBLinExpr con_right;
    for(int i=0;i<n_8_1;i++){
        con_right=double(m_data[i][0]);
        con_left=0.0;
        for(int j=1;j<n_6_1+1;j++){
            con_left=con_left+m_data[i][j]*vars[j-1];
        }
        string name;
        stringstream stream;
        stream<<i;
        stream>>name;
        switch(m0_data[i][0]){
            case -1:
            {
            model.addConstr(con_left,GRB_GREATER_EQUAL,con_right,name);
            break;
            }
            case 0:{
            model.addConstr(con_left,GRB_EQUAL,con_right,name);
            break;
            }
            case 1:{
            model.addConstr(con_left,GRB_LESS_EQUAL,con_right,name);
            break;
            }
        default:
            break;
        }
    }
    GRBLinExpr obj = 0.0;
    for(int i=0;i<n_6_1;i++){
        obj+=vars[i];
    }
    model.setObjective(obj,GRB_MINIMIZE);
    model.optimize();
    if(model.get(GRB_IntAttr_Status)!=GRB_OPTIMAL){
        return false;
    }else{
        vector <double>  x(n_6_1,0);
        for(int i=0;i<n_6_1;i++){
            x[i]=vars[i].get(GRB_DoubleAttr_X);
        }
        ans=x;
        return true;
    }
}

//int main(){
//        int n,m;
//        n=5;
//        m=6;
//        int a=1,b=10;
//        int matrix[5][6];
//        for(int i=0;i<n;i++){
//                for(int j=0;j<m;j++){
//                        matrix[i][j]=rand()%10;
//                }
//        }
//        int ans[6];
//        for(int i=0;i<m;i++){
//                ans[i]=rand()%12;
//        }
//        double res=sub(matrix,n,m,ans);
//        cout<<res<<endl;
//        return 0;

//}
