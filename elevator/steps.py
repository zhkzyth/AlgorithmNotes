#!/usr/bin/env python
# encoding: utf-8

# 递归求解算法，自顶向上
# f(n) = f(n-1) + f(n-2) , 其中，f(1) = 1, f(0) = 1
# 如果觉得费解，只要把这里的走法和走的次数两个概念区分开就可以了

# You are climbing a stair case. It takes n steps to reach to the top.
# Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
# Note: Given n will be a positive integer.
# Subscribe to see which companies asked this question

class Solution(object):

    def climbStairs(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 0 || n == 1:
            return 1

        return climbStairs(n-1) + climbStairs(n-2)


# # 动态规划算法，自底向上
# class Solution(object):

#     def climbStairs(self, n):
#         """
#         :type n: int
#         :rtype: int
#         """
#         # if n == 0 || n == 1:
#         #     return 1

#         # return climbStairs(n-1) + climbStairs(n-2)

#         if n == 0:
#             return 1

#         result = []

#         result.append(1)

#         if n >= 2 :
#             result.append(2)

#         for i in range(2, n) :

#             result.append(result[i-1] + result[i-2])

#         return result[n-1]


# 矩阵算法（把问题化归成矩阵进行计算）
