// 《编程之美》1.9 见面时间重复规避问题

const int N = 4 ;

struct Time
{
  int begin ; //开始时间
  int end   ; //结束时间

} ;

bool forbit[N] ; //禁止数组，为false的时候，表示当前该颜色可以使用
int maxcolors  ; //当前最大的颜色数目

Time times[N] ;
int color[N] = {0} ;
int cmp(const void * a , const void * b)
{
  return ((Time*)a)->begin - ((Time*)b)->begin ;

}

void init()
{
  for(int i = 0 ; i < N ; i++)
    {
      cin>>times[i].begin>>times[i].end ; //输入开始时间和结束时间
    }
  qsort(times ,N , sizeof(Time)  ,cmp) ;
  //for(i = 0 ; i < N ;i++)
  // forbit[i] = false ;
}

bool overlap(const Time & a, const Time & b)
{
  if(b.begin >= a.begin && b.begin < a.end )
    return true ;
  return false ;
}

int arrange()
{
  maxcolors = 0 ;

  int i , j , k ;

  for(i = 0 ; i < N ;i++) //循环每一个约会安排
    {

      for(k = 0 ; k < maxcolors ;k++)
        {
          forbit[k] = false ;
        }

      //判断在i之前的节点是否是与i节点有重合的部分
      for(j = 0 ; j < i ;j++)
        {
          if(overlap(times[j] , times[i])) //判断两者是否相交
            {
              forbit[color[j]] = true ;
            }
        }

      for(k = 0 ; k < maxcolors ;k++)
        {
          if(!forbit[k])
            break ;
        }

      if(k < maxcolors)
        color[i] = k ;
      else
        color[i] = maxcolors++ ;
    }

  return maxcolors ;
}


int main()
{
  init() ;
  int max = arrange() ;
  cout<<max<<endl ;
  system("pause") ;
  return 0 ;
}
