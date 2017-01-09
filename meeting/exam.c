/* TODO 这个算法的合理性待校验 */

#include <iostream>

using namespace std;

/* 1.for each vertex in G 初始化颜色为0 */
/* 2.vertex[0]=1//选初始点颜色置为1 */
/* 3.置颜色种类color=0； */
/* 4.循环置所有顶点着色 */
/*     color++;//取下一颜色 */
/*     for each vertex in G */
/*         if vertex[i]已着色，转下一顶点 */
/*         else */
/*             若该点用color着色与其他邻接点颜色不冲突 */
/*             vertex[i]=color; */
/*             否则不着色    */

bool IsOk(int **map, int *vertex, int node, int color, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (map[node][i] == 1 && vertex[i] == color && node != i)//邻接点且着色冲突,且冲突点不是该点本身
        return false;
        //if (map[node][i] == 1 && vertex[i] == color)也正确，因为判定点和着色点是同一点，着色点此时并未着色不会判false

    }
    return true;
}

int main(void)
{
    freopen("test.in", "r", stdin);
    freopen("result.out", "w", stdout);

    int count;

    cin >> count;

    int **map = new int *[count];//邻接矩阵
    int *vertex = new int[count];//存储顶点颜色

    // 申请内存及初始化顶点颜色
    for (int i = 0; i < count; i++)
    {
        map[i] = new int[count];
        vertex[i] = 0;
    }

    // 读邻接矩阵数据
    for (int i = 0; i < count; i++)
    for (int j = 0; j < count; j++)
        cin >> map[i][j];

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
            cout << map[i][j]<< " ";
        cout << endl;
    }


    vertex[0] = 1;//置首节点颜色为1
    int color = 0;
    int flag = 1;//标志位，是否有节点未被染色

    while (flag)//每循环一次用颜色color给尽可能多的结点染色
    {

        color++;

        for (int i = 1; i < count; i++)
        {
            if (vertex[i] != 0) // 已着色
                continue;
            else // 未着色
            {
                if (IsOk(map, vertex, i, color, count))
                    vertex[i] = color;
            }
        }

        int k = 0;

        // 这里有可能会退出
        for (k = 1; k < count; k++)
        {
            if (vertex[k] == 0)//有顶点未被着色
                break;
        }

        if (k == count)
            flag = 0;
    }

    cout << "At less" << color << "colors are needed!" << endl;

    for (int i = 0; i < count; i++)
        cout << "Vertex " << i << ": " << vertex[i] << endl;


    return 0;
}
