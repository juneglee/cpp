#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

//extern int Number;  ///< int �� Number�� ��𼱰� ���� �� ���̶�� ����, extern�� ����
//int nCount;         ///< int �� �ڷḦ ������ �� �ִ� nCount ����(�޸� ����)�� ����

//�ʱ�ȭ(initialization)
// int n = 10;     ///< (1) int �� n �� ����� 10���� �ʱ�ȭ�Ѵ�.
// int n(10);      ///< (2) int �� n �� ����� 10���� �ʱ�ȭ�Ѵ�.
// int n{ 10 };    ///< (4) int �� n �� ����� 10���� �ʱ�ȭ�Ѵ�.
// int n = { 10 }; ///< (3) int �� n �� ����� 10���� �ʱ�ȭ�Ѵ�. { } �� ����ϴ� ��� '='�� ������� �ʴ� ���� ����. ������ auto ����
/*
int i = 3.14;   ///< implicit narrowing conversions
int j { 3.14 }; ///< error
*/

// ����(assignment)
// ������ ���� ���Ƿ� ������� �޸� ������ ���� �����ϴ� ���̴�. assignment �� ����, ����, �Ҵ� ���� �ǹ̷� �ؼ��ȴ�. 
// int n;    // define a variable
// n = 10;   // assign a value to a variable

// const, constexpr
// const 
/*
- const: "���� �������� ���� ���� ���". �̰��� ��򰡿��� �����Ͱ� ����Ǵ� �Ϳ� ���� 
���� ���� ������ �� ������ ����Ͽ� �Լ��� ������ �� �ֵ��� �������̽��� �����ϴ� �� ���ȴ�.
�����Ϸ��� const�� ���� ����� ���� �Ѵ�. const ���� ��Ÿ�ӿ� ����� �� �ִ�.
- constexpr: "������Ÿ�ӿ� �򰡵Ǿ�� ���� �ǹ�". �̰��� �ַ� ����� �����ϰ� �б� ���� �޸𸮿� 
�����͸� ��ġ�� �� �ְ��ϸ� ������ ���� ���ȴ�. constexpr�� ���� ������ Ÿ�ӿ� ���ȴ�.
*/

//
//const int num = 5;         // ��� ������ num�� 5�� ����
//constexpr int var = 10;    // ���ǥ���� ������ var�� 10�� ����
//
//double fnStDev(const vector<double>&);
//double fnMean(const vector<double>&);
//
//vector<double> vecDbl{ 1.3, 2.4, 1., 2.7, 3.2, 1.8, 2.9 };
//const double stdev = fnStDev(vecDbl);   // ��Ÿ�ӿ� fnStDev ���� ������ ��� ����
//// constexpr double mean = fnMean(vecDbl); // error, fnMean�� constexpr�� �ƴϴ�.
//
//constexpr double square(double x) { return x * x; }
//
//constexpr double area1 = 3.14 * square(5);       // 3.14*square(5)�� ���ǥ�����̴�.
//constexpr double area2 = 3.14 * square(var);      // error: var�� ������� ���ǥ������ �ƴϴ�. ������ �����ϴ�.
//const double area3 = 3.14 * square(var);          // ��Ÿ�ӿ� ���� ���� ����� �����Ѵ�.


int& func(int& n) { n = 10;    return n; }
int main()
{
    // lvalue, xvalue, glvalue, rvalue, prvalue ����
    /*
    - lvalue("left" value)�� �Լ� �Ǵ� ��ü�� ���Ѵ�.
    [�� : p�� ������ ������ ǥ���� �� ��� *p�� p�� ����Ű�� ��ü �Ǵ� �Լ��� �����ϴ� lvalue ǥ�����̴�.
    �� �ٸ� ����, ��ȯ ������ lvalue ������ �Լ��� ȣ�� �� ����� lvalue�̴�.]
    - xvalue( "eXpiring" value)�� �Ϲ������� ������ ���� �������� ��ü�� ��Ÿ����.
    xvalue�� rvalue ������ ���õ� Ư�� ������ ǥ������ ����̴�.
    [�� : ��ȯ ������ rvalue ������ �Լ��� ȣ���� ����� xvalue�̴�.
    - glvalue( "generalized" lvalue)�� lvalue �Ǵ� xvalue�̴�.
    - rvalue("right" value, �Ҵ� ǥ������ �����ʿ� ��Ÿ�� �� �ֱ� ����)�� xvalue,
    �ӽ� ��ü �Ǵ� ���� ��ü �Ǵ� ��ü�� �������� ���� ���̴�.
    - prvalue ( "pure" rvalue)�� xvalue�� �ƴ� rvalue�̴�.
    [�� : ��ȯ ������ ������ �ƴ� �Լ��� ȣ�� �� ����� prvalue�̴�.]
    */
    int n1 = 5, n2 = 0;
    int* p = &n1;
    n2 = func(n1);
    printf("n1 = %d, n2 = %d\n", n1, n2);
    printf("&n1 = %p, p = %p, *p = %d\n", &n1, p, *p);
}