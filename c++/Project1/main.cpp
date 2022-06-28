
// 자료형 (크기 단위, byte) Data Type
// 정수형 : char(1), short(2), int(4), long(4), long long(8)
// 실수형 : float(4), double(8)

#define HUNGRY  0x001  
#define THIRSTY 0x002
#define TIRED   0x004
#define FIRE    0x008
#define COLD    0x010


// 가독성
// 유지성

// 전역 변수 
int global = 0;

int Add(int left, int right)
{
	return left + right;
}


int main()
{
	// int : 자료형 
	// i : 변수명
	int i = 0;

	
	// 1바이트로 양수만 표현
	// 256 가진 -> 0 ~ 255
	unsigned char c = 0; // unsigned 양의 정수 
	c = 0;
	c = 255;

	// 1 바이트로 양수, 음수 둘다 표현
	// -128 ~ 0 ~ 127
	signed char c1 = 0; // signed 양수와 음수를 모두 포함하지만 생략해도 된다
	c1 = 255;

	// 음의 정수 찾기 (2의 보수법)
	// 대응되는 양수의 부호를 반전 후, 1을 더한다

	int a = 4 + 4.0; // 정수는 정수끼리 실수는 실수끼리, 의도하지 않았지만 형변환이 일어나고 있다 

	// 정수표현 방식과 실수 표현 방식은 다르다 
	// 실수 표현방식은 정밀도에 의존한다
	// 따라서 double(8) 자료형이 float(4) 보다 더 아래의 소수점까지 정확하게 표현이 가능하다 
	
	// 두 표현 방식의 피 연산자가 연산될 경우 명시적으로 변환하자
	float f = 10.2415f + (float)20;


	// 연산자
	// 대입 연산자 =
	
	// 산술 연산자 
	// + - * / % (모듈러스, 나머지, 피 연산자가 모두 정수)
	// ++ -- // 한단계 증가 또는 감소 
	int data = 10 + 10;
	data += 20;

	data = 10 % 3;
	data = (int)(10.f / 3.f); // 4바이트 float 로 볼껀지 8바이트 double 볼껀지 .f로 명시


	data = 0;
	++data; // 전위
	data--; // 후위


	// 후위 연산자로 사용하는 경우, 연산자 우선순위가 가장 나중으로 밀린다.
	data = 0;

	a = 10;
	data = ++a;
	data = a++;

	data = 0;
	data--; 
	data--; 

	// 논리 연산자
	// ! (역), && (곱, and) , || (합, or)
	// 참(true, 1), 거짓(false, 0)

	int trueflase = true;

	bool truef = false;
	bool IsTrue = 100;
	IsTrue = !IsTrue;

	IsTrue = 0 && 200;
	IsTrue = 0 || 0;

	// 비교 연산자 
	// == , != , < , >, <= , >=

	// 구문 
	// if, else
	data = 0;
	if (100 && 200)
	{
		data = 100;
	}

	if (data == 100) {
		// 
	}
	else if (100) {

	}
	else {
		// 
	}

	switch (10) 
	{
	case 10: // :
		break;
	case 20:
		break;
	default:
		break;
	}

	// 삼항 연산자 
	// :?
	IsTrue == 20 ? IsTrue = 100 : IsTrue = 200;

	// 비트 연산자 
	// 쉬프트 <<, >>
	unsigned char byte = 13;
	byte <<= 3; // 2^n 배수
	byte >>= 2; // 2^n 나눈 몫

	// 비트 곱 (&), 합(|), xor(^), 반전 (~)
	// 비트 단위로 연산을 진행
	// & : 둘다 1인 경우 1
	// | : 둘 중하나라도 1이면 1
	// ^ : 같으면 0, 다르면 1
	// ! : 1은 0으로 0은 1로 

	unsigned int iStatus = 0;

	iStatus |= HUNGRY;
	iStatus |= THIRSTY;

	if (iStatus & THIRSTY)
	{
	}

	// 특정 자리 비트 제거 
	iStatus &= ~THIRSTY;

	// 변수 
	// 1. 지역 변수
	// 2. 전역 변수 
	// 3. 정적 변수 
	// 4. 외부 변수 

	// 지역 변수 
	int iName = 0;
	// 괄호 안에 선언된 변수 (함수, 지역)
	{
		//  변수명 규칙
		int iName = 100;
		iName;
		{
			{

			}
		}
	}

	// 함수 
	data = Add(10, 20);




	return 0;
}