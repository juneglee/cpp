// 제어문(control flow statements)
// C++ 프로그램이 원하는 결과를 얻기 위해서는 프로그램의 순차적인 흐름을 제어해야만 할 경우가 생깁니다.
// 이때 사용하는 명령문을 제어문이라고 하며, 이러한 제어문에는 조건문, 반복문 등이 있습니다.
// 이러한 제어문에 속하는 명령문들은 중괄호({})로 둘러싸여 있으며, 이러한 중괄호 영역을 블록(block)이라고 합니다.

// 조건문(conditional statements)
// 1. if 문
// 2. if / else 문
// 3. if / else if / else 문
// 4. switch 문


#include <iostream>
using namespace std;


int main(void)
{
	int num = 5;

	if (num < 5)
	{
		//블록에 속한 명령문은 중괄호({})를 기준으로 오른쪽으로 들여쓰기가 되어 있는 것을 볼 수 있다.
		// 이처럼 들여쓰기를 통해 코드의 가독성을 높이는 것을 인덴트(indent)라고 하며, 될 수 있으면 모든 코드를 인덴트하는 것이 좋다
		cout << "입력하신 수는 5보다 작습니다." << endl;
	}
	else if (num == 5)
	{
		cout << "입력하신 수는 5입니다." << endl;
	}
	else
	{
		cout << "입력하신 수는 5보다 큽니다." << endl;
	}
	
	char ch = 'C';

	switch (ch)
	{
		case 'a':
		case 'A':
			cout << "이 학생의 학점은 A입니다." << endl;
			break;
		case 'b':
		case 'B':
			cout << "이 학생의 학점은 B입니다." << endl;
			break;
		case 'c':
		case 'C':
			cout << "이 학생의 학점은 C입니다." << endl;
			break;
		case 'd':
		case 'D':
			cout << "이 학생의 학점은 D입니다." << endl;
			break;
		case 'f':
		case 'F':
			cout << "이 학생의 학점은 F입니다." << endl;
			break;
		default:
			cout << "학점을 정확히 입력해 주세요!(A, B, C, D, F)" << endl;
			break;
	}

	return 0;
}