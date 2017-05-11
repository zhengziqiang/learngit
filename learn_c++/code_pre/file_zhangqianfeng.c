/*==============================================================================
    > File Name: file_zhangqianfeng.c
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月08日 星期六 21时18分01秒
 ==========================================================================*/


#include<math.h>
#include<stdlib.h>//程序中用了malloc函数，应包含stdlib.h
#include<stdio.h>
//#include<fstream>
//#include<iostream.h>
int main()
{
 int i=0,j=0,k=0;
 double K1=37.0, K2=76.0, K3=76.8,K4=25.0, K11=0.25 ,K22=0.133, K33=3.013 ;
 double u1=44.0,u2=12.0,u3=32.0,u4=9.0;
 double V1, V2, V3,V4, V11, V22 ,V33;
 double Kv,Kr,Km,Kd,Ksat;
 double Uv,Ur,Um,Ud,Usat;
 double Ro_m; //固体基质的密度
 double fai,p,q,a,E,r,B,pi=3.1415926,p1;
 double *Vp,*Vs;

/*!岩石孔隙度
 k1为石英体积模量，K2为斜长石体积模量，K3为方解石体积模量,K4为粘土体积模量
 u1为石英剪切模量，u2为斜长石剪切模量，u3为方解石剪切模量,u4为方解石剪切模量
 K11为油体积模量，K22为气的体积模量，K33为水的体积模量
 V1：石英的百分含量；V2：斜长石的百分含量；V3：方解石的百分含量 ,V4:粘土的百分含量
 V11：油的百分含量；V22：气的百分含量；V32：水的百分含量
 Km：基质的体积模量,Kv和Kr:由Voigt方程求得；
 Um:基质的剪切模量，Uv和Ur：由Reuss方程求得；
 Kd:干岩石的体积模量
 Ud:干岩石的剪切模量
 Ksat:饱和岩石的体积模量
 Usat:饱和岩石的剪切模量
 P,和Q是与孔隙的形状有关的系数，a是孔隙的纵横比 */

double Ro1=2.65,Ro2=2.63,Ro3=2.71,Ro4=2.55;// ! Ro：密度；1:石英；2：斜长石；3：方解 ;4粘土；
double Ro_11=1.03,Ro_22=0.336,Ro_33=1.055;//! 11:油；22：气；33：水
double Kfl;  //!流体的体积模量
double Ro_fluid,Rsat;//  !流体的密度

Vp=(double *)malloc(sizeof(double)*1000),Vs=(double *)malloc(sizeof(double)*1000);
//开辟动态内存区，降低至转换为double *型，然后放在Vp,Vs中

printf("请输入纵横比a:\n");
scanf("%lf",&a);
for(V1=0.1;V1<=1;V1+=0.1)
  {for(V2=0.1;V2<=1-V1;V2+=0.1)
      {for(V3=0.1;V3<=1-V1-V2;V3+=0.1)
         {for(V4=0.1;V4<=1-V1-V2-V3;V3+=0.1)
           {for(V11=0.1;V11<=1-V1-V2-V3-V4;V11+=0.1)
              {for(V22=0.1;V22<=1-V1-V2-V3-V4-V11;V22+=0.1)
                 {for(V33=0.1;V33<=1-V1-V2-V3-V4-V11-V22;V33+=0.1)
                    if(V1+V2+V3+V4+V11+V22+V33==1)
                    { Kv=K1*V1+K2*V2+K3*V3+K4*V4;
                      Kr=1/(V1/K1+V2/K2+V3/K3+V4/K4);
                      Km=(Kv+Kr)/2;
                      Uv=u1*V1+u2*V2+u3*V3+u4*V4;
                      Ur=1/(V1/u1+V2/u2+V3/u3+V4/u4);
                      Um=(Uv+Ur)/2;
                      Ro_m=Ro1*V1+Ro2*V2+Ro3*V3;
                      fai=V11+V22+V33;
                      Kfl=1/(V11/K11+V22/K22+V33/K33);
                      Ro_fluid=V11*Ro_11+Ro_22*V22+Ro_33*V33;
                      E=Um/6.0*((9*Km+8*Um)/(Km+2*Um));
                      r=Um*(3*Km+Um)/(3*Km+7*Um);
                      B=Um*(3.0*Km+Um)/(3.0*Km+4.0*Um);
                      if(a==1)
                       {
                          p=(Km+(4/3.0)*Um)/(Kfl+(4/3.0)*Um);
                          q=(Um+E)/E;
                       }
                      if(a==0.1)
                       {
                           p=(Km+Um)/(Kfl+Um);
                           q=(4*Um/Um+2*(Um+r)/r+(Kfl+4*Um/3)/(Kfl+Um))/5.0;
                        }
                      if(a==0.01)
                        {
                            p=Km/Kfl;
                            q=(Um+E)/E;
                        }
                      if(a==0.001)
                        {
                            p=(Km+(4/3.0)*Um)/(Kfl+(4/3.0)*Um+pi*a*B);
                            q=(1+8.0*Um/(pi*a*(Um+2.0*B))+2*(Kfl+(2/3)*Um)/(Kfl+pi*a*B))/5.0;
                         }
                       Kd=Km*pow((1-fai),p);
                       Ud=Um*pow((1-fai),q);
                       Ksat=Kd+pow(1-Kd/Km,2)/(fai/Kfl+(1-fai)/Km-Kd/pow(Km,2));
                       Usat=Ud;
                       Rsat=fai*Ro_fluid+(1-fai)*Ro_m;
                       Vp[i++]=sqrt((Ksat+(4.0/3.0)*Usat)/Rsat);
                       Vs[j++]=sqrt(Usat/Rsat);
                       k++;
                    }
                  }
              }
          }
      }
   }
}
for(i=0,j=0;i<k&&j<k;i++,j++)
printf("干岩石的纵波速度:Vp=%.10lf干岩石的横波速度:Vs=%.10lf\n\n",Vp[i],Vs[j]);

FILE *fp=fopen("Vp_Vs.dat","w"); //定义指向FILE类型文件的指针变量,打开VP_Vs.dat文件，以只写的方式，把fopen函数的返回值赋给指针变量fp
if(!fp) {fprintf(fp,"file open error");exit(1);}//exit(1)表示异常结束
for(i=0,j=0;i<k&&j<k;i++,j++)
fprintf(fp,"Vp=%lf,Vs=%lf\n",Vp[i],Vp[j]);
fclose(fp);
return 0;
}
