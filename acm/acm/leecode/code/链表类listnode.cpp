/*==============================================================================
    > File Name: 链表类listnode.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月06日 星期四 14时36分55秒
 ==========================================================================*/

#include<iostream>
using namespace std;
template <Type> class LinkList;
template <Type> class listnode{
	friend class LinkList<Type>;
	private:
		Type data;
		listnode <Type> *next;
	public:
		listnode():next(NULL){

		}
		listnode(Type &e):data(e),next(NULL){

		}
		Type & get_nodedata(){
			return data;
		}
		listnode <Type> *get_ptr(){
			return next;
		}//返回一个节点的指针域
		void set_data(Type &e){
			data=e;
		}
		void set_ptr(listnode<Type> *ptr){
			next=ptr;
		}
};
template <class Type> class LinkList{
	private:
		listnode <Type> *head;
	public:
		LinkList(){
			head=new listnode<Type>();//调用了构造函数
		}
		LinkList<Type>(LinkList<Type> &List);//复制构造函数
		~LinkList(){
			clear();
			delete head;
		}
		void clear();
		int link_length()const;
		listnode<Type> *locate_elem(Type e)const;//返回值是指针
		listnode<Type> *get_elem(int i)const;
		int link_insert(int i,Type &e);
		int link_insertafter(int i,Type &e);
		Type *link_delete(int i);//删除单链表的第i个节点,并将其数据值的地址返回
		listnode <Type> *link_remove(int i);//将单链表的第i个节点取出
		int replace_elem(int i,Type &e);
		listnode <Type> *prior(int i);//前驱
		listnode <Type> *next(int i);//后驱
		bool is_empty(void);
		LinkList <Type> & operator = (LinkList <Type> &list);
};
//复制构造函数
template <class Type> LinkList<Type>::LinkList<Type>(LinkList <Type> &list){
	head = new listnode<Type>();//listnode 的拷贝构造函数
	listnode <Type> *p=list.head->next,*q=head,*s;
	while(p){
		s=new listnode<Type>;
		s->data=p->data;
		q->next=s;
		q=s;
		p=p->next;
	}
	q->next=NULL;
}
//置为空表的函数
template <class Type> void LinkList<Type>::clear(){
	lisnode <Type> *p;
	while(head->next!=NULL){
		p=head->next;
		head->next=p->next;
		delete p;
	}
}
//返回单链表第i个节点的地址
template <class Type>listnode <Type> *LinkList<Type>::get_elem(int i)const{
	if(i<0)
		return NULL;
	if(i==0)
		return head;
	istnode <Type> *p=head->next;
	int j=1;
	while(p&&j<i){
		p=p->next;
		j++;
	}
	return p;
}
//计算单链表的长度
template <class Type >int LinkList<Type>::link_length()const{
	listnode <Type> *p=head->next;
	int count=0;
	while(p){
		p=p->next;
		count++;
	}
	return count;
}
//重载赋值运算符
template<class Type>
LinkList<Type>& LinkList<Type>::operator = (LinkList <Type> &list){
	if(this==&list)
		return *this;
	clear();
	listnode<Type> *p=list.head->next,*q=head,*s;
	while(p){
		s=new listnode<Type>;
		s->data=p->data;
		q->next=s;
		q=s;
		p=p->next;
	}
	q->next=NULL;
	return *this;
}
//插入数据
template <class Type> int LinkList<Type>::link_insert(int i,Type &e){
	listnode <Type> *p=get_elem(i-1);
	if(!p)
		return 0;
	listnode <Type> *s=new listnode<Type> (e);
	s->next=p->next;
	p->next=s;//并没有后移,只是插入了一个节点
	return 1;
}
//在节点之后插入
template <class Type> int LinkList<Type>::link_insertafter(int i,Type &e){
	listnode <Type> *p =get_elem(i);
	if(!p)
		return 0;
	listnode<Type> *s=new listnode<Type>(e);
	s->next=p->next;
	p->next=s;
	return 1;
}
//删除一个节点
template <class Type>Type *LinkList<Type>::link_delete(int i){
	listnode<Type> *s,*p=get_elem(i-1);
	if(!p||p->next=NULL)
		return NULL;
	s=p->next;
	p->next=s->next;
	Type *ptr=new Type(s->data);//取出已删除节点的数据值
	delete s;
	return ptr;
}
//融合两个
template <class Type>
void connect(LinkList<Type> &la,LinkList<Type> &lb){
	listnode <Type> *p=la.get_elem(1);
	while(p->get_ptr())
		p=p->ger_ptr();
	p->set_ptr(lb.get_elem(1));
	p=lb.get_elem(0);
	p->set_ptr(NULL);
}
//融合为一个
template<class Type>
void merge<LinkList <Type> &la,LinkList <Type> &lb,LinkList <Type> &lc){
	listnode <Type> *pa,*pb,*pc;
	pa=la.get_elem(1);
	pb=lb.get_elem(1);
	pc=lc.get_elem(0);
	while(pa&&pb){
		if(pa->get_nodedata()<=pb->get_nodedata()){
			pc->set_ptr(pa);
			pc=pa;
			pa=pa->get_ptr();
		}
		else{
			pc->set_ptr(pb);
			pc=pb;
			pb=pb->get_ptr();
		}
	}
	pc->set_ptr(pa?pa:pb);
	pa=la.get_elem(0);
	pb=lb.get_elem(0);
	pa->set_ptr(NULL);
	pb->set_ptr(NULL);
}
//循环列表
template <class Type> class Cirlist{
	private:
		listnode <Type> *head;
	public:
		Cirlist(){
			head=new listnode<Type>();
			head->next=head;
		}
		~Cirlist(){
			clear();
			delete head;
		}
		void clear();
		listnode <Type> *next_elem(listnode <Type> *p=NULL);
		listnode <Type> *cir_remove(listnode <Type> *p);
};
template <class Type> void Cirlist<Type>::clear(){
	listnode< Type> *p;
	while(head->next!=head){
		p=head->next;
		head->next=p->next;
		delete p;
	}
}
template <class Type>
listnode<Type> *next_elem(listnode<Type> *p){
	if(p==NULL){
		return head;
	}
	listnode <Type> *q=p->next;
	if(q==head){
		q=q->next;
	}
	return q;
}
teplate <class Type> listnode<Type>*cir_remove(listnode <Type> *p){
	listnode <Type> *q=p->next;
	if(q==head){
		q=q->next;
		head->next=q->next;
	}
	else{
		p->next=q->next;
	}
	return q;
}
