#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

//extern int Number;  ///< int 형 Number가 어디선가 정의 될 것이라는 선언, extern은 전역
//int nCount;         ///< int 형 자료를 저장할 수 있는 nCount 변수(메모리 공간)를 정의

//초기화(initialization)
// int n = 10;     ///< (1) int 형 n 을 만들고 10으로 초기화한다.
// int n(10);      ///< (2) int 형 n 을 만들고 10으로 초기화한다.
// int n{ 10 };    ///< (4) int 형 n 을 만들고 10으로 초기화한다.
// int n = { 10 }; ///< (3) int 형 n 을 만들고 10으로 초기화한다. { } 를 사용하는 경우 '='은 사용하지 않는 것이 좋다. 이유는 auto 참고
/*
int i = 3.14;   ///< implicit narrowing conversions
int j { 3.14 }; ///< error
*/

// 대입(assignment)
// 대입은 변수 정의로 만들어진 메모리 공간에 값을 설정하는 것이다. assignment 는 대입, 설정, 할당 등의 의미로 해석된다. 
// int n;    // define a variable
// n = 10;   // assign a value to a variable

// const, constexpr
// const 
/*
- const: "값을 변경하지 않을 것을 약속". 이것은 어딘가에서 데이터가 변경되는 것에 대한 
염려 없이 포인터 및 참조를 사용하여 함수로 전달할 수 있도록 인터페이스를 지정하는 데 사용된다.
컴파일러는 const에 의한 약속을 강제 한다. const 값은 런타임에 계산할 수 있다.
- constexpr: "컴파일타임에 평가되어야 함을 의미". 이것은 주로 상수를 지정하고 읽기 전용 메모리에 
데이터를 배치할 수 있게하며 성능을 위해 사용된다. constexpr의 값은 컴파일 타임에 계산된다.
*/

//
//const int num = 5;         // 상수 정수형 num에 5를 저장
//constexpr int var = 10;    // 상수표현식 정수형 var에 10을 저장
//
//double fnStDev(const vector<double>&);
//double fnMean(const vector<double>&);
//
//vector<double> vecDbl{ 1.3, 2.4, 1., 2.7, 3.2, 1.8, 2.9 };
//const double stdev = fnStDev(vecDbl);   // 런타임에 fnStDev 리턴 값으로 상수 정의
//// constexpr double mean = fnMean(vecDbl); // error, fnMean이 constexpr이 아니다.
//
//constexpr double square(double x) { return x * x; }
//
//constexpr double area1 = 3.14 * square(5);       // 3.14*square(5)는 상수표현식이다.
//constexpr double area2 = 3.14 * square(var);      // error: var가 변수라면 상수표현식이 아니다. 상수라면 가능하다.
//const double area3 = 3.14 * square(var);          // 런타임에 계산된 값을 상수로 정의한다.


int& func(int& n) { n = 10;    return n; }
int main()
{
    // lvalue, xvalue, glvalue, rvalue, prvalue 개념
    /*
    - lvalue("left" value)는 함수 또는 객체를 말한다.
    [예 : p가 포인터 유형의 표현식 인 경우 *p는 p가 가리키는 객체 또는 함수를 참조하는 lvalue 표현식이다.
    또 다른 예로, 반환 유형이 lvalue 참조인 함수를 호출 한 결과는 lvalue이다.]
    - xvalue( "eXpiring" value)는 일반적으로 수명이 거의 끝나가는 객체를 나타낸다.
    xvalue는 rvalue 참조와 관련된 특정 종류의 표현식의 결과이다.
    [예 : 반환 유형이 rvalue 참조인 함수를 호출한 결과는 xvalue이다.
    - glvalue( "generalized" lvalue)는 lvalue 또는 xvalue이다.
    - rvalue("right" value, 할당 표현식의 오른쪽에 나타날 수 있기 때문)는 xvalue,
    임시 객체 또는 하위 객체 또는 객체와 연관되지 않은 값이다.
    - prvalue ( "pure" rvalue)는 xvalue가 아닌 rvalue이다.
    [예 : 반환 유형이 참조가 아닌 함수를 호출 한 결과는 prvalue이다.]
    */
    int n1 = 5, n2 = 0;
    int* p = &n1;
    n2 = func(n1);
    printf("n1 = %d, n2 = %d\n", n1, n2);
    printf("&n1 = %p, p = %p, *p = %d\n", &n1, p, *p);
}