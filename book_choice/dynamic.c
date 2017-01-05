#include <iostream>

using namespace std;

#define MAX 1000000

void SortY1_Y5(int &nY1, int &nY2, int &nY3, int &nY4, int &nY5)
{
    int nTmp = 0, nMax = 0;
    int i = 0, j = 0;
    int arrData[5] = {nY1, nY2, nY3, nY4, nY5};

    for (i = 0; i < 5; i++)
    {
        nMax = arrData[i];
        for (j = i; j < 5; j++)
        {
            if (arrData[j] > nMax)
            {
                nTmp = nMax;
                nMax = arrData[j];
                arrData[j] = nTmp;
            }
        }
        arrData[i] = nMax;
    }

    nY1 = arrData[0];
    nY2 = arrData[1];
    nY3 = arrData[2];
    nY4 = arrData[3];
    nY5 = arrData[4];
}

// 选出最低值出现的方案，然后继续遍历下去
double minValue(double dVal1, double dVal2, double dVal3, double dVal4, double dVal5, int& nIndex)
{
    double dmin = dVal1;
    nIndex = 0;

    if (dmin > dVal2)
    {
        nIndex = 1;
        dmin = dVal2;
    }

    if (dmin > dVal3)
    {
        nIndex = 2;
        dmin = dVal3;
    }

    if (dmin > dVal4)
    {
        nIndex = 3;
        dmin = dVal4;
    }

    if (dmin > dVal5)
    {
        nIndex = 4;
        dmin = dVal5;
    }
    return dmin;
}

// Y1 >= Y2 >= Y3 >= Y4 >= Y5
double Calc(int nY1, int nY2, int nY3, int nY4, int nY5)
{
    double dMin = 0;
    int nIndex = 0;

    if ((nY1 == 0) && (nY2 == 0) && (nY3 == 0) && (nY4 == 0) && (nY5 == 0))
        return 0;

    // 深度优先的遍历
    if ((nY1 - 1 >= 0) || (nY2 - 1 >= 0) || (nY3 - 1 >= 0) || (nY4 - 1 >=  0) || (nY5 - 1 >= 0))
    {
        SortY1_Y5(nY1, nY2, nY3, nY4, nY5);
        dMin = minValue(
            (5*8)*(1-0.25) + Calc(nY1-1, nY2-1, nY3-1, nY4-1, nY5-1),
            (4*8)*(1-0.20) + Calc(nY1-1, nY2-1, nY3-1, nY4-1,   nY5),
            (3*8)*(1-0.10) + Calc(nY1-1, nY2-1, nY3-1,   nY4,   nY5),
            (2*8)*(1-0.05) + Calc(nY1-1, nY2-1,   nY3,   nY4,   nY5),
            8  + Calc(nY1-1,   nY2,   nY3,   nY4,   nY5),
            nIndex);
    }
    else
    {
        return MAX;
    }

    switch (nIndex)
    {
    case 0:
        cout << "Min:   " << dMin << "( " <<nY1-1 << ", " << nY2-1 << ", " << nY3-1 << ", " << nY4-1 << ", " << nY5-1 << ", " << ")"<< endl;
        break;
    case 1:
        cout << "Min:   " << dMin << "( " <<nY1-1 << ", " << nY2-1 << ", " << nY3-1 << ", " << nY4-1 << ", " << nY5 << ", " << ")"<< endl;
        break;
    case 2:
        cout << "Min:   " << dMin << "( " <<nY1-1 << ", " << nY2-1 << ", " << nY3-1 << ", " << nY4 << ", " << nY5 << ", " << ")"<< endl;
        break;
    case 3:
        cout << "Min:   " << dMin << "( " <<nY1-1 << ", " << nY2-1 << ", " << nY3 << ", " << nY4 << ", " << nY5 << ", " << ")"<< endl;
        break;
    case 4:
        cout << "Min:   " << dMin << "( " <<nY1-1 << ", " << nY2 << ", " << nY3 << ", " << nY4 << ", " << nY5 << ", " << ")"<< endl;
        break;
    default:
        break;
    }

    return dMin;
}


int main()
{
    double dMoney = 0;
    //int test[5] = {1,1,1,1,1};
    //int test[5] = {2,2,2,2,2};
    //int test[5] = {1,1,0,0,0};
    //int test[5] = {2,2,2,1,1};
    int test[5] = {3,2,2,1,1};
    //int test[5] = {2,1,1,0,0};

    dMoney = Calc(test[0], test[1], test[2], test[3], test[4]);

    cout << dMoney << endl;

    cin >> dMoney;
}
