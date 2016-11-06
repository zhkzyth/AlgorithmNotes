#!/usr/bin/env python
# encoding: utf-8

"""
问题： 星期五的晚上，一帮同事在希格玛大厦附近的“硬盘酒吧”多喝了几杯。程序员多喝了几杯之后谈什么呢？自然是算法问题。有个同事说：“我以前在餐馆打工，顾客经常点非常多的烙饼。店里的饼大小不一，我习惯在到达顾客饭桌前，把一摞饼按照大小次序摆好——小的在上面，大的在下面。由于我一只手托着盘子，只好用另一只手，一次抓住最上面的几块饼，把它们上下颠倒个个儿，反复几次之后，这摞烙饼就排好序了。我后来想，这实际上是个有趣的排序问题：假设有n块大小不一的烙饼，那最少要翻几次，才能达到最后大小有序的结果呢？” 你能否写出一个程序，对于n块大小不一的烙饼，输出最优化的翻饼过程呢？

分析：
- 本质上，这是一个前缀排序翻转算法
- 在laobin.py算法里面，因为没有重用数据结构，在量大的情况下，因为盲搜带来的空间浪费还是蛮可观的。另外，基于dfs的盲搜，即使采用了upperbond和lowerbond来剪枝，还是有改进的空间。
- 拜读了网上的一些文章后，发现在树空间的前提下，还有很多搜索的策略可以用。
- 因为编程能力和时间的考虑，暂时先用爬山算法再写一次，同时采用公共数据结构，避免不必要的浪费。

参考：
- https://site.douban.com/161134/widget/works/8500866/chapter/18557459/
- http://www.cnblogs.com/TenosDoIt/p/3250742.html
- http://blog.csdn.net/solomon1558/article/details/44226997

备注：
- 爬山法的实现有点难，还是先放着，后面再回头来写吧，一整天都在消化这个=。=
- laobin_recursion_better.c里面，用了一个比较简单的node结构，以及基于子集本身的有序性算分的机制，进一步的把dfs的搜索策略优化了，往最容易找到结果集的子空间去探索。
- 用python实现一个

输入限制：
- 至少两个元素的数组
"""
import sys
import json

__original_author__ = 'DELL'


class Node:

    def __init__(self, index=None, score=None):
        self.score = score
        self.index = index


def release_all():
    m_cake_list = None
    m_swap_list = None
    m_reverse_list = None
    m_reverse_swap_list = None

    m_cake_count = 0
    m_max_swap = 0 # the max swap count we have met
    m_search = 0  # 当前搜索次数信息


def init(cake_list):
    """
    """
    global m_cake_count, m_reverse_list
    global m_cake_list, m_max_swap, m_reverse_swap_list, m_swap_list

    m_cake_count = n = len(cake_list)

    m_max_swap = cal_upper_bound(n)

    m_cake_list = cake_list[:]
    m_reverse_list = cake_list[:]

    m_reverse_swap_list = ["" for i in range(0, m_max_swap+1)] # TODO 为什么这里要加1 ; 因为要给多走一步step判断用
    m_swap_list = ["" for i in range(0, m_max_swap)]


# TODO upper bound 的次数还可以再缩减
def cal_upper_bound(cake_count):
    return 2 * cake_count - 3


# 假定都是从0开始，把后面特定某个位置的元素翻转到一个位置来
def swap(end):
    """
    """
    global m_reverse_list

    cake_list = m_reverse_list

    for i in range(0, end/2 + 1):
        temp = cake_list[i]
        cake_list[i] = cake_list[end - i]
        cake_list[end - i] = temp


def is_sorted(cakes):
    """
    """
    for i in range(0, len(cakes) - 1):
        if cakes[i] > cakes[i+1]:
            return False
    return True


def cal_lower_bound(cake_list):
    """
    """
    t = ret = 0

    for i in range(1, len(cake_list)):

        t = cake_list[i] - cake_list[i-1]
        if t not in (1,-1):
            ret = ret + 1

    if cake_list[len(cake_list) - 1] != len(cake_list) -1 :

        ret = ret + 1

    return ret


