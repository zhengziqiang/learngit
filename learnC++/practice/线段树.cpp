/*==============================================================================
    > File Name: 线段树.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月15日 星期二 19时33分06秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
const int MAXNUM = 1000;
struct SegTreeNode
{
    int val;
}segTree[MAXNUM];//定义线段树

/*
功能：构建线段树
root：当前线段树的根节点下标
arr: 用来构造线段树的数组
istart：数组的起始位置
iend：数组的结束位置
*/
void build(int root, int arr[], int istart, int iend)
{
    if(istart == iend)//叶子节点
        segTree[root].val = arr[istart];
    else
    {
        int mid = (istart + iend) / 2;
        build(root*2+1, arr, istart, mid);//递归构造左子树
        build(root*2+2, arr, mid+1, iend);//递归构造右子树
        //根据左右子树根节点的值，更新当前根节点的值
        segTree[root].val = min(segTree[root*2+1].val, segTree[root*2+2].val);
    }
}

/*
功能：线段树的区间查询
root：当前线段树的根节点下标
[nstart, nend]: 当前节点所表示的区间
[qstart, qend]: 此次查询的区间
*/
int query(int root, int nstart, int nend, int qstart, int qend)
{
    //查询区间和当前节点区间没有交集
    if(qstart > nend || qend < nstart)
        return INFINITE;
    //当前节点区间包含在查询区间内
    if(qstart <= nstart && qend >= nend)
        return segTree[root].val;
    //分别从左右子树查询，返回两者查询结果的较小值
    int mid = (nstart + nend) / 2;
    return min(query(root*2+1, nstart, mid, qstart, qend),
               query(root*2+2, mid + 1, nend, qstart, qend));

}

/*
功能：更新线段树中某个叶子节点的值
root：当前线段树的根节点下标
[nstart, nend]: 当前节点所表示的区间
index: 待更新节点在原始数组arr中的下标
addVal: 更新的值（原来的值加上addVal）
*/
void updateOne(int root, int nstart, int nend, int index, int addVal)
{
    if(nstart == nend)
    {
        if(index == nstart)//找到了相应的节点，更新之
            segTree[root].val += addVal;
        return;
    }
    int mid = (nstart + nend) / 2;
    if(index <= mid)//在左子树中更新
        updateOne(root*2+1, nstart, mid, index, addVal);
    else updateOne(root*2+2, mid+1, nend, index, addVal);//在右子树中更新
    //根据左右子树的值回溯更新当前节点的值
    segTree[root].val = min(segTree[root*2+1].val, segTree[root*2+2].val);
}




//全部代码
const int INFINITE = INT_MAX;
const int MAXNUM = 1000;
struct SegTreeNode
{
    int val;
    int addMark;//延迟标记
}segTree[MAXNUM];//定义线段树

/*
功能：构建线段树
root：当前线段树的根节点下标
arr: 用来构造线段树的数组
istart：数组的起始位置
iend：数组的结束位置
*/
void build(int root, int arr[], int istart, int iend)
{
    segTree[root].addMark = 0;//----设置标延迟记域
    if(istart == iend)//叶子节点
        segTree[root].val = arr[istart];
    else
    {
        int mid = (istart + iend) / 2;
        build(root*2+1, arr, istart, mid);//递归构造左子树
        build(root*2+2, arr, mid+1, iend);//递归构造右子树
        //根据左右子树根节点的值，更新当前根节点的值
        segTree[root].val = min(segTree[root*2+1].val, segTree[root*2+2].val);
    }
}

/*
功能：当前节点的标志域向孩子节点传递
root: 当前线段树的根节点下标
*/
void pushDown(int root)
{
    if(segTree[root].addMark != 0)
    {
        //设置左右孩子节点的标志域，因为孩子节点可能被多次延迟标记又没有向下传递
        //所以是 “+=”
        segTree[root*2+1].addMark += segTree[root].addMark;
        segTree[root*2+2].addMark += segTree[root].addMark;
        //根据标志域设置孩子节点的值。因为我们是求区间最小值，因此当区间内每个元
        //素加上一个值时，区间的最小值也加上这个值
        segTree[root*2+1].val += segTree[root].addMark;
        segTree[root*2+2].val += segTree[root].addMark;
        //传递后，当前节点标记域清空
        segTree[root].addMark = 0;
    }
}

/*
功能：线段树的区间查询
root：当前线段树的根节点下标
[nstart, nend]: 当前节点所表示的区间
[qstart, qend]: 此次查询的区间
*/
int query(int root, int nstart, int nend, int qstart, int qend)
{
    //查询区间和当前节点区间没有交集
    if(qstart > nend || qend < nstart)
        return INFINITE;
    //当前节点区间包含在查询区间内
    if(qstart <= nstart && qend >= nend)
        return segTree[root].val;
    //分别从左右子树查询，返回两者查询结果的较小值
    pushDown(root); //----延迟标志域向下传递
    int mid = (nstart + nend) / 2;
    return min(query(root*2+1, nstart, mid, qstart, qend),
               query(root*2+2, mid + 1, nend, qstart, qend));

}

/*
功能：更新线段树中某个区间内叶子节点的值
root：当前线段树的根节点下标
[nstart, nend]: 当前节点所表示的区间
[ustart, uend]: 待更新的区间
addVal: 更新的值（原来的值加上addVal）
*/
void update(int root, int nstart, int nend, int ustart, int uend, int addVal)
{
    //更新区间和当前节点区间没有交集
    if(ustart > nend || uend < nstart)
        return ;
    //当前节点区间包含在更新区间内
    if(ustart <= nstart && uend >= nend)
    {
        segTree[root].addMark += addVal;
        segTree[root].val += addVal;
        return ;
    }
    pushDown(root); //延迟标记向下传递
    //更新左右孩子节点
    int mid = (nstart + nend) / 2;
    update(root*2+1, nstart, mid, ustart, uend, addVal);
    update(root*2+2, mid+1, nend, ustart, uend, addVal);
    //根据左右子树的值回溯更新当前节点的值
    segTree[root].val = min(segTree[root*2+1].val, segTree[root*2+2].val);
}
