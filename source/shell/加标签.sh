#########################################################################
# File Name: 加标签.sh
# Author: zzq
# mail: zhengziqiang1@gmail.com
# Created Time: 2016年08月02日 星期二 13时40分06秒
#########################################################################
#!/usr/bin/env sh
echo "creating val.txt"
rm -rf path.txt
j=0
for dirname in `ls -F | grep /$`
do
	for filename in `find ${dirname} -type f -name 



