#########################################################################
# File Name: shell.sh
# Author: zzq
# mail: zhengziqiang1@gmail.com
# Created Time: 2016年08月09日 星期二 14时10分41秒
#########################################################################
#!/usr/bin/env
file=~/todo/shi/ca/cancer
file2=~/todo/shi/ca/label.txt
rm -rf sortlabel.txt
for i in `seq 32`
do
	cat ${file} | cut -d , -f ${i} >>label.txt
	i=`expr $i + 1`	
done
for j in `seq 32`
do
	sed -n "$((${j}*569-568)),$(($j*569))p" ${file2} | sort -n >>sortlabel.txt
	j=`expr $j + 1`
done
