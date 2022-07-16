#include <iostream>
#include <vector>
#include <string>

using namespace std;

// std::vector<typename> var_name;
/*
 vector�� C++ template �������� ������� Ŭ�����̹Ƿ� ���� ����� typename�� �����ؾ� �Ѵ� 
 <vector> ��� ���� �߰� �ʿ� (#include <vector>) 
 std ���ӽ����̽� ��� (using namespace std;)
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

// �ֿ� vector ����
/*
vector<T> v1; // TŸ���� ������ ���� v1 ����, v1�� ���� ��� ����
 vector<T> v2(v1); // v1 �� �����Ͽ� v2 �� ����

vector<T> v3(n); // T Ÿ�� ��ü n�� ������ v3�� ����
vector<T> v4(n, val); // T Ÿ�� ��ü n�� �����ϰ� val�� �ʱ�ȭ

vector<T> v5{a, b, c, ....}; // {}���� ���ҷ� �ʱ�ȭ
vector<T> v6 = {a, b, c, ....};  //v5�� ���� 

v[n]; // n��° ���ҿ� ����, v.at(n); �� ����

v.empty() // v�� ��� ������ true�� ��ȯ
v.size() // v�� ���ԵǾ� �ִ� ���� ������ ��ȯ
v.capacity() // v�� ��� �뷮�� ��ȯ

v.push_back(a): // v �� �ڿ� ���ο� ���� a�� �߰�

v1 = v2; // v2�� �����Ͽ� v1�� ���� (���� ���� )
v1 = { a, b, c, .... }; // v1�� {} ��ȣ �� �����ͷ� ��ü 
*/