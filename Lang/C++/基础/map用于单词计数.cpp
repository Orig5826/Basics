#include <iostream>
#include <string>
#include <map>
using namespace std;

template <typename T>
T orig_max(const T &v1, const T &v2)
{
    return (v1>v2)?(v1):(v2);
}

int main()
{
#if 0
    map<string,size_t> word_count;
    map<string,size_t>::iterator iter;
    string word;

    while(cin >> word)
    {
        ++word_count[word];
    }

    cout << "counting statistics" << endl;
    for(iter = word_count.begin(); iter != word_count.end(); iter++)
    {
        cout << iter->first << " : " << iter->second <<endl;
    }
#endif // 0

    cout << orig_max(1,2) << endl;
    string s1="abc",s2="adc";
    cout << orig_max(s1,s2) << endl;

    return 0;
}
