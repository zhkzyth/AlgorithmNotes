#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

/* Welch Powell法 */

/* a).将G的结点按照度数递减的次序排列. */
/* b).用第一种颜色对第一个结点着色,并按照结点排列的次序  */
/*    对与前面着色点不邻接的每一点着以相同颜色. */
/* c).用第二种颜色对尚未着色的点重复步骤b).用第三种颜色 */
/*    继续这种作法, 直到所有点着色完为止. */

/* http://www.kancloud.cn/qiaodong/datastructure/143774 */
/* 这是一种表示无向连通图的表示方法 */
/* 8 8 */
/* 0 1 1 1 0 0 1 0 */
/* 1 0 1 1 1 0 0 0 */
/* 1 1 0 0 1 1 0 0 */
/* 1 1 0 0 1 0 1 0 */
/* 0 1 1 1 0 1 1 1 */
/* 0 0 1 0 1 0 0 1 */
/* 1 0 1 1 1 0 0 1 */
/* 0 0 0 0 1 1 1 0 */

using namespacestd;

int map[10][10];//邻接矩阵

typedef struct Node{ //定义节点结构体
  int index; //编号
  int degree; //度
  int color; //改节点的颜色
} Node;

Node nodes[10];

bool com(Node node1,Node node2) {
  // 按度从高到低排序，这样就可以把连接度高的优先拿出来
  return node1.degree > node2.degree;
}

bool com2(Node node1,Node node2) {
  // 再按照节点的顺序排序
  return node1.index < node2.index;
}

int main() {

  ifstream read;

  read.open("map.data"); // map.data是存放数据的文件名

  int m, n;

  while (read >> m>> n) {

    for (int i = 0; i < m; i++) { // 读入数据

      int degree = 0;

      for (int j = 0; j < n; j++) {

        read >> map[i][j];

        if (map[i][j])
          degree++;
      }

      nodes[i].index = i;
      nodes[i].degree = degree;
      nodes[i].color = 0;
    }

    // 先对每一行做排序
    sort(nodes, nodes + m, com);

    int k = 0; // K代表第几种颜色

    while (true) {

      k++;

      int i;

      for (i = 0; i < m; i++) { // 先找到第一个未着色的节点

        if (nodes[i].color == 0) {
          nodes[i].color = k;
          break;
        }

      }

      if (i == m)//循环退出的条件,所有节点都已着色
        break;

      //再把所有不和该节点相邻的节点着相同的颜色
      for(int j=0; j<m; j++){

        // 在当前的第i行，找第j列可以着色的
        // 当前这个节点没有着色，且两节点不相连，且不是同一个节点
        if(nodes[j].color == 0 && map[nodes[i].index][nodes[j].index] == 0
           &&i!=j)

          nodes[j].color = k;
      }

    }

    //输出结果：
    sort(nodes, nodes + m, com2); // 再按照输入的节点序列输出节点

    cout << "共需要" << k-1 << "种颜色" << endl;
    for (int i = 0; i < m; i++)
      cout<< "节点："<<nodes[i].index <<":着色" << nodes[i].color <<endl;
    return 0;
  }

}
