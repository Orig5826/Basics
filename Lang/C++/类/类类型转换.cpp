#include<iostream>
using namespace std;
class Test
{
private:
	int a;
public:
	Test(int a)
	{
		Test::a=a;
	}
	
	operator int()
	{
		return Test::a;
	}

} ;

int main()
{
	Test a(99);
	cout<<a<<endl;
	cout<<(int)a<<endl;
	return 0;
}