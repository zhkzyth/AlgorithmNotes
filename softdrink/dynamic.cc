// 使用动态规划算法来解决饮料满意度的问题，代码思路


// 参数说明：
// 用(Si、Vi、Ci、Hi、Bi)（对应饮料名字、容量、可能的最大数量、满意度、实际购买量）来表示第i种饮料（i=0,1,...,n-1）
// T表示目前有多少种饮料可以供选择的

int Cal(int V, int type) {

  opt[0][T] = 0; // 边界条件

  // 边界条件
  for(int i = 1; i<= V; i++) {
    opt[i][T] = -INF;
  }

  for(int j = T - 1; j >= 0; j--) {

    for(int i=0;i<=V;i++) {

      opt[i][j] = -INF;

      for(int k=0;k<=C[j];k++) { // 遍历第j种饮料选取数量k

        if(i<=k*V[j]) {
          break;
        }

        int x = opt[i - k * V[j]][j+1];

        if(x != -INF) {

          x += H[j] * k;
          if(x > opt[i][j]) {
            opt[i][j] = x;
          }

        }

      }

    }

  }

  return opt[V][0];
}
