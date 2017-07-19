/*==============================================================================
    > File Name: 字典树.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年04月04日 星期二 19时31分13秒
 ==========================================================================*/

#include <iostream>
using namespace std;
#define Max 26
typedef struct node
{
    struct node *next[Max];
    int num;
}Node;
//创建一个新节点
Node *createNew()
{
    Node *p=new Node;
    for(int i=0;i<Max;i++)
    {
        p->next[i]=NULL;
    }
    p->num=0;
    return p;
}
//插入一个字符串
void Insert_str(char str[],Node *head)
{
    int len=strlen(str);
    Node *t,*p=head;
    for(int i=0;i<len;i++)
    {
        int c=str[i]-'a';
        if(p->next[c]==NULL)
        {

            t=createNew();
            p->next[c]=t;
            p->num++;
            //cout<<p->num<<endl;
             p=p->next[c];
        }
        else
        {
            p=p->next[c];
        }
    }
}
int Search_str(char str[],Node *head)
{
    Node *p=head;
    int len=strlen(str);
    int count=0;
    for(int i=0;i<len;i++)
    {
        int c=str[i]-'a';
        if(p->next[c]==NULL)
        {

            cout<<"不存在字符串"<<endl;
            count=0;
            return 0;
        }
        else
        {
            p=p->next[c];
            count=p->num;
        }


    }
    return count;
}
int main()
{
    cout<<"nihao"<<endl;
    Node *head=createNew();
    char s[10];
    while(cin>>s,strcmp(s,"quit"))
    {
        Insert_str(s,head);
    }
    int c=Search_str("abc",head);
    cout<<c<<endl;
    system("pause");


    return 0;
}
