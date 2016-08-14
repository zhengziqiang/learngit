#########################################################################
# File Name: b.sh
# Author: zzq
# mail: zhengziqiang1@gmail.com
# Created Time: 2016年08月09日 星期二 16时04分00秒
#########################################################################
#!/bin/bash
file2=~/todo/shi/ca/label.txt
for j in {1..30}
do
	m=$(($j*569-568))
	n=$(($j*569))
	sed -n "$m,$n p" ${file2} | sort -n >>sortlabel.txt
	j=`expr $j + 1`
done

