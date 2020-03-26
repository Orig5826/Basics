#include <iostream>
#include <string>
#include <cctype>
using namespace std;

/*
    有些特性也是与时俱进的，C++也并非完全是老古董么
*/
int main()
{
    string line;
    while(getline(cin,line))
    {
        if(!line.empty())
        {
            // 方法1 [C]：for(auto i = 0; i < line.size(); i++)
            // 方法2 [C++]: iter迭代
            // 方法3 [C++11] 基于范围的For（Range-Based-For）。 类似于python中的for。更加方便的遍历方式
            for(auto &c : line) //此处采用3，并且c是一个引用。
            {
                c = toupper(c);
            }
            cout << line << endl;
        }
    }
    return 0;
}
