/*==============================================================================
    > File Name: 水池装水问题.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月19日 星期六 17时17分48秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
class solution{
	public:
		int max_area(vector <int> height){
			int max=0;
			int area;
			int left=0;
			int right=height.size()-1;
			while(left<right){
				area=(right-left)*(height[left]<height[right]?height[left]:height[right]);
				max=area>max?area:max;
				if(height[left]<height[right]){
					do{
						left++;
					}
					while(left<right&&height[left-1]>=height[left]);
				}
				else{
					do{
						right--;
					}
					while(right>left&& height[right+1]>=height[right]);
				}
			}
			return max;
		}
};
int main(){
	return 0;
}
