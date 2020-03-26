#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

/**
    迭代器实现对有序序列的二分搜索
*/
int main()
{
    vector<int> data = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    vector<int>::iterator begin = data.begin();
    vector<int>::iterator end = data.end();
    vector<int>::iterator mid = begin + (end - begin)/2;

    for(auto d : data)
    {
        cout << d << " ";
    }
    cout << endl;

    int sought = 12;
    while(mid != end && *mid != sought)
    {
        cout << *mid << endl;

        if(sought < *mid)
        {
            end = mid;
        }
        else
        {
            begin = mid + 1;
        }
        mid = begin + (end - begin)/2;
    }
    cout << *mid << endl;

    return 0;
}
