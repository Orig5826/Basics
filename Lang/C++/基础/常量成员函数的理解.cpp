#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

class Sales_data
{
    public:
    Sales_data(string num)
    {
        this->book_num = num;
    }
    // const �ڳ�Ա����������ã�
    // ��this����ʽ�ģ���Ĭ���������ָ�����ͷǳ����汾�ĳ���ָ��
    // �������൱�������´��룺
	// Sales_data * const this
    // ������ʵ����Ϊconst������ú�������ʧ�ܡ�
    // ����ע�������ں����β���string str������Ҫֱ�Ӵ���"hello"�������
    // ����������this����Ϊ���´��룺
    // const Sales_data * const this
    // ���C++����˽�const���ں�������ķ�ʽ
    // ���������ĺ�����֮Ϊ����������Ա������
    // ��ʹ���߿������������������ã�
    // 1. ����ͨ��this���޸ĳ�Ա����
    // 2. ������������ʸó�Ա����
    string isbn() //const
    {
        // this->book_num = "Hello";
        return this->book_num;
    }
    private:
        string book_num;
};

int main()
{
    // const Sales_data book("book1");
    Sales_data book("book1");
    cout << book.isbn() << endl;
    return 0;
}
