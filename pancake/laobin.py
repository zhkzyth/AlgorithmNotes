#!/usr/bin/env python
# encoding: utf-8
__author__ = 'DELL'


def introduction():
    """
    问题： 星期五的晚上，一帮同事在希格玛大厦附近的“硬盘酒吧”多喝了几杯。程序员多喝了几杯之后谈什么呢？自然是算法问题。有个同事说：“我以前在餐馆打工，顾客经常点非常多的烙饼。店里的饼大小不一，我习惯在到达顾客饭桌前，把一摞饼按照大小次序摆好——小的在上面，大的在下面。由于我一只手托着盘子，只好用另一只手，一次抓住最上面的几块饼，把它们上下颠倒个个儿，反复几次之后，这摞烙饼就排好序了。我后来想，这实际上是个有趣的排序问题：假设有n块大小不一的烙饼，那最少要翻几次，才能达到最后大小有序的结果呢？” 你能否写出一个程序，对于n块大小不一的烙饼，输出最优化的翻饼过程呢？
    分析： 题目要求的是最优化方案，而不是仅仅将其排好序。一种简单的排序方法是，首先将最上面到最大的饼翻转，这样最大的饼到了最上面，再整体翻转，这样最大的饼就排好序了。按照这样的方法依次去拍n-1大的，n-2大的……经过2n-2次翻转，完成排序。也就是说，这个问题的最优解的一个上界是2n-2，我们要寻找最优化的解。 寻找最优解的很直接的想法就是搜索。搜索的缺点是相对其他方法比较消耗内存和时间，但是比较通用，很多问题也只适合用搜索解，其他方法不适合用。动态规划相比搜索会有更好的效率。考虑如果使用动态规划，动态规划需要划分问题具有优化子结构，以及子问题重叠性。但在这个问题里似乎不太好划分子问题。
    搜索的步骤就是把全部的交换方式组织成一棵树，对这颗树进行遍历操作，到达叶子节点表示找到了一种可行解，我们要寻找的是所有可行解中的最优情况。广度优先遍历需要保存整个树在内存中，非常消耗空间，因此使用深度优先遍历。对深搜的优化可以使用分支定界，对不可能的解空间减少不必要的搜索。树的创建的过程就是遍历的过程，由于需要进行回退，因此不能在原数组上进行排序，而是需要额外的空间进行存储，因此考虑在每个节点存储当前整个数组。树的创建是动态的，一旦确定是需要抛弃的，就直接删除节省空间。
    总结一下： 1. 设有n张饼，交换方式上界为2n-2，那么每个节点有n-1个子节点 2. 实际上每个节点有n-2个子节点，因为有一个节点必然不成立：不可能和上一层的交换方式相同，那样就换回去了 3. 但是这个节点的位置还得留着，给个空指针即可 4. 每个节点存储的内容有：当前数组，层数，全部的交换步骤 5. 根节点层数标为0，因为我们要的实际上是交换次数 6. 需要一个全局变量，保存当前已经找到的可行解的上界
    遍历和剪枝的过程： 1. 对于每个节点，考察它是否已经排好序 2. 如果已经排好序，比较它和当前的上界的大小，如果更小，那么修改上界为当前值。返回 3. 如果没有排好序，考察它是否已经达到上界 4. 如果已经达到上界，返回 5. 如果没有到达上界，创建它的子节点
    这样看下来发现其实不需要存储这棵树，只需要一个栈就行了。每个节点存储着之前的交换信息。差不多可以开始写代码了。JetBrains的PyCharm社区版不久之前宣布开源，正好试用一下。Python中的List可以作为栈使用，栈顶为List的末尾，栈底为起始位置，这个要记清楚。注意我们假设每一张饼大小都不相同。
    写完了，感觉PyCharm相当不错啊，调试比PyDev强多了。上Python代码
    ```
    """
    pass


class Node:
    cakes = []
    currentLevel = 0
    steps = []


def inputCakes(cakes):
    global n
    global upperBound
    n = int(raw_input('n:'))
    upperBound = 2 * n - 2
    for i in range(0, n):
        cakes.append(int(raw_input(str(i) + ':')))


def init():
    global stack
    node = Node()
    inputCakes(node.cakes)
    #node.cakes = swap(node.cakes, 1)
    stack.append(node)


def swap(cakes, position):
    newcakes = cakes[:]
    for i in range(0, position / 2 + 1):
        temp = newcakes[i]
        newcakes[i] = newcakes[position - i]
        newcakes[position - i] = temp
    return newcakes


def isSorted(cakes):
    for i in range(0, len(cakes) - 1):
        if cakes[i] > cakes[i+1]:
            return False
    return True


def dfs():

    global stack
    global upperBound
    global n

    while len(stack) != 0:

        node = stack[-1]
        stack.pop()

        if isSorted(node.cakes):
            print 'Found:', node.steps
            if node.currentLevel < upperBound:
                upperBound = node.currentLevel
        else:
            if node.currentLevel < upperBound:
                for i in range(1, n):
                    if len(node.steps) == 0 or (len(node.steps) > 0 and i != node.steps[-1]): # 在i和step的值重复的情况下，就会重排，因为之前已经排过一次
                        childNode = Node()
                        childNode.cakes = swap(node.cakes, i)
                        childNode.currentLevel = node.currentLevel + 1
                        childNode.steps = node.steps[:]
                        childNode.steps.append(i)
                        stack.append(childNode)

n = 0
upperBound = 0
stack = []

if __name__ == '__main__':
    init()
    dfs()
