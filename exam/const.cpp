#include <stdlib.h>
#include <stdio.h>

void Output(const int * pI)
{
	int i = *pI;
	// int* pInt = (int*)pI;
	// *pInt = 1000;
}
 

int main()
{
	// 1. const 
	const int cint = 100;

	// ���ȭ
	// l-value : ����
	// r-value : ��� 
	int a = 0;
	int* pInt = &a;
	int ii = 10;
	
	*pInt = 1;
	pInt = nullptr;

	// ------------
	// const ������
	const int* pConstInt = &a;
	// *pConstInt = 100;

	int b = 0;
	pConstInt = &b; 

	// ------------
	// ������ const
	int* const pIntConst = &a;

	*pIntConst = 400;
	// pConstInt = &b;

	// ------------
	// �ʱ�ȭ �� ����Ų ��� ����Ŵ, ����Ű�� ������ ���� �� �� ����
	// �ΰ��� ����� ���ÿ� ����� �����ϴ� 
	const int* const pConstIntConst = nullptr;

	{
		int a = 0;
		const int* pInt = &a;
		
		// *pInt = 100;
		// a = 100; 

		int* p = &a;
		*p = 100;
	}

	a = 100;
	Output(&a);
	// ����Ű : ctrl + shift + space

	// void 
	// 1. ������ �ڷ����� ������ ����
	// 2. ��� Ÿ���� ������ �ּҵ� �� ���� ����
	// 3. ������ �Ұ���
	// 4. �ּ� ���� �Ұ���
	void* pVoid = nullptr;
	float* pFloat = nullptr;
	{
		int a = 0;
		float f = 0.f;
		double d = 0.;
		long long ll = 0;

		pVoid = &a;
		pVoid = &f;
		pVoid = &d;
		pVoid = &ll;

		// *pVloid;
		// pVoid + 1;
	}


	return 0;

}