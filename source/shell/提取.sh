#########################################################################
# File Name: 提取.sh
# Author: zzq
# mail: zhengziqiang1@gmail.com
# Created Time: 2016年08月09日 星期二 23时46分39秒
#########################################################################
#!/bin/bash
last=~/todo/shi/ca/last
for j in `seq 569`
do
	for k in `seq 30`
	do
		m=$(($k * 569))
		p=$(($m - 569))
		n=k
		mn=$(($m - $n -$p))
		sed -n "$mn p" ${last} >> hehe
		k=`expr $k + 1`
	done
	j=`expr $j + 1`
done
