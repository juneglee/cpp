#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/*
Vec
�ϳ��� �����θ� �̷���� ����� �� ���Ͷ�� �θ���, �ϳ��� ���θ� ������ ����� �� ���Ͷ�� �θ��� 
�׸��� �� ���Ϳ� �� ���͸� ���ļ� ���� �Ǵ� ���� ����̶�� �θ��� 
���ʹ� ���� �ڷ����� ���� ���� �� ���� ������ ������ �����̶�� �� �� �ִ� 

Scalar Ŭ����
scalar Ŭ������ 4ä�� ������ ���󿡼� �ȼ� ���� ǥ���ϴ� �뵵�� ���� ���ȴ�. ��� scalar Ŭ������ scalar ��� �̸��� Ŭ���� ���ø� �̸��� �������̸�, 
scalar Ŭ������ vec Ŭ������ ��ӹ޾� ����� ����.
*/
void VecOp();
void ScalarOp();

int main(void)
{
	VecOp();
	ScalarOp();

	return 0;
}

void VecOp()
{
	Vec3b p1, p2(0, 0, 255);
	p1[0] = 100;
	cout << "p1: " << p1 << endl; // p1: [100, 0, 0]
	cout << "p2: " << p2 << endl; // p2 : [0, 0, 255]
}

void ScalarOp()
{
	Scalar gray = 128;
	cout << "gray: " << gray << endl; // gray: [128, 0, 0, 0]

	Scalar yellow(0, 255, 255);
	cout << "yellow: " << yellow << endl; // yellow: [0, 255, 255, 0]

	Mat img1(256, 256, CV_8UC3, yellow);

	for (int i = 0; i < 4; i++)
		cout << yellow.val[i] << ", " << yellow[i] << endl;
	/*
	0, 0
	255, 255
	255, 255
	0, 0
	*/
}