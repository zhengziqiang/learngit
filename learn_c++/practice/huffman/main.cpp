

/*==============================================================================
    > File Name: 霍夫曼.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com
    > Created Time: 2017年05月23日 星期二 08时28分51秒
 ==========================================================================*/

/*
        代码说明：
  1.读取文件中需进行哈夫曼编码的数据信息
  2.构造生成单节点二叉树组 -> 森林
  3.构造哈夫曼树
  4.进行哈夫曼编码
  5.输出对应数据及其编码
*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int MAX_N = 100;//最大容量
const int INF = 65535;//定义为无穷大

//哈夫曼树节点
class HNode
{
public:
    char data;//节点值
    double weight;//权重
    int parent;//双亲节点
    int lchild;//左孩子节点
    int rchild;//右孩子节点
};

//哈夫曼编码节点
class HuffCode
{
public:
    string code;//数据的编码
    char huffinfo;//被编码数据
};

class HuffMan
{
public:
    HuffMan(){}
    ~HuffMan(){}

    //      函数名：CreateForest
    //      返回值类型：void
    //      参数：string filename
    //      功能：
    //              1.读取文件中数据信息
    //              2.构建单节点二叉树组成的森林
    //
    void CreateForest(string filename)
    {
        int i = 0;
        string str;
        double fdata;
        ifstream readfile;
        readfile.open(filename.c_str(),ios::in);
        //读取被编码数据
        getline(readfile, str);
        for (i = 0; i < (int)str.length(); i++)
        {
            ht[i].data = str[i];
        }//end for -> data for code

        snum = (int)str.length();//被编码数据数量
        //读取被编码数据出现频率
        i = 0;
        while (!readfile.eof())
        {
            if ((readfile >> fdata).good())
            {
                ht[i].weight = fdata;//读数据频率
                i++;
            }//end if -> judge input

        }//end while -> file eof

        readfile.close();
    }

    //      函数名：CreateHuffManTree
    //      返回值类型：void
    //      参数：NULL
    //      功能：利用森林构建哈夫曼树
    //
    void CreateHuffManTree()
    {
        //左右孩子
        int lnode, rnode;
        //最小的两个频率值
        double min1, min2;
        //初始化为-1
        for (int i = 0; i < snum; i++)
        {
            ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
        }//end for -> init result
        //2*n-1
        for (int j = snum; j < 2 * snum - 1; j++)
        {
            //每次调用初始化
            min1 = min2 = INF;
            lnode = rnode = -1;
            //遍历寻找最小的两个频率值min1和min2
            for (int k = 0; k < j; k++)
            {
                //逐一排查不存在双亲节点
                if (ht[k].parent == -1)
                {
                    if (ht[k].weight < min1)//小于最小
                    {
                        min2 = min1;//最小赋值给次小
                        rnode = lnode;//同理下标
                        min1 = ht[k].weight;//新的最小频率值
                        lnode = k;//其下标
                    }//end if -> less

                    //不小于最小，小于次小
                    else if (ht[k].weight < min2)
                    {
                        min2 = ht[k].weight;
                        rnode = k;
                    }//end else if -> only bigger than min1
                    //no else

                }//end if -> search
            }
            ht[j].weight = ht[lnode].weight + ht[rnode].weight;//双亲结点权重
            ht[j].lchild = lnode;//双亲节点左孩子
            ht[j].rchild = rnode;
            ht[lnode].parent = j;//原最小频率值所在节点的双亲节点赋值为当前节点j
            ht[rnode].parent = j;
            ht[j].parent = -1;//双亲节点参与比较，赋值为-1
        }
    }

    //      函数名：CreateHuffCode
    //      返回值类型：bool -> 判断是否编码成功，成功返回true,否则false
    //      功能：生成哈夫曼编码
    //
    bool CreateHuffCode()
    {
        int f, c;
        HuffCode hc;
        for (int i = 0; i < snum; i++)//作为hcode下标
        {
            hc.huffinfo = snum;//从非叶子节点开始
            c = i;//下标->左节点
            f = ht[i].parent;
            while (f != -1)//未到根节点
            {
                if (ht[f].lchild == c)//找到左节点
                {
                    hc.code.assign("0" + hc.code);//左边较小赋值为0

                }//end if -> left node

                else
                {
                    hc.code.assign("1" + hc.code);//右边赋值为1
                }//end else -> right node

                c = f;//替换为上一层节点
                f = ht[f].parent;//上一层的双亲节点
            }//end while

            hc.huffinfo++;
            hcode[i] = hc;//赋值当前编码
            hc.code.clear();//清空code内容，进行下一次访问
        }//end for

        return true;
    }

    //      函数名：display
    //      返回值类型：void
    //      参数：NULL
    //      功能：输出哈夫曼树编码
    //
    void display()
    {
        for (int i = 0; i < snum; i++)
        {
            cout << ht[i].data << ":";//被编码数据
            cout << hcode[i].code << endl;//编码
        }//end for

    }
    void Encode(string ifile_name,string ofile_name){
        ifstream ifile(ifile_name.c_str(),ios::in);
        ofstream ofile(ofile_name.c_str(),ios::out);
        string text;
        while(getline(ifile,text)){
            for(int i=0;i<text.size();i++){
                for(int j=0;j<snum;j++){
                    if(text[i]==ht[j].data){
                        ofile<<hcode[j].code;
                    }
                }
            }
            ofile<<endl;
        }
        ifile.close();
        ofile.close();
    }
    void Decode(string name){
        ifstream ifile(name.c_str(),ios::in);
        string text;
        string str_tmp;
        int first;
        int cnt;
        while(getline(ifile,text)){
            first=0;
            cnt=0;
            for(int i=0;i<text.size()+1;i++){
                str_tmp=text.substr(first,cnt);
                for(int j=0;j<snum;j++){
                    if(str_tmp==hcode[j].code){
                        first=i;
                        cnt=0;
                        cout<<ht[j].data;
                        break;
                    }else{

                        continue;
                    }
                }
                cnt++;
            }
            cout<<endl;
        }
        ifile.close();
    }

private:
    HNode ht[MAX_N];//哈夫曼树
    HuffCode hcode[MAX_N];//编码
    int snum;//总结点数
};

int main()
{
    HuffMan huff;
    huff.CreateForest("/home/zzq/homework/data");//读取待编码数据信息
    huff.CreateHuffManTree();//构建哈夫曼树
    if (huff.CreateHuffCode())//数据编码
    {
        cout << "OK." << endl;
    }//end if -> Create HuffMan Tree's Code

    huff.display();//输出编码
    huff.Encode("/home/zzq/homework/text","/home/zzq/homework/demo");
    huff.Decode("/home/zzq/homework/demo");
    return 0;
}
