#include <stdio.h>

//  함수
// Factorial 

int Factorial(int _iNum)
{
	// int i = 2;
	int iValue = 1;

	for (int j = 0; j < _iNum - 1; ++j)
	{
		iValue *= (j + 2);
	}

	return iValue;
}

// 재귀함수 
// 가독성, 구현의 용이
int Factorial_Re(int _iNum)
{
	if (1 == _iNum)
	{
		return 1;
	}

	return _iNum * Factorial_Re(_iNum - 1);
}

// 피보나치 수열
int Fibornacci(int _iNum)
{
	if (1 == _iNum || 2 == _iNum)
	{
		return 1;
	}
	int iPrev1 = 1;
	int iPrev2 = 2;
	int iValue = 0;

	for (int i = 0; i < _iNum - 2; ++i)
	{
		iValue = iPrev1 + iPrev2;
		iPrev1 = iPrev2;
		iPrev2 = iValue;
	}

	return iValue;
}

int Fibornacci_Re(int _iNum)
{
	if (1 == _iNum || 2 == _iNum)
	{
		return 1;
	}

	return Fibornacci_Re(_iNum - 1) + Fibornacci_Re(_iNum - 2);
}


int ex05()
{
	int iValue = Factorial(4);
	iValue = Factorial(10);
	iValue = Factorial_Re(10);

	iValue = Fibornacci(7);
	iValue = Fibornacci_Re(8);

	// 배열 
	int iArray[10] = {};

	iArray[4] = 10;

	int iData = 100;

	int iArray2[100] = {};

	return 0;

}