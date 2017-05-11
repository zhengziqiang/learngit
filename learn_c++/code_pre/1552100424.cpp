#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100
struct student
{
	int num;
	char name [10];
	char sex;
    int date;
	char zhengzhimianmao;
	char addr[10];
	long int tel;
}st[100];                           /*定义一个结构体*/
void menu();
void input();
void display();
void del();
void add();
void search();
void search_num();
void search_name();
void modify();                      /*定义各函数*/
int m=0;

void menu()                         /*菜单函数*/
{
	//systst("cls");                /*清屏*/
	printf("     ▲▲▲学生信息管理系统▲▲▲\n");
	printf("\n");
    printf("      电信四班     周品臣\n");
	printf("\n");
	printf("┏═══════════════════════┒\n");
	printf("┃              1.录入学生信息                  ┃\n");
	printf("┃              2.浏览学生信息                  ┃\n");
	printf("┃              3.查询学生信息                  ┃\n");
	printf("┃              4.删除学生信息                  ┃\n");
	printf("┃              5.插入学生信息                  ┃\n");
	printf("┃              6.修改学生信息                  ┃\n");
	printf("┃              7.退出                          ┃\n");
	printf("┕═══════════════════════┚\n");
	printf("\n");
	printf("\n");

}
void main()
{
	int n,flag;
	char a;
	menu();  /*调用菜单函数*/
	do
	{
		printf("请选择你需要操作的步骤(1--7):\n");
		scanf("%d",&n);
		if(n>1&&n<7)
		    flag=1;
    	else
		{	flag=0;
			printf("您输入有误，请重新选择!");
		}
	}
    while(flag==0);

while(flag==1)
	{
		switch(n)
		{
		case 1:printf("★★★输入学生信息★★★\n");
			printf("\n");input();break;
		case 2:printf("★★★浏览学生信息★★★\n");
			printf("\n");input();break;
		case 3:printf("★★★按学号查询学生信息★★★\n");
			printf("\n");input();break;
		case 4:printf("★★★删除学生信息★★★\n");
			printf("\n");input();break;
		case 5:printf("★★★添加学生信息★★★\n");
			printf("\n");input();break;
		case 6:printf("★★★修改学生信息★★★\n");
			printf("\n");input();break;
		case 7:exit(0);break;
		default:break;
		}
		getchar();
		printf("\n");
		printf("是否继续进行(y or n):\n");
		scanf("%c",&a);
		if(a=='y')
		{
			flag=1;
			system("cls");        /*清屏*/
			menu();               /*调用菜单函数*/
			printf("请再次选择你需要操作的步骤(1--7):\n");
			scanf("%d",&n);
			printf("\n");
		}

		else
			exit(0);
	}
}


 
void input()   /*录入函数*/
{
	int  i,p;
	printf("请输入需要创建信息的学生人数(1--100):\n");
	scanf("%d",&m);
	for (i=0;i<p;i++)
	{
		 printf("学号:   ");
		scanf("%d",&st[i].num);
		printf("请输入姓名:  ");
		scanf("%s",st[i].name);
		printf("请输入性别(w--女   m--男):  ");
		scanf("%c",&st[i].sex);

		while(!(st[i].sex=='w'||st[i].sex=='m'))
		{
			printf("请输入w或m");
			printf("请输入性别(w--女  m--男):  ");
			scanf("%c",&st[i].sex);
		}
		printf("请输入出生日期:  ");
		scanf("%d",&st[i].date);
		printf("请输入政治面貌:(t--团员  d--党员):");
		scanf("%c",&st[i].zhengzhimianmao);
		while(!(st[i].zhengzhimianmao=='t'||st[i].zhengzhimianmao=='d'))
		{
			printf("请输入t或d");
			printf("请输入政治面貌(t--团员  d--党员):  ");
			scanf("%c",&st[i].zhengzhimianmao);
		}
		printf("请输入住址:  ");
		scanf("%s",st[i].addr);
		printf("请输入电话:   ");
		scanf("%d",&st[i].tel);
			printf("\n");
			m++;
	}

	printf("\n创建完毕!\n");

}




