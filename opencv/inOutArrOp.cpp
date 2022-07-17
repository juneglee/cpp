#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/*
InputArray
InputArray Ÿ���� ���ڸ� ����ϴ� �Լ��� ���� �� �� ������, ������ ȭ�� ��� �Լ��� imshow() �Լ��� ������ InputArray Ÿ������ �����ϵ��� ����Ǿ� �ִ�. 
InputArray Ŭ������ Mat, vector<T> �� �پ��� Ÿ���� ǥ���� �� �ִ� �������̽� Ŭ�����μ� �ַ� OpenCV �Լ��� �Է� ���� �ڷ������� ���

OutputArray
OpenCV �Լ��� ������ �Է����� �޾� ���� ó���� �����ϰ�, �� ����� �ٽ� �������� �����Ͽ� ��ȯ
�̶� ��� ������ �Լ��� return �������� ��ȯ�ϴ� ���� �ƴ϶� ���� OutputArray Ŭ������ ������ �Լ� ���ڷ� ����Ͽ� ��� ������ ����
*/
void InputArrayOp();
void printMat(InputArray _mat);

int main(void)
{
	InputArrayOp();

	return 0;
}

void InputArrayOp()
{
	uchar data1[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat1(2, 3, CV_8UC1, data1);
	printMat(mat1);

	vector<float> vec1 = { 1.2f, 3.4f, -2.1f };
	printMat(vec1);
}

void printMat(InputArray _mat)
{
	Mat mat = _mat.getMat();
	cout << mat << endl;
}