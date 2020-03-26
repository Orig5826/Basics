#include <iostream>
#include <string>
#include <cctype>
using namespace std;

/*
    ��Щ����Ҳ����ʱ����ģ�C++Ҳ������ȫ���ϹŶ�ô
*/
int main()
{
    string line;
    while(getline(cin,line))
    {
        if(!line.empty())
        {
            // ����1 [C]��for(auto i = 0; i < line.size(); i++)
            // ����2 [C++]: iter����
            // ����3 [C++11] ���ڷ�Χ��For��Range-Based-For���� ������python�е�for�����ӷ���ı�����ʽ
            for(auto &c : line) //�˴�����3������c��һ�����á�
            {
                c = toupper(c);
            }
            cout << line << endl;
        }
    }
    return 0;
}
