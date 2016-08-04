#########################################################################
# File Name: 提取文件.sh
# Author: zzq
# mail: zhengziqiang1@gmail.com
# Created Time: 2016年07月28日 星期四 20时29分12秒
#########################################################################
#!/bin/bash
grep "accuracy" log.txt | awk '{print $11}' >acc.txt
#将accuracy写入到acc.txt中。
awk 'NR%2==1' acc.txt>top1.txt
#将奇数行的正确率提取到top1中
awk 'NR%2==0' acc.txt>top5.txt
#将偶数行的正确率提取到top5中
