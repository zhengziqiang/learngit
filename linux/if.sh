#########################################################################
# File Name: if.sh
# Author: zhengziqiang
# mail: 1174986943@qq.com
#Created Time:2016年05月01日 星期日 22时08分02秒
#########################################################################
#!/bin/bash
test=$(env | grep USER | cut -d "=" -f 2)
echo $test
if [ "$test" == "zzq" ]
		then
				echo "welcome to home ! my master!"
fi
