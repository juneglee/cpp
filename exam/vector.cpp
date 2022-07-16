#include <iostream>
#include <vector>
#include <string>

using namespace std;

// std::vector<typename> var_name;
/*
 vector는 C++ template 문법으로 만들어진 클래스이므로 변수 선언시 typename을 지정해야 한다 
 <vector> 헤더 파일 추가 필요 (#include <vector>) 
 std 네임스페이스 사용 (using namespace std;)
*/

vector<int> func()
{
	vector<int> v{ -10, -20 };
	return v;
}

int main()
{
	vector<int> a;
	a.push_back(10);
	a.push_back(20);
	a.push_back(30);
	a.push_back(40);

	for (int i = 0; i < a.size(); i++)
		cout << a[i] << endl;

	vector<string> b{ "I", "love", "you" };
	b.push_back("!!!");

	for (int i = 0; i < b.size(); i++)
		cout << b[i] << endl;

	vector<int> c(a.begin(), a.begin() + 3);

	for (int i = 0; i < c.size(); i++)
		cout << c.at(i) << endl;

	a.clear();
	cout << "a.size: " << a.size() << endl;

	vector<int> d = func();

	for (int i = 0; i < d.size(); i++)
		cout << d[i] << endl;

	return 0;
}

// 주요 vector 사용법
/*
vector<T> v1; // T타입을 지정할 벡터 v1 생성, v1은 현재 비어 있음
 vector<T> v2(v1); // v1 을 복사하여 v2 를 생성

vector<T> v3(n); // T 타입 객체 n을 저장할 v3을 생성
vector<T> v4(n, val); // T 타입 객체 n을 저장하고 val로 초기화

vector<T> v5{a, b, c, ....}; // {}안의 원소로 초기화
vector<T> v6 = {a, b, c, ....};  //v5와 동일 

v[n]; // n번째 원소에 접근, v.at(n); 과 같음

v.empty() // v가 비어 있으면 true를 반환
v.size() // v에 포함되어 있는 원소 개수를 반환
v.capacity() // v의 허용 용량을 반환

v.push_back(a): // v 맨 뒤에 새로운 원소 a를 추가

v1 = v2; // v2를 복사하여 v1에 대입 (깊은 복사 )
v1 = { a, b, c, .... }; // v1을 {} 괄호 안 데이터로 교체 
*/