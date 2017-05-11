/*==============================================================================
    > File Name: remove_duplicate.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月30日 星期五 11时35分44秒
 ==========================================================================*/

#include<iostream>
#include<ListNode>
using namespace std;
class solution{
	public:
		ListNode *delete_duplicate(ListNode *head){
			if(!head){
				return head;
			}
			int val= head->val;
			ListNode *p=head;
			while(p&&p->next){
				if(p->next->val!=val){
					val=p->next->val;
					p=p->next;
				}
				else{
					ListNode *n=p->next->next;
					p->next=n;
				}
			}
			return head;
		}
};
int main(){
	return 0;
}
