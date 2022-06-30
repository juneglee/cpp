#include <stdio.h>

//  ÇÔ¼ö
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

int main()
{
	int iValue = Factorial(4);

	iValue = Factorial(10);

	return 0;

}