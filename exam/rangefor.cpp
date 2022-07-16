#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
범위 기반 for 루프 형식
for (declaration : expression)
	loop-statement
*/

int main()
{
	vector<int> ages{ 20, 30, 40, 50 };

	for (int i = 0; i < ages.size(); i++) {
		int age = ages[i];
		cout << age << endl;
	}

	for (int age : ages)
		cout << age << endl;

	for (auto& age : ages)
		cout << age << endl;

	string str[] = { "I", "love", "you" };

	for (auto& s : str)
		cout << s << endl;

	return 0;
}