// 루프의 제어 
// 일반적으로 조건식의 검사를 통해 루프로 진입하면, 다음 조건식을 검사하기 전까지 루프 안에 있는 모든 명령문을 실행합니다.
// 하지만 continue 문과 break 문은 이러한 일반적인 루프의 흐름을 사용자가 직접 제어

#include <iostream>
using namespace std;

int main(void)
{
	// continue 문
	// continue 문은 루프 내에서 사용하여 해당 루프의 나머지 부분을 건너뛰고, 바로 다음 조건식의 판단으로 넘어가게 해줍니다.
	// 보통 반복문 내에서 특정 조건에 대한 예외 처리를 하고자 할 때 자주 사용됩
	int except_num = 2;

	for (int i = 0; i <= 100; i++)
	{
		if (i % except_num == 0)
		{
			continue;
		}
		cout << i << endl;
	}

	// break 문
	// break 문은 루프 내에서 사용하여 해당 반복문을 완전히 종료시킨 뒤, 반복문 바로 다음에 위치한 명령문을 실행합니다.
	// 즉 루프 내에서 조건식의 판단 결과와 상관없이 반복문을 완전히 빠져나가고 싶을 때 사용
	int num = 1, sum = 0;
	int end_num = 10;

	while (1) // 무한 루프 
	{
		sum += num;
		if (num == end_num)
		{
			break;
		}
		num++;
	}
	cout << "1부터 " << end_num << "까지 더한 값은 " << sum << "입니다.";


	return 0;
}