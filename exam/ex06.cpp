#include <stdio.h>

// 사용자 정의 자료형
typedef struct _tagMyst
{
	int a;
	float f;
}Myst;

typedef struct _tagBig
{
	Myst k;
	int i;
	float c;
}Big;

typedef int INT;



int main()
{
	int arr[10] = { 1,2,3,4,5,6 };
	// 구조체
	Myst t = {100, 3.14f};
	t.a = 10;
	t.f = 10.2312f;

	int iSzie = sizeof(Myst);

	INT a;

	return 0;

}