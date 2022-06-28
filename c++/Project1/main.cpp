
// �ڷ��� (ũ�� ����, byte) Data Type
// ������ : char(1), short(2), int(4), long(4), long long(8)
// �Ǽ��� : float(4), double(8)

#define HUNGRY  0x001  
#define THIRSTY 0x002
#define TIRED   0x004
#define FIRE    0x008
#define COLD    0x010


// ������
// ������

// ���� ���� 
int global = 0;

int Add(int left, int right)
{
	return left + right;
}


int main()
{
	// int : �ڷ��� 
	// i : ������
	int i = 0;

	
	// 1����Ʈ�� ����� ǥ��
	// 256 ���� -> 0 ~ 255
	unsigned char c = 0; // unsigned ���� ���� 
	c = 0;
	c = 255;

	// 1 ����Ʈ�� ���, ���� �Ѵ� ǥ��
	// -128 ~ 0 ~ 127
	signed char c1 = 0; // signed ����� ������ ��� ���������� �����ص� �ȴ�
	c1 = 255;

	// ���� ���� ã�� (2�� ������)
	// �����Ǵ� ����� ��ȣ�� ���� ��, 1�� ���Ѵ�

	int a = 4 + 4.0; // ������ �������� �Ǽ��� �Ǽ�����, �ǵ����� �ʾ����� ����ȯ�� �Ͼ�� �ִ� 

	// ����ǥ�� ��İ� �Ǽ� ǥ�� ����� �ٸ��� 
	// �Ǽ� ǥ������� ���е��� �����Ѵ�
	// ���� double(8) �ڷ����� float(4) ���� �� �Ʒ��� �Ҽ������� ��Ȯ�ϰ� ǥ���� �����ϴ� 
	
	// �� ǥ�� ����� �� �����ڰ� ����� ��� ��������� ��ȯ����
	float f = 10.2415f + (float)20;


	// ������
	// ���� ������ =
	
	// ��� ������ 
	// + - * / % (��ⷯ��, ������, �� �����ڰ� ��� ����)
	// ++ -- // �Ѵܰ� ���� �Ǵ� ���� 
	int data = 10 + 10;
	data += 20;

	data = 10 % 3;
	data = (int)(10.f / 3.f); // 4����Ʈ float �� ������ 8����Ʈ double ������ .f�� ���


	data = 0;
	++data; // ����
	data--; // ����


	// ���� �����ڷ� ����ϴ� ���, ������ �켱������ ���� �������� �и���.
	data = 0;

	a = 10;
	data = ++a;
	data = a++;

	data = 0;
	data--; 
	data--; 

	// �� ������
	// ! (��), && (��, and) , || (��, or)
	// ��(true, 1), ����(false, 0)

	int trueflase = true;

	bool truef = false;
	bool IsTrue = 100;
	IsTrue = !IsTrue;

	IsTrue = 0 && 200;
	IsTrue = 0 || 0;

	// �� ������ 
	// == , != , < , >, <= , >=

	// ���� 
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

	// ���� ������ 
	// :?
	IsTrue == 20 ? IsTrue = 100 : IsTrue = 200;

	// ��Ʈ ������ 
	// ����Ʈ <<, >>
	unsigned char byte = 13;
	byte <<= 3; // 2^n ���
	byte >>= 2; // 2^n ���� ��

	// ��Ʈ �� (&), ��(|), xor(^), ���� (~)
	// ��Ʈ ������ ������ ����
	// & : �Ѵ� 1�� ��� 1
	// | : �� ���ϳ��� 1�̸� 1
	// ^ : ������ 0, �ٸ��� 1
	// ! : 1�� 0���� 0�� 1�� 

	unsigned int iStatus = 0;

	iStatus |= HUNGRY;
	iStatus |= THIRSTY;

	if (iStatus & THIRSTY)
	{
	}

	// Ư�� �ڸ� ��Ʈ ���� 
	iStatus &= ~THIRSTY;

	// ���� 
	// 1. ���� ����
	// 2. ���� ���� 
	// 3. ���� ���� 
	// 4. �ܺ� ���� 

	// ���� ���� 
	int iName = 0;
	// ��ȣ �ȿ� ����� ���� (�Լ�, ����)
	{
		//  ������ ��Ģ
		int iName = 100;
		iName;
		{
			{

			}
		}
	}

	// �Լ� 
	data = Add(10, 20);




	return 0;
}