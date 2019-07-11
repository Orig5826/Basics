/*******************************
	在VC++6.0中，友元函数居然不能访问私有变量
郁闷啊，可是在VS2010中可以。
	所以，在vc++6.0中，我就使用
#include<iostream.h>了，就不用
	std了
********************************/

#include<iostream.h>
#include<math.h>
//using namespace std;

class Complex
{
private:
	double real,imag;
public:
	Complex(double real = 0,double imag = 0)
	{
		this->real=real;
		this->imag=imag;
	}

	Complex operator + (Complex complex);
	Complex operator - (Complex complex);
	Complex operator * (Complex complex);
	Complex operator / (Complex complex);
	Complex operator = (Complex complex);

	friend istream & operator >>(istream &input,Complex &c);
	friend ostream & operator <<(ostream &output,Complex &c);

	void show()
	{
		cout<<"复数为："<<real<<"+"<<imag<<"i"<<endl;
	}
} ;

Complex Complex::operator + (Complex complex)
{
	return Complex(real+complex.real,imag+complex.imag);
}

Complex Complex::operator - (Complex complex)
{
	return Complex(real-complex.real,imag-complex.imag);
}
Complex Complex::operator * (Complex complex)
{
	Complex c;
	c.real=real*complex.real-imag*complex.imag;
	c.imag=real*complex.imag+imag*complex.real;
	return c;
}

Complex Complex::operator / (Complex complex)
{
	Complex c;
	c.real=(real*complex.real+imag*complex.imag)/(pow(complex.real,2)+pow(complex.imag,2));
	c.imag=(complex.real*imag-real*complex.imag)/(pow(complex.real,2)+pow(complex.imag,2));
	return c;
}

Complex Complex::operator = (Complex complex)
{
	real=complex.real;
	imag=complex.imag;
	return complex;
}

istream & operator >>(istream &input,Complex &c)
{
	input>>c.real>>c.imag;
	return input;
}

ostream & operator <<(ostream &output,Complex &c)
{
	output<<"("<<c.real<<"+"<<c.imag<<"i)"<<endl;
	return output;
}

int main()
{
	Complex c1(1,2),c2(3,4),c3;
	cout<<"c1_";
	c1.show();
	cout<<"c2_";
	c2.show();

	c3=c1+c2;
	cout<<"c1+c2__";
	c3.show();

	c3=c1-c2;
	cout<<"c1-c2__";
	c3.show();

	c3=c1*c2;
	cout<<"c1*c2__";
	c3.show();

	c3=c1/c2;
	cout<<"c1/c2__";
	c3.show();

	cout<<c3;
	cout<<"请输入一个复数，实数部分和虚数部分用空格隔开："<<endl;
	cin>>c3;
	cout<<c3;
	return 0;
}
