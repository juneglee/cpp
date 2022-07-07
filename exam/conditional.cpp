// ���(control flow statements)
// C++ ���α׷��� ���ϴ� ����� ��� ���ؼ��� ���α׷��� �������� �帧�� �����ؾ߸� �� ��찡 ����ϴ�.
// �̶� ����ϴ� ��ɹ��� ����̶�� �ϸ�, �̷��� ������� ���ǹ�, �ݺ��� ���� �ֽ��ϴ�.
// �̷��� ����� ���ϴ� ��ɹ����� �߰�ȣ({})�� �ѷ��ο� ������, �̷��� �߰�ȣ ������ ���(block)�̶�� �մϴ�.

// ���ǹ�(conditional statements)
// 1. if ��
// 2. if / else ��
// 3. if / else if / else ��
// 4. switch ��


#include <iostream>
using namespace std;


int main(void)
{
	int num = 5;

	if (num < 5)
	{
		//��Ͽ� ���� ��ɹ��� �߰�ȣ({})�� �������� ���������� �鿩���Ⱑ �Ǿ� �ִ� ���� �� �� �ִ�.
		// ��ó�� �鿩���⸦ ���� �ڵ��� �������� ���̴� ���� �ε�Ʈ(indent)��� �ϸ�, �� �� ������ ��� �ڵ带 �ε�Ʈ�ϴ� ���� ����
		cout << "�Է��Ͻ� ���� 5���� �۽��ϴ�." << endl;
	}
	else if (num == 5)
	{
		cout << "�Է��Ͻ� ���� 5�Դϴ�." << endl;
	}
	else
	{
		cout << "�Է��Ͻ� ���� 5���� Ů�ϴ�." << endl;
	}
	
	char ch = 'C';

	switch (ch)
	{
		case 'a':
		case 'A':
			cout << "�� �л��� ������ A�Դϴ�." << endl;
			break;
		case 'b':
		case 'B':
			cout << "�� �л��� ������ B�Դϴ�." << endl;
			break;
		case 'c':
		case 'C':
			cout << "�� �л��� ������ C�Դϴ�." << endl;
			break;
		case 'd':
		case 'D':
			cout << "�� �л��� ������ D�Դϴ�." << endl;
			break;
		case 'f':
		case 'F':
			cout << "�� �л��� ������ F�Դϴ�." << endl;
			break;
		default:
			cout << "������ ��Ȯ�� �Է��� �ּ���!(A, B, C, D, F)" << endl;
			break;
	}

	return 0;
}