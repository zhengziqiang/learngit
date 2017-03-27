#########################################################################
# File Name: cat_while.sh
# Author: zzq
# mail: zhengziqiang1@gmail.com
# Created Time: 2017年03月16日 星期四 19时40分40秒
#########################################################################
#!/bin/bash
file1=/home/zzq/learngit/source/shell/target
file2=/home/zzq/learngit/source/shell/all_file
file3=/home/zzq/learngit/source/shell/output
cat ${file1} | while read image_name
do
	grep -w ${image_name} ${file2} >> ${file3}
done
echo "Done"
