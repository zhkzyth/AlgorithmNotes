#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

struct node
{
    int index;
    int score;
};

bool comp(struct node a, struct node b)
{
    return a.score < b.score;
}

class CPrefixSorting
{
public:

    CPrefixSorting()
    {
        m_nCakeCnt = 0;
        m_nMaxSwap = 0;
        m_CakeArray = NULL;
        m_SwapArray = NULL;
        m_ReverseCakeArray = NULL;
        m_ReverseCakeArraySwap = NULL;
        flag1 = false;
    }

    ~CPrefixSorting()
    {
        releaseAll();
    }

    void releaseAll()
    {
        if( m_CakeArray != NULL )
        {
            delete []m_CakeArray;
            m_CakeArray = NULL;
        }
        if( m_SwapArray != NULL )
        {
            delete []m_SwapArray;
            m_SwapArray = NULL;
        }
        if( m_ReverseCakeArray != NULL )
        {
            delete []m_ReverseCakeArray;
            m_ReverseCakeArray = NULL;
        }
        if( m_ReverseCakeArraySwap != NULL )
        {
            delete []m_ReverseCakeArraySwap;
            m_ReverseCakeArraySwap = NULL;
        }
    }

    //
    // 计算烙饼翻转信息
    // @param
    // pCakeArray    存储烙饼索引数组
    // nCakeCnt    烙饼个数
    //
    void Run(int* pCakeArray, int nCakeCnt)
    {

        releaseAll();
        Init(pCakeArray, nCakeCnt);

        m_nSearch = 0;
        Search(0, nCakeCnt - 1);
    }

    //
    // 输出烙饼具体翻转的次数
    //
    void Output()
    {
        for(int i = 0; i < m_nMaxSwap; i++)
        {
            printf("%d ", m_SwapArray[i]);
        }

        printf("\n |Search Times| : %d\n", m_nSearch);
        printf("Total Swap times = %d\n\n", m_nMaxSwap);
    }

private:

    //
    // 初始化数组信息
    // @param
    // pCakeArray    存储烙饼索引数组
    // nCakeCnt    烙饼个数
    //
    void Init(int* pCakeArray, int nCakeCnt)
    {
        assert(pCakeArray != NULL);
        assert(nCakeCnt > 0);

        flag1 = false;

        m_nCakeCnt = nCakeCnt;

        // 初始化烙饼数组
        m_CakeArray = new int[m_nCakeCnt];
        assert(m_CakeArray != NULL);
        for(int i = 0; i < m_nCakeCnt; i++)
        {
            m_CakeArray[i] = pCakeArray[i];
        }

        // 初始化中间交换结果信息
        m_ReverseCakeArray = new int[m_nCakeCnt];
        for(int i = 0; i < m_nCakeCnt; i++)
        {
            m_ReverseCakeArray[i] = m_CakeArray[i];
        }

        // 设置最多交换次数信息
        //m_nMaxSwap = UpBound(m_nCakeCnt);
        m_nMaxSwap = UpBound_case(m_ReverseCakeArray, m_nCakeCnt);
        //UpBound_case中m_ReverseCakeArray改变了
        //m_ReverseCakeArray复原
        for(int i = 0; i < m_nCakeCnt; i++)
        {
            m_ReverseCakeArray[i] = m_CakeArray[i];
        }

        // 初始化交换结果数组
        m_SwapArray = new int[m_nMaxSwap + 1];
        assert(m_SwapArray != NULL);

        m_ReverseCakeArraySwap = new int[m_nMaxSwap];
        assert(m_ReverseCakeArraySwap != NULL);
    }


    //
    // 寻找当前翻转的上界
    //
    //
    int UpBound(int nCakeCnt)
    {
        return nCakeCnt*2-2;
    }

    //--每次把最大的翻转到最下面，计算这种方法所需要的次数
    //--计算过程中保存翻转结果，因为这种方法可能就是最小翻转次数的方法
    //--这个次数可以作为翻转次数的上界
    int UpBound_case(int* pCakeArray, int nCakeCnt)
    {
        int re = 0;
        for (int j = nCakeCnt - 1 ; ;)
        {
            while(j > 0 && j == pCakeArray[j])
                --j;
            if (j <= 0)
                break;
            int i = j;
            while (i >= 0 && pCakeArray[i] != j)
                --i;
            if (i != 0)
            {
                Revert(pCakeArray, 0, i);
                re++;
            }
            Revert(pCakeArray, 0, j);
            re++;
            --j;
        }
        return re;
    }

    //
    // 寻找当前翻转的下界
    //
    //
    int LowerBound(int* pCakeArray, int nCakeCnt)
    {
        int t, ret = 0;

        // 根据当前数组的排序信息情况来判断最少需要交换多少次
        for(int i = 1; i < nCakeCnt; i++)
        {
            // 判断位置相邻的两个烙饼，是否为尺寸排序上相邻的
            t = pCakeArray[i] - pCakeArray[i-1];
            if((t == 1) || (t == -1))
            {
            }
            else
            {
                ret++;
            }
        }
        //--如果最大的烙饼不在最后一个位置，则要多翻转一次
        if (pCakeArray[nCakeCnt-1] != nCakeCnt-1) ret++;
        return ret;
    }

    //--序列评估函数，对一个序列，若到达有序状态所需的翻转次数越少，得分越少
    //--若到达有序状态所需的翻转次数越多，得分越多
    //--搜索时可以优先搜索得分少的序列，这样能尽快达到最优解
    int Evaluate(int* pCakeArray, int nCakeCnt)
    {
        return LowerBound(pCakeArray, nCakeCnt);
    }

