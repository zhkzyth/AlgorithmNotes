#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

const int MAXSIZE = 100;

using namespace std;

void generateData()//产生随机测试数据
{
  srand(time(NULL));
  ofstream fin("dataSource.txt");
  if(!fin)
    {
      printf("Can't open file!\n");
      return;
    }
  for(int i = 0 ; i < MAXSIZE ; i++)
    {
      int temp = rand() % MAXSIZE;
      fin << temp << ' ';
    }
  fin.close();
}

int readData(int* pArr)
{
  ifstream fin("dataSource.txt");
  if(!fin)
    {
      printf("Can't open file!\n");
      return -1;
    }
  int iCnt = 0;//读取每一个数字之后然后存入
  char strNum[100];
  while(fin >> strNum)//将读到的每个数字的字符串形式转换成整数形式
    {
      pArr[iCnt++] = atoi(strNum);
    }
  fin.close();
  return iCnt;
}

int _iCnt = 0;
void mergeSort(int* pArr,int low,int high,int* pTempArr)
{
  if(!pArr || !pTempArr || low > high || low < 0 || high < 0)//鲁棒性
    {
      return;
    }
  if(high - low > 1)//注意，必须确保在至少含有一个元素，如果high- low = 1,此时只有一个元素，不需要排序
    {
      int mid = low + (high - low)/2;//先划分
      mergeSort(pArr,low,mid,pTempArr);//然后递归求解
      mergeSort(pArr,mid,high,pTempArr);
      int l = low,m = mid,i = l;
      while(l < mid || m < high)
        {
          //如果右边已经遍历结束，或者两边都没结束但是左边<=右边的话，就归并左边的，此时不存在逆序对
          if(m >= high || (l < mid && pArr[l] <= pArr[m]))
            {
              pTempArr[i++] = pArr[l++];
            }
          else
            {
              pTempArr[i++] = pArr[m++];
              _iCnt += mid - l;//存在的逆序数为：左边剩余没有被归并到数组中的元素的个数，因为只有比右边大的才留下来了
            }
        }
      for(int i = low ; i < high; i++)//全部归并结束之后，把临时数组里面的元素赋给原来的数组
        {
          pArr[i] = pTempArr[i];
        }
    }
}

void writeResult(int* pArr,int iLen)
{
  if(!pArr || iLen < 0)
    {
      return;
    }
  ofstream fout("sortedData.txt");//输出，想把数据写在文件里面用ofstream
  if(!fout)
    {
      return;
    }
  for(int i = 0 ; i < iLen ; i++)
    {
      if((i+1) % 20 == 0)
        {
          fout << endl;
        }
      fout << pArr[i] << ' ';
    }
}

void process()
{
  generateData();
  int iArr[MAXSIZE + 1];
  int iLen = readData(iArr);
  int iTempArr[MAXSIZE+1];
  _iCnt = 0;
  mergeSort(iArr,0,iLen,iTempArr);
  printf("%d\n",_iCnt);
  writeResult(iArr,iLen);//将排序后的数据写入文件
}

int main(int argc,char* argv[])
{
  process();
  getchar();
  return 0;
}
