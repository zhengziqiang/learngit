#########################################################################
# File Name: 时.sh
# Author: zzq
# mail: zhengziqiang1@gmail.com
# Created Time: 2016年08月09日 星期二 15时31分27秒
#########################################################################
#!/bin/bash
file=~/todo/shi/ca/label.txt
i=2
j=3
m=$(($i*$j))
n=$(($j*$j))
sed -n "${m},$n p" ${file}
