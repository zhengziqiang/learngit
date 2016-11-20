/*==============================================================================
    > File Name: 前序和中序重建二叉树.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月19日 星期六 16时53分25秒
 ==========================================================================*/


/**/

//定义树的长度
#define TREELEN 6
#include<iostream>
using namespace std;

struct Node
{
    struct Node* pLeft;
    struct Node* pRight;
    char value;
};

void Rebuild(char *pPreOrder,//前序遍历结果
             char *pInorder,//中序遍历结果
             int nTreeLen,//树的长度
             Node **pRoot)//根节点
{
    //检查边界条件
    if(pPreOrder==NULL ||pInorder==NULL)
    {
        return ;
    }
    //获得前序遍历的第一个结点
    Node *pt=new Node ;
    pt->value=*pPreOrder;
    pt->pLeft=NULL;
    pt->pRight=NULL;
    //如果根节点为空，将该节点设置为根节点，首次会调用
    if(*pRoot==NULL)
    {
        *pRoot=pt;
    }
    //如果深度为1，那么已经是叶节点了
    if(nTreeLen==1)
    {
        return;
    }
    //在中序遍历中寻找左子树
    char *pOrgInOrder=pInorder;
    char *pLeftEnd=pInorder;
    int ntemp=0;
    //找到左子树的结尾
    while(*pPreOrder!=*pLeftEnd)
    {
        if(pPreOrder==NULL||pLeftEnd==NULL)
        {
            return;
        }
        ntemp++;
        if(ntemp>nTreeLen)
        {
            return;
        }
        pLeftEnd++;
    }
    //确定左子树的长度
    int nLeftLen=0;
    nLeftLen=(int)(pLeftEnd-pOrgInOrder);
    //确定右子树的长度
    int nRightLen=0;
    nRightLen=nTreeLen-nLeftLen-1;
    
    //重建左子树
    if(nLeftLen>0)
    {
        Rebuild(pPreOrder+1,pInorder,nLeftLen,&((*pRoot)->pLeft));
    }
    //重建右子树
    if(nRightLen>0)
    {
        Rebuild(pPreOrder+nLeftLen+1,pInorder+nLeftLen+1,nRightLen,&((*pRoot)->pRight));
    }
}

int main()
{
    char PreOrder[]={'a','b','d','c','e','f'};
    char InOrder[]={'d','b','a','e','c','f'};
    Node *root=NULL;
    Rebuild(PreOrder,InOrder,TREELEN,&root);
}
