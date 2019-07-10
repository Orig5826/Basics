
#include <stdio.h>

#define ORDER		10

double abs(double x)
{
	return x > 0 ? x : -x;
}

double power(double x, int n)
{
	double result = 1.0;

	for (int i = 0; i < (int)abs(n); i++)
	{
		result *= x;
	}

	if (n >= 0)
	{
		return result;
	}
	else
	{
		return 1.0 / result;
	}
}

long factorial(long n)
{
	long result = 1.0;
	for (long i = 1; i <= n; i++)
	{
		result *= i;
	}
	return result;
}

double exp(double x)
{
	double result = 0;
	for (int i = 0; i < ORDER; i++)
	{
		result += 1.0 / factorial(i) * power(x, i);
	}
	return result;
}

double cos(double x)
{
	double result = 0;
	for (int i = 0; i < ORDER; i+= 2)
	{
		if (i % 4 == 0)
		{
			result += 1.0 / factorial(i) * power(x, i);
		}
		else
		{
			result -= 1.0 / factorial(i) * power(x, i);
		}
	}
	return result;
}


double sin(double x)
{
	double result = 0;
	for (int i = 1; i < ORDER; i += 2)
	{
		if ((i - 1) % 4 == 0)
		{
			result += 1.0 / factorial(i) * power(x, i);
		}
		else
		{
			result -= 1.0 / factorial(i) * power(x, i);
		}
	}
	return result;
}

#define PI		3.1415926

void main()
{
	double result = 0.0;
	result = factorial(5);
	printf("result = %f\n", result);

	result = power(4, -2);
	printf("result = %f\n", result);

	result = exp(1);
	printf("result = %f\n", result);

	result = cos(PI);
	printf("result = %f\n", result);

	result = sin(PI/2);
	printf("result = %f\n", result);
}
