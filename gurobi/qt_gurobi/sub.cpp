#include<iostream>
#include<vector>
#include "/home/zzq/gurobi702/linux64/include/gurobi_c++.h"
#include <sstream>
using namespace std;
int sub_train_sub(){
    GRBEnv env=GRBEnv();
    GRBModel model=GRBModel(env);
    vector <double> exam;
    exam.push_back(3.5);
    exam.push_back(4.5);
    GRBVar x=model.addVar(0.0,1.0,0.0,GRB_BINARY,"x");
//The first and second arguments to the addVar() call are the variable lower and upper bounds, respectively. The third argument is the linear objective coefficient (zero here - we'll set the objective later). The fourth argument is the variable type. Our variables are all binary in this example. The final argument is the name of the variable.
    GRBVar y=model.addVar(0.0,1.0,0.0,GRB_BINARY,"y");
    GRBVar z=model.addVar(0.0,1.0,0.0,GRB_BINARY,"z");
    model.setObjective(x + y + 2 * z, GRB_MAXIMIZE);
    //model.setObjective(obj,GRB_MINIMIZE);
    //string constr="x+y >=2";
    //model.addConstr(x + y >= 1, "c1");
    //model.addConstr(constr, "c1");
    int coef[6]={
        1,2,3,1,1,0
    };
    int cnt=0;
    double right[2]={
        4.0,1.0
    };
    for(int i=0;i<2;i++){
    GRBLinExpr con_left=0.0;
    GRBLinExpr con_right=right[i];
    con_left=con_left+coef[cnt+0]*x;
    con_left=con_left+coef[cnt+1]*y;
    con_left=con_left+coef[cnt+2]*z;
    model.addConstr(con_left,GRB_LESS_EQUAL,con_right,"");
    }
    model.optimize();
    cout << x.get(GRB_StringAttr_VarName) << " "
         << x.get(GRB_DoubleAttr_X) << endl;
    cout << y.get(GRB_StringAttr_VarName) << " "
         << y.get(GRB_DoubleAttr_X) << endl;

    cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;
    //另外一种形式
    //GRBLinExpr obj = 0.0;
    //obj += x;
    //obj += y;
    //obj += 2*z;
    //model.setObjective(obj, GRB_MAXIMIZE);
    return 0;
}
//double sub(int matrix[5][6],int n,int m,int ans[6]){
//        GRBEnv env=GRBEnv();
//        GRBModel model=GRBModel(env);
//        GRBLinExpr con_left[n];
//        GRBLinExpr con_right[n];
//        GRBVar vars[m];
//        for(int i=0;i<n;i++){
//                con_left[i]=0.0;
//                con_right[i]=0.0;
//                for(int j=0;j<m;j++){
//                        string name;
//                        stringstream stream;
//                        stream<<j;
//                        stream>>name;
//                        vars[j]=model.addVar(0.0,1.0,0.0,GRB_INTEGER,name);
//                        con_left[i]+=matrix[i][j]*vars[j];
//                }
//                model.addConstr(con_left[i],GRB_EQUAL,con_right[i],"");
//        }
//        GRBLinExpr obj=0.0;
//        for(int i=0;i<m;i++){
//                vars[i]=model.addVar(0.0,1.0,0.0,GRB_INTEGER,"");
//                obj+=ans[i]*vars[i];
//        }
//        model.setObjective(obj, GRB_MAXIMIZE);
//        model.optimize();
//        if(model.get(GRB_IntAttr_Status))

//        double res=model.get(GRB_DoubleAttr_ObjVal);
//        return res;
//}
