/*==============================================================================
    > File Name: matrix.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年05月10日 星期三 22时52分35秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include "gurobi_c++.h"
using namespace std;

int main(){
	GRBEnv env=GRBEnv();
	GRBModel model=GRBModel(env);
	GRBVar x1 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x1");
	GRBVar x2 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x2");
	GRBVar x3 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x3");
	GRBVar x4 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x4");
	GRBVar x5 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x5");
	model.setObjective(x1+x2+x3+x4+x5, GRB_MINIMIZE);
	model.addConstr(x2-x1+x4>=40, "c1");
	model.addConstr(x3-x2+x5>=40, "c2");
	model.optimize();
	cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;
	return 0;
}
