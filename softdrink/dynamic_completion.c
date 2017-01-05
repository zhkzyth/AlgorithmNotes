// TODO 再仔细研读下这块

#include<iostream>
#include<memory.h>
using namespace std;

/**
 * W：饮料总容量的最大上限；N：饮料的种类；C：每种饮料的个数；H：每种饮料的满意度；V：每种饮料的容量
 * 求：在满足最大容量<=W的前提下，如何购买饮料获得的满意度最大
*/
int Cal(int W,int N,int* C,int* H,int* V)
{
	if(W <=0 || N<=0 || C== NULL|| H==NULL || V==NULL)
    return 0;

	int i,j,k;
	int** dp = new int* [N+1];

	for(i=0;i<=N;i++)
	{
		dp[i] = new int[W+1];
	}

	memset(dp[N], 0, sizeof(int)*(W+1));

	for(i=N-1;i>=0;i--) // 遍历每一种饮料
	{

    // 遍历当前饮料，装满最大容量的情况下，满意度的可能性
		for(j=1;j<=W;j++)
		{

			dp[i][j] = 0;

      // 遍历当前饮料可能的最大个数
			for(k=0; k<=C[i]; k++)
			{
				if(j >= k*V[i]) // 如果当前组合没有超过限制范围
				{
					dp[i][j] = max(dp[i][j], dp[i+1][j-k*V[i]]+k*H[i]);
				}
				else break;
			}
		}
	}

	int res = dp[0][W];

	for(i=0;i<=N;i++)delete[] dp[i];

	delete[] dp;

	return res;
}

int main()
{
	int w,n,i;
	while(cin >> w >> n)
	{
		int* C = new int[n];
		int* H = new int[n];
		int* V = new int[n];
		for(i=0;i<n;i++) cin >> C[i] >> H[i] >> V[i];
		cout << Cal(w,n,C,H,V)<< endl;
		delete[] C;
		delete[] H;
		delete[] V;
	}
	return 0;
}
