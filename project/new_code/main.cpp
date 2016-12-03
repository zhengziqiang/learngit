#include <QCoreApplication>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;
const int MAX=99999;


int read_data(int &row,int &col,vector <vector <int> > &data,string filename){
    ifstream ifile(filename);
    string line;
    row=0;
    col=0;

    while(getline(ifile,line)){
        //cout<<"原始数据："<<line<<endl;
        istringstream sin(line);
        string field;
        vector <string> ans;
        while(getline(sin,field,',')){
            ans.push_back(field);
            for(int i=0;i<ans.size();i++){
                col+=1;
                if(ans[i]==""){
                    data[row].push_back(MAX);
                }
                else{
                    int m=atoi(ans[i].c_str());
                    data[row].push_back(m);
                }
            }
            row+=1;

        }
        col/=row;
    }
    ifile.close();
    return 0;
}

vector < vector <double> > data_transform(int m,int n,vector <double> data){
    n/=2;
    vector <vector <double> > new_data(m,vector<double>(n,0));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            new_data[i][j]=data[i*m+2*j]*10000+data[i*m+2*j+1];
        }
    }
    return new_data;
}

void write_data(string filename,vector <vector <int> > data,int row,int col){
    ifstream ofile(filename);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            ofile<<data[i][j]<<"\t";
        }
        ofile<<endl;
    }
    ofile.close();
}
int get_data(int row,int col,vector < vector <int > > data){
    return data[row][col];
}

bool is_empty(int row,int col,vector <vector <int> > data){
    if(data[row][col]!=MAX){
        return false;
    }
    else{
        return true;
    }
}

int fun_12(vector <vector <int> > &data){
    return 0;
}

int fun_12(vector <vector <int> > &data){
    return 0;
}

int fun_12(vector <vector <int> > &data){
    return 0;
}

int fun_12(vector <vector <int> > &data){
    return 0;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    vector <vector <int> > pmf_data;
    vector <vector <int> > pmf_data;
    vector <vector <int> > pmf_data;
    vector <vector <int> > pmf_data;
    vector <vector <int> > pmf_data;
    vector <vector <int> > pmf_data;
    vector <vector <int> > pmf_data;
    int pmf_row=0,pmf_col=0;
    int pmf_row=0,pmf_col=0;
    int pmf_row=0,pmf_col=0;
    int pmf_row=0,pmf_col=0;
    int pmf_row=0,pmf_col=0;
    int pmf_row=0,pmf_col=0;
    int pmf_row=0,pmf_col=0;

    string pmf_path="/home/zzq/project/";
    string pmf_path="/home/zzq/project/";
    string pmf_path="/home/zzq/project/";
    string pmf_path="/home/zzq/project/";
    string pmf_path="/home/zzq/project/";
    string pmf_path="/home/zzq/project/";

    read_data(pmf_row,pmf_col,pmf_data,pmf_path);
    read_data(pmf_row,pmf_col,pmf_data,pmf_path);
    read_data(pmf_row,pmf_col,pmf_data,pmf_path);
    read_data(pmf_row,pmf_col,pmf_data,pmf_path);
    read_data(pmf_row,pmf_col,pmf_data,pmf_path);
    read_data(pmf_row,pmf_col,pmf_data,pmf_path);
    read_data(pmf_row,pmf_col,pmf_data,pmf_path);



    return a.exec();
}
