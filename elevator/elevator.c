#include <iostream>

using namespace std;

#define FLOORS    10
int arrFloorPeople[FLOORS] = {0,0,1,0,1,1,0,0,1,1};

void Calc(int &nFloors, int& nFloorIndex)
{
    int i = 0;
    int N1 =0, N2 = 0, N3 = 0;
    int nMin = 0, nTargetFloor = 0;

    for (N1 = 0, N2 = arrFloorPeople[1], N3 = 0, i = 1; i < FLOORS; i++)
    {
        N3 += arrFloorPeople[i];
        nMin += arrFloorPeople[i] * (i-1);
    }

    for (i = 2; i < FLOORS; i++)
    {
        if(N1+N2 <N3)
        {
            nTargetFloor = i;
            nMin += (N1 + N2 - N3);
            N1 += N2;
            N2 = arrFloorPeople[i];
            N3 -= arrFloorPeople[i];
        }
        else
            break;
    }

    nFloors = nMin;

    nFloorIndex = nTargetFloor+1;
}

int main()
{
    int nFloors = 0;
    int nFloorIndex = 0;

    Calc(nFloors, nFloorIndex);
    cout << "stop at: floor " << nFloorIndex << "   clmib = " << nFloors << endl;
    cin >> nFloors;
}
