/*==============================================================================
    > File Name: 方法.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年02月14日 星期二 21时50分14秒
 ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>

void printMatrix(int*a, int m, int n);

/*
 * Dynamic Programming
 *
 * We have a dp[i][j] represents  how many paths from [0][0] to hear. So, we have the following DP formuler:
 *
 *    dp[i][j] =  1  if i==0 || j==0        //the first row/column only have 1 uniqe path.
 *             =  dp[i-1][j] + dp[i][j-1]   //the path can be from my top cell and left cell.
 */
int uniquePaths(int m, int n) {
    int* matrix = new int[m*n];
    printMatrix(matrix, m, n);
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            if(i==0 || j==0){
                matrix[i*n+j]=1;
            }else{
                matrix[i*n+j] = matrix[(i-1)*n+j] + matrix[i*n+j-1];
            }
        }
    } 
    printMatrix(matrix, m, n);
    int u = matrix[m*n-1];
    delete[] matrix;
    return u;
}

void printMatrix(int*a, int m, int n)
{
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            printf("%4d ", a[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    int m=3, n=7;
    if( argc>2){
        m = atoi(argv[1]);
        n = atoi(argv[2]);
    }

    printf("uniquePaths=%d\n", uniquePaths(m,n));
    return  0;
}
