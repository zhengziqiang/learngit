#########################################################################
# File Name: duipai.sh
# Author: zzq
# mail: zhengziqiang1@gmail.com
# Created Time: 2016年11月10日 星期四 14时03分36秒
#########################################################################
#!/bin/bash  
while(true)do  
./rand
/usr/bin/time -f "%Us" ./Brute  
/usr/bin/time -f "%Us" ./Out  
diff ans out > null  
if ([ $? -eq 0 ]); then  
printf "\033[7;32mAccepted!!!\n\033[7;0m"  
else  
printf "\033[7;31mWrong Answer!\033[7;0m\n"  
break  
fi  
sleep 1  
done  
