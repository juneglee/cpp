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

	// 상수화
	// l-value : 변수
	// r-value : 상수 
	int a = 0;
	int* pInt = &a;
	int ii = 10;
	
	*pInt = 1;
	pInt = nullptr;

	// ------------
	// const 포인터
	const int* pConstInt = &a;
	// *pConstInt = 100;

	int b = 0;
	pConstInt = &b; 

	// ------------
	// 포인터 const
	int* const pIntConst = &a;

	*pIntConst = 400;
	// pConstInt = &b;

	// ------------
	// 초기화 시 가리킨 대상만 가리킴, 가리키는 원본을 수정 할 수 없음
	// 두가지 기능을 동시에 사용이 가능하다 
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
	// 단축키 : ctrl + shift + space

	// void 
	// 1. 원본의 자료형을 정하지 않음
	// 2. 어떠한 타입의 변수의 주소든 다 저장 가능
	// 3. 역참조 불가능
	// 4. 주소 연산 불가능
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