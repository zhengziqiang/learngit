#!/bin/sh
# Ping网段所有IP
# 2012/02/05
ipStart=101 #开始ip
ipEnd=120 #结束ip
ipNet="192.168.1"
output=log
ip=$ipStart
while [ $ip -le $ipEnd ]; do
#yes正常，no主机不存在或不正常
#echo $ipNet.$ip
#分号间隔不同的命令,又先后顺序
ping -c 2 $ipNet.$ip | grep -q "ttl=" && (echo "$ipNet.$ip yes";echo "$ipNet.$ip yes" >> $output;./serverExpect.sh $ipNet.$ip) || (echo "$ipNet.$ip no";echo "$ipNet.$ip no">>$output)
ip=`expr "$ip" "+" "1"`
done
