#########################################################################
# File Name: rm.sh
# Author: zzq
# mail: zhengziqiang1@gmail.com
# Created Time: 2016年09月11日 星期日 18时11分29秒
#########################################################################
#!/bin/bash
ls -l | awk '$1~/x/{print $NF}' | xargs rm
