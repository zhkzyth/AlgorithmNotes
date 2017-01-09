#include <iostream>
#include <list>
#include <vector>

 using namespace std;

 // If 2 recruiting meetings are conflicting
 bool IsConflict(const vector<bool>& v1, const vector<bool>& v2)
{
    for(int i = 0; i < v1.size(); ++i)
    {
        if(v1[i] && v2[i]) return true;
    }
    return false;
}

 // merge 2 recruiting meetings: v2 will be held at the same time of v1
 void Merge(vector<bool>& v1, const vector<bool>& v2)
{
    for(int i = 0; i < v1.size(); ++i)
    {
        v1[i] = v1[i] || v2[i];
    }
}

 // input:       input[m][n], 2d array to represents students' selection of meetings. row stands for meetings, column stands for students,
//              and array value stands for if a student select a meeting
// next:        The meeting to check
// curTime:     Time required so far
// curArrangement: record the information of which meeting is merged with another meeting
// best[output]:The best time
// bestArrangement[output] : The best arragement
void ArrangeRecruitings(vector<vector<bool> >& input, int next, int& curTime, vector<list<int> >& curArrangement, int& bestTime, vector<list<int> >& bestArrangement)
{
    int m = input.size();
    // base cases
    if(next >= m)
    {
        // Save the best one
        if(curTime < bestTime)
        {
            bestTime = curTime;
            bestArrangement = curArrangement;
        }

        return;
    }
    else
    {
        // recursive cases
        for(int i = 0; i <= next; ++i)
        {

            if(curArrangement[i].empty()) continue; // if already merged with other ones, just skip it

            if (!IsConflict(input[i], input[next]))
            {

                // update the status
                vector<bool> bkI = input[i];
                Merge(input[i], input[next]);

                curArrangement[next].pop_back();
                curArrangement[i].push_back(next);

                // Consider next one after merge
                ArrangeRecruitings(input, next+1, curTime, curArrangement, bestTime, bestArrangement);

                // restore the status
                curArrangement[i].pop_back();
                curArrangement[next].push_back(next);

                input[i] = bkI;
            }
        }

        // Consider next one without any merge
        ArrangeRecruitings(input, next+1, ++curTime, curArrangement, bestTime, bestArrangement);

    }
}


int main()
{
    // 1. Initializing
    int m = 3;
    int n = 4;

    vector<vector<bool> > input(m, vector<bool>(n, false));

    input[0][0] = true;
    input[0][1] = true;

    input[1][1] = true;
    input[1][2] = true;

    input[2][2] = true;
    input[2][3] = true;

    //input[0][2] = true;

    int curTime = 1;
    int bestTime = m+1;
    vector<list<int> > curArrangement(m);
    vector<list<int> > bestArrangement(m);
    for(int i = 0; i < m; ++i) curArrangement[i].push_back(i);

    // 2. Solve
    ArrangeRecruitings(input, 1, curTime, curArrangement, bestTime, bestArrangement);

    // 3. Output the result
    cout << "Totoal Time: " << bestTime << endl;
    for(int i = 0; i < m; ++i)
    {
        cout << i << "): ";
        if(bestArrangement[i].empty())
        {
            cout << "none" << endl;
            continue;
        }
        for(list<int>::const_iterator it = bestArrangement[i].begin(); it != bestArrangement[i].end(); ++it)
            cout << *it << "-";

        cout << endl;
    }
}
