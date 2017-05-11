/*==============================================================================
    > File Name: example_c++.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年05月09日 星期二 20时57分23秒
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
	GRBVar x6 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x6");
	GRBVar x7 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x7");
	GRBVar x8 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x8");
	GRBVar x9 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x9");
	GRBVar x10 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x10");
	GRBVar x11 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x11");
	GRBVar x12 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x12");
	GRBVar x13 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x13");
	GRBVar x14 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x14");
	GRBVar x15 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x15");
	GRBVar x16 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x16");
	GRBVar x17 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x17");
	GRBVar x18 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x18");
	GRBVar x19 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x19");
	GRBVar x20 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x20");
	GRBVar x21 = model.addVar(0.0, 200.0, 0.0, GRB_INTEGER, "x21");
	model.setObjective(x1+x2+x3+x4+x5+x6+x7+x8+x9+x10+x11+x12+x13+x14+x15+x16+x17+x18+x19+x20+x21, GRB_MINIMIZE);
	model.addConstr(x4-x1+x10>=35, "c1");
	model.addConstr(x7-x4+x11>=25, "c2");
	model.addConstr(x5-x2+x12>=35, "c3");
	model.addConstr(x8-x5+x13>=25, "c4");
	model.addConstr(x6-x3+x14>=35, "c5");
	model.addConstr(x9-x6+x15>=25, "c6");
	model.addConstr(x2-x1+x16>=40, "c7");
	model.addConstr(x3-x2+x17>=40, "c8");
	model.addConstr(x5-x4+x18>=30, "c9");
	model.addConstr(x6-x5+x19>=30, "c10");
	model.addConstr(x8-x7+x20>=25, "c11");
	model.addConstr(x9-x8+x21>=25, "c12");
	model.optimize();
	cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;
	return 0;
}
