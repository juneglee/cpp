// �ݺ���(iteration statements)
// 1. while ��
// 2. do / while ��
// 3. for ��
// 4. ���� ����� for ��

#include <iostream>
using namespace std;

int main(void)
{
	int i = 0, w_num = 5;
	
	while (i < w_num)
	{
		cout << "while ��" << i + 1 << "��° �ݺ�" << endl;
		i++; // �� �κ��� �����ϸ� ���� ������ ������ �ȴ�
	}
	cout << "while ���� ����� �� ���� i�� �� : " << i << endl;

	int d = 0, do_num = 5;
	do {
		cout << "do / while ���� ���� " << d + 1 << " ��° �ݺ� �������Դϴ�." << endl;
		d++;  
	} while (d > do_num);
	cout << "do / while ���� ����� �� ���� i�� �� : " << d << endl;

	int f;
	int f_num = 5;
	for (f = 0; f < f_num; f++)
	{
		cout << "for ���� ���� " << f + 1 << " ��° �ݺ� �������Դϴ�." << endl;
	}
	cout << "for���� ����� �� ���� i�� �� : " << f << endl;

	int arr[5] = { 1, 3, 5, 7, 9 };

	// ���� ����� for ��
	// ���� ����� for ���� ǥ���� �ȿ� ���ԵǾ� �ִ� ��� ���� ���� �� ���� ������ ����
	for (int element : arr)
	{
		cout << element << " ";
	}
	return 0;

	return 0;
}