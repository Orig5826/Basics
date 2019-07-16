#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	double real;
	double imag;
}Complex,* pComplex;

void Display(pComplex pC)
{
	printf("%.0f + i%.0f\t",pC->real,pC->imag);
}

pComplex Complex_Add(const Complex C1,const Complex C2)
{
	pComplex pC = (pComplex)malloc(sizeof(Complex));
	pC->real = C1.real + C2.real;
	pC->imag = C1.imag + C2.imag;
	return pC;
}

pComplex Complex_Sub(const Complex C1,const Complex C2)
{
	pComplex pC = (pComplex)malloc(sizeof(Complex));
	pC->real = C1.real - C2.real;
	pC->imag = C1.imag - C2.imag;
	return pC;
}

pComplex Complex_Mul(const Complex C1,const Complex C2)
{
	pComplex pC = (pComplex)malloc(sizeof(Complex));
	pC->real = (C1.real * C2.real) - (C1.imag * C2.imag);
	pC->imag = C1.real * C2.imag + C1.imag * C2.real;
	return pC;
}

pComplex Complex_Div(const Complex C1,const Complex C2)
{
	pComplex pC = (pComplex)malloc(sizeof(Complex));
	pC->real = (C1.real * C2.real) + (C1.imag * C2.imag);
	pC->imag = -C1.real * C2.imag + C1.imag * C2.real;
	return pC;
}

void main(void )
{
	Complex a[2] = {1,2,3,4};
	printf("a1=");
	Display(&a[0]);
	printf("a2=");
	Display(&a[1]);
	printf("\n");	printf("ADD:");
	Display(Complex_Add(a[0],a[1]));
	printf("\n");	printf("SUB:");	  	   
	Display(Complex_Sub(a[0],a[1]));
	printf("\n");	printf("MUL:");	  	   
	Display(Complex_Mul(a[0],a[1]));
	printf("\n");	printf("DIV:");	  	   
	Display(Complex_Div(a[0],a[1]));
	printf("\n");		  
}