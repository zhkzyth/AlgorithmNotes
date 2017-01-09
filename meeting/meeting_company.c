/* http://www.cppblog.com/jake1036/archive/2011/06/30/149802.html */
/*  一 问题描述： */
/*   已知有n位学生，他们分别对m个分组中的若干个感兴趣。  */
/*   每个学生都必须能够参加，他们所感兴趣的部门的会议。 */
/*   每个会议的开会时间都为t，求会议如何安排使得需要的总时间最短。 */

/*   其中一个最简单的方法： */
/*   即每个会议不会同时召开，则时间变为m * t。 */

/*  二 问题分析： */

/*   下面我们需要寻找可以同时召开的会议，来进一步减少花费的总时间。 */
/*   问题建模： */
/*    这个题目可以转换为图的最少着色问题： */
/*    (1)即将两个不能同时召开的会议，用同一条直线进行连接。 */
/*    (2)然后对图中的每个顶点进行着色，保证有直线连接的两个节点之间不允许重色。  */
/*    (3)先随意将其中一个节点染色，然后对剩余的n-1个节点，进行n个颜色的枚举， */
/*       复杂度为o((n-1)^n) 。 */
/*    (4)着色之后，需要对每一个顶点进行判断，则复杂度为o(n*n)。 */
/*    (5)则全部的时间复杂度为o((n-1)^n * o(n*n))  */

#include <iostream>
using namespace std ;
const int N = 3 ; //学生数目
const int M = 4 ; //会议的数目

int meet[N][M] = //表示每个学生感兴趣的会议信息
  {
    {1 , 1 , 1 , 0} ,
    {0 , 1 , 1 , 1} ,
    {0 , 1 , 1 , 0} ,
  } ;

int path[M][M] =  //根据meet二维数组。建立起
  {
    {0 , 0 , 1 , 0} ,
    {0 , 0 , 0 , 1} ,
    {1 , 0 , 0 , 0} ,
    {0 , 1 , 0 , 0}
  } ;


int color[M] = {0 , -1 , -1 ,-1}; //初始化颜色数组，每一个顶点有一个颜色

bool judge(int i , int j)//判断第i个节点，当涂j颜色的时候，是否满足
{
  for(int w = 0 ; w < M ;w++)
    {
      if(path[i][w]) //若是i 和 w两点相邻，则需要判断 两者的颜色是否相同
        {
          if(color[i] == color[w])
            return false ;
        }
    }
  return true ;
}

int arrange()
{
  int num = 0 ; //表示可以同时安排的会议的数目

  for(int i =  1 ; i < M ;i++)//表示每一个顶点
    {
      for(int j = 0 ; j < M ;j++)    //表示每一种颜色
        {
          color[i] = j ; //对应节点设置为颜色j，设置完毕之后，判断该颜色是否满足

          if(judge(i , j)) //判断第i个节点，当涂j颜色的时候，是否满足
            {
              break;
            }
        }
    }

  for(int i = 0 ; i< M ;i++)
    {
      cout<<color[i]<<" " ;
      if(num < color[i])
        num = color[i] ;
    }

  return num + 1;
}


int main()
{
  int time = 5 ; //每个会议持续的时间
  int t = arrange() ;
  cout<<"花费总的时间:"<<time *  t<<endl ;

  getchar() ;
  return 0 ;
}
