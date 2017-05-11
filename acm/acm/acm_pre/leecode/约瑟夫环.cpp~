/*==============================================================================
    > File Name: 约瑟夫环.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月27日 星期二 21时11分33秒
 ==========================================================================*/

// 6.cpp -- using gcc compiler 
#include <iostream>
using namespace std;

typedef struct List
{
    int num;
    struct List *next;
}*pList;

class Josephus
{
    public:
        Josephus() {}
        Josephus(int number, int mes):
            n(number),
            m(mes){}
        void set();
        void creat();
        void del();
    private:
        pList head;
        int n, m, tmp_n;
};

void Josephus::set()
{
    cout << "please input the number of the people: ";
    cin >> n;
    tmp_n = n;
    cout << "please input the m: ";
    cin >> m;
}

void Josephus::creat()
{
    pList p1, p2;
    pList p = new List;
    n += 1;//n+1连成环状
    p -> num = 1;
    p2 = head = p;
    for(int i = 2; i < n; i++)
    {
        p = new List;
        p -> num = i;

        p1 = p2;
        p2 = p;
        p1 -> next = p2;
    }

    p2 -> next = head;
    // output each number of the circle list's members.
    // and it should be: 1, 2, ..., n
    p = head;
    cout << "Now, the \"num\" member of the list is: " << endl;
    while(n--)
    {
        if(n == 0)
            cout << p-> num << ".";
        else
        {
            cout << p->num << ", ";
            p = p -> next;
        }
    }
}

void Josephus::del()
{
    pList p1 = NULL;
    pList p2 = head;

    n = tmp_n + 1;
    while(n--)
    {
        int s = m - 1;
        while(s--)
        {
            p1 = p2;
            p2 = p2 -> next;
        }
        
        if(n == 0)
        {
            p2 = p2 -> next;
            p1 -> next = NULL;
            cout << "The result is: " << p2 -> num << endl;
        }
        else 
        {
            p2 = p2 -> next;
            p1 -> next = p2;
        }
    }
}

int main()
{
    Josephus t;
    t.set();
    t.creat();
    cout << endl;
    t.del();
    return 0;
}