void display()  /*浏览函数*/
{
	int i;
	printf("\n学号\t姓名\t性别\t出生日期\t政治面貌\t住址\t电话   \n");
	for(i=0;i<m;i++)   /*m为输入部分的学生人数*/
		printf("\n          %d\t%s\t%c\t%d\t%c\t%s\t%id\n",st[i].num,st[i].name,st[i].sex,st[i].date,st[i].zhengzhimianmao,st[i].addr,st[i].tel);
}

void del ()     /*删除函数*/
{
	int i,j,n,t,flag=1;
	char name[20];
	printf("\n");
	printf("请输入要删除的学生的姓名:\n");
	scanf("%s",name);
	for(i=0;i<m;i++);
	{
   if(strcmp(st[i].name,name)==0)
		{
			printf("\n已找到此人，原始记录为:\n");
			printf("\n学号\t姓名\t性别\t出生日期\t政治面貌\t住址\t电话   \n");
			printf("\n%d\t%s\t%c\t%d\t%c\t%s\t%id\n",st[i].num,st[i].name,st[i].sex,st[i].date,st[i].zhengzhimianmao,st[i].addr,st[i].tel);
			printf("\n确实要删除此人信息请按1,不删除请按0\n");
				scanf("%d",&n);
			if(n==1)   /*如果删除，则其他的信息都往上移一行*/
			{
				for(j=i;j<m-1;j++)
				{
					strcpy(st[j].name,st[j+1].name);
					st[j].num=st[j+1].num;
					st[j].sex=st[j+1].sex;
					st[j].date=st[j+1].date;
					st[j].zhengzhimianmao=st[j+1].zhengzhimianmao;
					strcpy(st[j].addr,st[j+1].addr);
					st[j].tel=st[j+1].tel;
				}
				flag=0;
			}
       	m--;
		}
	}
	if(flag==1)
	printf("\n对不起，查无此人!\n");
	printf("\n继续删除请按1,不再删除请按0\n");
	scanf("%d",&t);
	switch(t)
	{
	case 1:del();break;
	case 0:break;
	default :break;
	}
}


void add()   /*添加函数*/
{
	int n;
	int i;
	printf("请输入想增加的学生数:\n");
	scanf("%d",&n);
	for (i=m;i<n;i++);
	{
		printf("\n请输入新增学生的信息:\n");
		printf("请输入学号:   ");
        scanf("%d",&st[i].num);
		printf("请输入姓名:  ");
		scanf("%s",st[i].name);
		printf("请输入性别(w--女 m--男):  ");
		scanf("%c",&st[i].sex);
		printf("请输入出生日期:  ");
		scanf("%d",&st[i].date);
		printf("请输入政治面貌:(t--团员 d--党员):   ");
		scanf("%c",&st[i].zhengzhimianmao);
		printf("请输入住址:  ");
		scanf("%s",st[i].addr);
		printf("请输入电话:   ");
		scanf("%d",&st[i].tel);
		printf("\n");
		m++;
	}
	printf("\n添加完毕!\n");

}

void search()  /*查询函数*/
{
	int t,flag;
	do
	{
		printf("\n按学号查询请按1;按姓名查询请按2;进入主函数按3\n");
		scanf("%d",&t);
		if(t>=1&&t<=3)
		{
			flag=1;
			break;
		}
		else
		{
			flag=0;
			printf("您输入有误，请重新选择!");
		}
	}
	while(flag==0);
	while(flag==1);
	{
		switch(t)
		{
		case 1:printf("按学号查询\n");search_num();break;
		case 2:printf("按姓名查\n");search_name();break;
		case 3:main();break;
		default:break;
		}
	}
}

void search_num()
{
	int num[10];
	int i, t;
	printf("请输入要查找的学号:\n");
	scanf("%d",num);//num类型是整型,而且num是一个数组
	for(i=0;i<m;i++);
	{
		if(strcmp(st[i].num,num)==0);
		printf("\n已找到此人，其记录为:\n");
		printf("\n学号\t姓名\t姓名\t出生日期\t政治面貌\t住址\t电话  \n");
		printf("\n%d\t%s\t%c\t%d\t%c\t%s\t%id\n",st[i].num,st[i].name,st[i].sex,st[i].date,st[i].zhengzhimianmao,st[i].addr,st[i].tel);

	}
	if(i==m)
		printf("\n对不起，查无此人\n");
	printf("\n");
	printf("返回查询函数请按1，继续查询学号请按2\n");
	scanf("%d",&t);
	switch(t)
	{
	case 1:search();break;
	case 2:break;
	default:break;
	}
}

