#########################################################################
# File Name: welcome_master.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: 2016年07月28日 星期四 19时30分45秒
#########################################################################
#!/bin/bash
test=$(env | grep USER | cut -d "=" -f 2)
echo $test
if [ "$test" == "zzq" ] 
then
				echo "welcome to home ! my master!"
fi
