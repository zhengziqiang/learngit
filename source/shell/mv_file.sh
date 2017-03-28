#########################################################################
# File Name: mv_file.sh
# Author: zzq
# mail: zhengziqiang1@gmail.com
# Created Time: 2017年03月28日 星期二 09时30分24秒
#########################################################################
#!/bin/bash
target=/home/zzq/learngit/source/shell/demo
dist=/home/zzq/
cat $target | while read file
do
	mv $file $dist
done
