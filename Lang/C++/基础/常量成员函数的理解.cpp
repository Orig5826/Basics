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
    // const 在成员函数后的作用：
    // 因this是隐式的，且默认情况下是指向类型非常量版本的常量指针
    // 本质上相当于是如下代码：
	// Sales_data * const this
    // 若对象实例化为const对象，则该函数调用失败。
    // （备注：类似于函数形参是string str，而你要直接传入"hello"的情况）
    // 因此我们想把this声明为如下代码：
    // const Sales_data * const this
    // 因此C++提出了将const放在函数后面的方式
    // 这样声明的函数称之为：“常量成员函数”
    // 在使用者看来，有以下两个作用：
    // 1. 不能通过this来修改成员变量
    // 2. 允许常量对象访问该成员函数
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
