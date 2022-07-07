// 반복문(iteration statements)
// 1. while 문
// 2. do / while 문
// 3. for 문
// 4. 범위 기반의 for 문

#include <iostream>
using namespace std;

int main(void)
{
	int i = 0, w_num = 5;
	
	while (i < w_num)
	{
		cout << "while 문" << i + 1 << "번째 반복" << endl;
		i++; // 이 부분을 삭제하면 무한 루프에 빠지게 된다
	}
	cout << "while 문이 종료된 후 변수 i의 값 : " << i << endl;

	int d = 0, do_num = 5;
	do {
		cout << "do / while 문이 현재 " << d + 1 << " 번째 반복 수행중입니다." << endl;
		d++;  
	} while (d > do_num);
	cout << "do / while 문이 종료된 후 변수 i의 값 : " << d << endl;

	int f;
	int f_num = 5;
	for (f = 0; f < f_num; f++)
	{
		cout << "for 문이 현재 " << f + 1 << " 번째 반복 수행중입니다." << endl;
	}
	cout << "for문이 종료된 후 변수 i의 값 : " << f << endl;

	int arr[5] = { 1, 3, 5, 7, 9 };

	// 범위 기반의 for 문
	// 범위 기반의 for 문은 표현식 안에 포함되어 있는 모든 값에 대해 한 번씩 루프를 실행
	for (int element : arr)
	{
		cout << element << " ";
	}
	return 0;

	return 0;
}