/*******************************
	��VC++6.0�У���Ԫ������Ȼ���ܷ���˽�б���
���ư���������VS2010�п��ԡ�
	���ԣ���vc++6.0�У��Ҿ�ʹ��
#include<iostream.h>�ˣ��Ͳ���
	std��
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
		cout<<"����Ϊ��"<<real<<"+"<<imag<<"i"<<endl;
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
	cout<<"������һ��������ʵ�����ֺ����������ÿո������"<<endl;
	cin>>c3;
	cout<<c3;
	return 0;
}