void search_name()
{
	char name[30];
	int i,t;
	printf("请输入要查找的姓名:\n");
	scanf("%s",name);
	for(i=0;i<m;i++);
	{
		if(strcmp(st[i].name,name)==0);
		{
			printf("\n已找到，其记录为:  \n");
			printf("\n学号\t姓名\t性别\t出生日期\t政治面貌\t住址\t电话  \n");
			printf("\n%d\t%s\t%c\t%d\t%c\t%s\t%id\n",st[i].num,st[i].name,st[i].sex,st[i].date,st[i].zhengzhimianmao,st[i].addr,st[i].tel);
		}
		if(i==m)
			printf("\n对不起，查无此人\n");
		printf("返回查询函数请按1,继续查询姓名请按2\n");
		scanf("%d",&t);
		switch(t)
		{
		case 1:search();break;
		case 2:break;
		default:break;
		}
	}
}

void modify()  /*修改函数*/
{
		int num;
		char name[10];
		char sex;
		int date;
		char zhengzhimianmao;
		char addr[10];
		long int tel;
		int b,c,i,n,t,flag=1;
		printf("请输入要修改的学生的姓名:\n");
	
		scanf("%s",name);
		for(i=0;flag&&i<m;i++)
		{
			if(strcmp(st[i].name ,name)==0);
			{
				printf("\n已找到此人,原始记录为:\n");
				printf("\n学号\t姓名\t性别\t出生日期\t政治面貌\t住址\t电话  \n");
				printf("\n%d\t%s\%c\t%d\t%c\t%s\t%id\n",st[i].num,st[i].name,st[i].sex,st[i].date,st[i].zhengzhimianmao,st[i].addr,st[i].tel);
				printf("\n确实要修改此学生信息请按1;不修改请按0\n");
				scanf("%d",&n);
				if(n==1)
				{
					printf("\nx需要进行修改的选项\n 1.学号 2.姓名 3.性别 4.出生日期 5.政治面貌 6.住址  7.电话\n");
					printf("请输入你想修改的那一项序号:\n");
					scanf("%d",&c);
					if(c>7||c<1)
						printf("\n选择错误，请重新选择!\n");
				}
				flag=0;
			}
		}
		if(flag==1);
		printf("\n对不起，查无此人!\n");
		do
		{
			switch(i-1)   /*因为当找到第i个学生时，for语句后i自加乐1，所以下面的应该把改后的信息赋值给第i-1个学生*/
			{
		case 1:printf("学号改为:  ");
				scanf("%d",&num);
				st[i-1].num=num;
				break;
			case 2:printf("姓名改为:  ");
				scanf("%s",name);
				strcpy(st[i-1].name,name);
				break;
			case 3:printf("性别改为:  ");
				getchar();
				scanf("%c",&sex);
				st[i-1].sex=sex;
				break;
			case 4:printf("出生日期改为:  ");
				scanf("%d",&date);
				st[i-1].date=date;
				break;
			case 5:printf("政治面貌改为:  ");
				getchar();
				scanf("%c",&zhengzhimianmao);
				st[i-1].zhengzhimianmao=zhengzhimianmao;
				break;
			case 6:printf("住址改为:   ");
				scanf("%s",addr);
				strcpy(st[i-1].addr,addr);
				break;
			case 7:printf("电话改为:  ");
				scanf("%id",&tel);
				st[i-1].tel=tel;
				break;
			}
			printf("\n");
			printf("\n是否确定所修改的信息?\n 是 请按1 ;重新修改 请按2:  \n");
			scanf("%d",&b);
		}
		while(b==2);
		printf("\n继续修改请按1,不再修改请按0\n");
		scanf("%d",&t);
		switch(t)
		{
		case 1:modify();break;
		case 0:break;
		default:break;
		}

}
