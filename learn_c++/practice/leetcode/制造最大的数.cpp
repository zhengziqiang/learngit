/*==============================================================================
    > File Name: 制造最大的数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月20日 星期日 19时37分48秒
 ==========================================================================*/

/*************************************************************************************** 
 *
 * Given two arrays of length m and n with digits 0-9 representing two numbers.
 *     Create the maximum number of length k  from digits of the two. The relative 
 * order of the digits
 *     from the same array must be preserved. Return an array of the k digits. You 
 * should try to optimize your time and space complexity.
 * 
 *     Example 1:
 * 
 *     nums1 = [3, 4, 6, 5]
 *     nums2 = [9, 1, 2, 5, 8, 3]
 *     k = 5
 *     return [9, 8, 6, 5, 3]
 * 
 *     Example 2:
 * 
 *     nums1 = [6, 7]
 *     nums2 = [6, 0, 4]
 *     k = 5
 *     return [6, 7, 6, 0, 4]
 * 
 *     Example 3:
 * 
 *     nums1 = [3, 9]
 *     nums2 = [8, 9]
 *     k = 3
 *     return [9, 8, 9]
 * 
 * Credits:Special thanks to @dietpepsi for adding this problem and creating all test 
 * cases.
 ***************************************************************************************/



/*
 * Solution
 * --------
 * 
 * 1) We split the `K` to two parts : `i` & `k-i`  0<= i <= k
 * 
 * 2) Find the max number for both arrays with giving the length `i` and `k-i`
 *      - sub1 = FindMaxNumber(num1, len=i);
 *      - sub2 = FindMaxNumber(num2, len=k-i);
 *    Here, we need use stack-way to solve find the max number.
 * 
 * 3) Merge two arrays 
 *      - solution = Merge(sub1, sub2);
 *    Here, we need be careful if a two number are same which one we need to take.  For examples: 
 *      [6,7]
 *      [6,0,4]
 *      5
 *      
 *      [2,5,6,4,4,0]
 *      [7,3,8,0,6,5,7,6,2]
 *      15
 * 
 * 4) compare with the last solution
 *     - result = max(result, solution); 
 * 
 * 
 */
#include<iostream>
#include<vector>
using namespace std;

