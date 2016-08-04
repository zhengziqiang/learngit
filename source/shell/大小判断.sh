#########################################################################
# File Name: 大小判断.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: 2016年07月28日 星期四 19时41分50秒
#########################################################################
#!/bin/bash
a=10
b=20
if [ $a == $b] 
	then
	echo "a==b"
elif [ $a -gt $b ] 
	then
	echo "a>b"
elif [ $a -lt $b ] 
	then
	echo "a<b"
else
	echo "impossible"
fi
