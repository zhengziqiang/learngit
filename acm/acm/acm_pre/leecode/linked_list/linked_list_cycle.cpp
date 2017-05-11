/*==============================================================================
    > File Name: linked_list_cycle.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 22时52分23秒
 ==========================================================================*/

#include<iostream>
#include<ListNode.h>
using namespace std;
class solution{
	public:
		bool has_cycle(ListNode *head){
			if(head ==NULL|| head->next==NULL){
				return false;
			}
			ListNode *fast=head;
			ListNode *slow=head;
			while(fast->next!=NULL&&fast->next->next!=NULL){
				fast=fast->next->next;
				slow=slow->next;
				if(slow==fast){
					return true;
				}
			}
			return false;
		}


		ListNode *detect_cycle(ListNode *head){
			if(head==NULL||head->next==NULL){
				return NULL;
			}
			ListNode *fast=head;
			ListNode *slow=head;
			while(fast->next!=NULL&&fast->next->next!=NULL){
				fast=fast->next->next;
				slow=slow->next;
				if(fast==slow){
					slow=head;
					while(slow!=fast){
						fast=fast->next;
						slow=slow->next;
					}
					return slow;
				}
			}
			return NULL;
		}
};
int main(){
	return 0;
}