    // 排序的主函数
    //--第endBound+1 个烧饼后均以排好序，没有必要对排好序的进行交换
    //--因为交换已经排好序的烧饼只能使交换次数增大
    //--如果当前搜索的序列排好序则返回true，否则返回false
    bool Search(int step, int endBound)
    {
        int i, nEstimate;

        m_nSearch++;

        // 估算这次搜索所需要的最小交换次数
        nEstimate = LowerBound(m_ReverseCakeArray, m_nCakeCnt);

        //--遇到相等情形，若对于翻转次数为m_nMaxSwap的结果已经保存，流程继续。
        //--后面再遇到就可以跳过了，因为针对该翻转次数的结果已经保存，
        //无需再计算
        if(step + nEstimate == m_nMaxSwap && flag1 == false);
        else if(step + nEstimate >= m_nMaxSwap)
            return false;

        //重新计算排好序的位置
        int k = endBound;
        while(k > 0 && k == m_ReverseCakeArray[k])
            --k;

        // 如果k=0,说明已经排好序，即翻转完成，输出结果
        //if(IsSorted(m_ReverseCakeArray, m_nCakeCnt))
        if(k == 0)
        {
            if(step < m_nMaxSwap)
            {
                //--当前找到的一个解
                m_nMaxSwap = step;
                for(i = 0; i < m_nMaxSwap; i++)
                    m_SwapArray[i] = m_ReverseCakeArraySwap[i];
            }
            else if(step == m_nMaxSwap && flag1 == false)
            {
                //--只有第一次碰到step == m_nMaxSwap时才做如下操作
                //--因为m_nMaxSwap可能是最小翻转次数，因此要记录此次结果
                //--后面再碰到相等时，可以忽略，因为不用重复保存结果
                for(i = 0; i < m_nMaxSwap; i++)
                    m_SwapArray[i] = m_ReverseCakeArraySwap[i];
                flag1 = true;
            }
            return true;
        }

        // 递归进行翻转,k之后已经排好序的位置就不用翻转了
        std::vector<node> swapIndexScore;

        //对翻转后的序列进行评估，评估它到排序好的序列之间的距离，优先搜索距离小的序列
        for(i = 1; i <=k; i++)
        {
            struct node tnode;
            tnode.index = i;
            tnode.score = nEstimate;//原始序列的分数
            //求翻转后的分数，翻转后只有翻转位置影响分数的大小
            if(i != m_nCakeCnt - 1)
            {
                if(abs(m_ReverseCakeArray[i] - m_ReverseCakeArray[i+1]) == 1)
                    tnode.score++;
                if(abs(m_ReverseCakeArray[0] - m_ReverseCakeArray[i+1]) == 1)
                    tnode.score--;
            }
            else
            {
                if(m_ReverseCakeArray[i] == i)tnode.score++;
                if(m_ReverseCakeArray[0] == i)tnode.score--;
            }
            swapIndexScore.push_back(tnode);
        }
        //按照得分小到大排序，得分小的优先搜索
        sort(swapIndexScore.begin(), swapIndexScore.end(),comp);

        for(i = 0; i < swapIndexScore.size() ; i++)
        {
            Revert(m_ReverseCakeArray, 0, swapIndexScore[i].index);
            m_ReverseCakeArraySwap[step] = swapIndexScore[i].index;
            bool isDone = Search(step + 1, k);
            Revert(m_ReverseCakeArray, 0, swapIndexScore[i].index);
            //如果该搜索序列有序，那么其他翻转方案肯定会导致无序，因此不需要搜索
            if(isDone == true) return true;
        }

//        for(i = 1; i <=k ; i++)
//        {
//            Revert(m_ReverseCakeArray, 0, i);
//            m_ReverseCakeArraySwap[step] = i;
//            Search(step + 1, k);
//            Revert(m_ReverseCakeArray, 0, i);
//        }
        return false;
    }
    //
    // true : 已经排好序
    // false : 未排序
    //
    bool IsSorted(int* pCakeArray, int nCakeCnt)
    {
        for(int i = 1; i < nCakeCnt; i++)
        {
            if(pCakeArray[i-1] > pCakeArray[i])
            {
                return false;
            }
        }
        return true;
    }

    //
    // 翻转数组
    //
    void Revert(int arry[], int nBegin, int nEnd)
    {
        assert(nEnd > nBegin);
        int i, j, t;

        // 翻转数组
        for(i = nBegin, j = nEnd; i < j; i++, j--)
        {
            t = arry[i];
            arry[i] = arry[j];
            arry[j] = t;
        }
    }

private:

    int* m_CakeArray;    // 烙饼信息数组
    int m_nCakeCnt;    // 烙饼个数
    int m_nMaxSwap;    // 最多交换次数。根据前面的推断，这里最多为
    // m_nCakeCnt * 2
    int* m_SwapArray;    // 交换结果数组

    int* m_ReverseCakeArray;    // 当前翻转烙饼信息数组
    int* m_ReverseCakeArraySwap;    // 当前翻转烙饼交换结果数组
    int m_nSearch;    // 当前搜索次数信息
    bool flag1;//--当最开始计算的m_nMaxSwap是最小翻转次数时，若记录了这个翻转的
               //结果,flag1 = ture，否则为false，详见search函数
};

int main()
{
    CPrefixSorting a;
    /* int cakeArry[] = {3,2,1,6,5,4,9,8,7,0}; */
    int cakeArry[] = {3,1,2,6,5,4,8,9,0,7};
    int cakeArry1[] = {12,3,2,1,11,6,5,10,4,9,8,7,0};
    int cakeArry2[] = {2,0,1};
    a.Run(cakeArry, sizeof(cakeArry) / sizeof(int));
    a.Output();
    a.Run(cakeArry1, sizeof(cakeArry1) / sizeof(int));
    a.Output();
    a.Run(cakeArry2, sizeof(cakeArry2) / sizeof(int));
    a.Output();
    return 0;
}