def cal_list_score(child):
    """
    """

    # total_distance = 0

    # for k,e in reversed(list(enumerate(child))):

    #     if k == 0:
    #         break

    #     if k == child[k]:
    #         continue

    #     distance = abs(child[k] - child[k-1])
    #     if distance == 1:
    #         continue

    #     total_distance = total_distance + 1

    # return total_distance




def search(step=0, end=0):
    """
    """

    global m_search, m_max_swap, m_reverse_list
    global m_swap_list, m_reverse_swap_list, m_cake_count
    global m_flag

    n_estimate = 0
    m_search = m_search + 1

    n_estimate = cal_lower_bound(m_reverse_list)
    if step + n_estimate >= m_max_swap:
        print "opps~exceed max swap.step({step})/n_estimate({n_estimate})/max_swap({max_swap})".format(step=step,
                                                                                                       n_estimate=n_estimate,
                                                                                                       max_swap=m_max_swap)
        return False

    k = end
    while k > 0 and k == m_reverse_list[k]:
        k = k - 1

    if k == 0:
        # if is_sorted(m_reverse_list):
        if step < m_max_swap:
            m_max_swap = step
            for k in range(0, m_max_swap):
                m_swap_list[k] = m_reverse_swap_list[k]

        elif step == m_max_swap and m_flag == False:
            # 只记录第一组找到的最小swap_list，同时避免m_max_swap就是step的情况，比如输入一个只有1个元素的数组
            m_max_swap = step
            m_flag = True
            for k in range(0, m_max_swap):
                m_swap_list[k] = m_reverse_swap_list[k]

        return True

    node_set = []

    # 构造最佳子集
    # TODO 这里的交换次数分数，依据是什么呢？
    #  TODO 基础分数是从cal_lower_bound算出来的，所以要减掉的话，应该从那里加出来来分析
    # TODO 太晚了，先睡觉
    for i in range(1, k+1):
        node = Node()
        node.index = i
        node.score = n_estimate

        # 这里的计算还可以再优化，算法的出发点要多读几遍原文去理解哈=）
        if i != m_cake_count -1:
            if abs(m_reverse_list[i] - m_reverse_list[i+1]) == 1: # 不在自己的位置上，但又相隔1，必然会导致一次交换
                node.score = node.score + 1
            # 这个减少分数的逻辑就有点看不懂了=(
            if abs(m_reverse_list[0] - m_reverse_list[i+1]) == 1:
                node.score = node.score - 1
        else:
            # if m_reverse_list[i] == i:
                # node.score = node.score + 1
            if m_reverse_list[0] == i:
                node.score = node.score - 1

        node_set.append(node)

    sorted_node_set = sorted(node_set, key=lambda node: node.score)

    for node in sorted_node_set:
        swap(node.index)
        m_reverse_swap_list[step] = node.index
        is_done = search(step+1, k)
        swap(node.index)
        if is_done:
            break

    return False


def record():

    global m_cake_list, m_max_swap, m_reverse_swap_list, m_swap_list

    print "\n********\n"
    print "input_list:{input_list}".format(input_list=m_cake_list)
    print "m_search:{m_search}".format(m_search=m_search)
    print "m_max_swap:{m_max_swap}".format(m_max_swap=m_max_swap)
    print "m_swap_list:{m_swap_list}".format(m_swap_list=m_swap_list[:m_max_swap])
    print "\n********\n"


# define the global vars
m_cake_list = []
m_swap_list = [] # store the steps
m_reverse_list = [] # current reverse cake list
m_reverse_swap_list = [] # current reverse cake swap list
m_cake_count = 0
m_max_swap = 0 # the max swap count we have met
m_search = 0  # 当前搜索次数信息
m_root_node = None
m_flag = False


if __name__ == '__main__':
    # test 1
    t_list = (
    # [1, 2, 3, 6, 5, 4, 8, 9, 0, 7],
    [3, 1, 2, 6, 5, 4, 8, 9, 0, 7],
    [12,3,2,1,11,6,5,10,4,9,8,7,0],
    [2,0,1]
    )
    for cake_list in t_list:
        print "**** input list *****:", cake_list
        init(cake_list)
        search(0, len(cake_list)-1)
        record()
        release_all()

    # test 2
