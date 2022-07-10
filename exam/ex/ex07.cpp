#include <stdio.h>


// 변수의 종류
// 1. 지역 변수 
// 2. 전역 변수 
// 3. 정젹 변수 (static)
// 4. 외부 변수 (extern)


// 메모리 영역
// 1. 스택 영역
// 2. 데이터 영역
// 3. 읽기 전용 (코드 , ROM)
// 4. 힙 영역


// 전역 변수 
int g_i = 0; // 데이터 영역

// 데이터 영역 특징
// 프로그램 시작 시 생성
// 프로그램 종료 시 해제

void Test()
{
	int i= 0;
	++i;

	++g_i;
 }

int main()
{
	Test();
	Test();
	Test();

	return 0;
}