/*==============================================================================
    > File Name: intersection_of_two.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 23时06分21秒
 ==========================================================================*/

#include<iostream>
using namespace std;
class solution{
	public:
		ListNode *get_intersection(ListNode *heada,ListNode *headb){
			if(!heada){
				return NULL;
			}
			else if(!headb){
				return NULL;
			}
			ListNode *p=heada;
			while(p->next){
				p=p->next;
			}
			p->next=headb;
			ListNode *tail=p;
			p=heada;
			headb=heada;
			while(headb->next&&headb->next->next){
				heada=heada->next;
				headb=headb->next->next;
				if(heada==headb){
					break;
				}
			}
			if(!heada->next||!headb->next||!headb->next->next){
					tail->next=NULL;
					return NULL;
			}
			head = p;
			while(heada!=headb){
				heada=heada->next;
				headb=headb->next;
			}
			tail->next=NULL;
			return heada;
		}
};
int main(){
	return 0;
}
