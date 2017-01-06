#!/usr/bin/env python
# encoding: utf-8

# TODO 暂时还没完全理解这个算法
# 扩展概念，如果放到1~m步来看

# 从每步1～2级阶梯到1～m级阶梯，需要改变的不仅仅只是步长，还有每步走完之后，对剩余台阶总数的判断。
# 当总剩余的台阶数n大于步长m的时候，则第一步为1～m的一个数值，循环递归求解可能的走法。
# 如果总剩余台阶数n小于步长m的时候，则步长调整为n，递归求解。
# 具体代码如下:

public class Solution {

    @param n: 总的台阶数
    @param m: 每次可以走的最大的阶数
    @return: 一共有多少种可能的走法
    public int climbStairs(int n, int m) {

        int stepsCount = 0;

        # // TODO 思考这里的台阶数为0的时候表示已经走完
        # 为什么n==1的时候，不在这里进行判断呢
        # if (n == 0 || n == 1) {
        #     return 1;
        # }

        # // 台阶数为0的时候表示已经走完
        if (n == 0) {
            return 1;
        }

        # // 当总剩余的台阶数n大于步长m的时候，则
        # // 第一步为 1～m的一个数值，循环递归求解可能的走法
        if (n >= m) {

            for (int i = 1; i <= m; i++) {
                stepsCount += climbStairs(n-i, m);
            }

        } else {

            // 如果总剩余台阶数n小于步长m的时候，则 步长为n，递归求解。
            stepsCount += climbStairs(n, n);

        }

        return stepsCount;
    }
}
