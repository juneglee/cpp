#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/*
Vec
하나의 행으로만 이루어지 행렬을 행 벡터라고 부르고, 하나의 열로만 구성된 행렬은 열 벡터라고 부른다 
그리고 행 벡터와 열 벡터를 합쳐서 벡터 또는 벡터 행렬이라고 부른다 
벡터는 같은 자료형을 가진 원소 몇 개로 구성된 데이터 형식이라고 볼 수 있다 

Scalar 클래스
scalar 클래스는 4채널 이하의 영상에서 픽셀 값을 표현하는 용도로 자주 사용된다. 사실 scalar 클래스는 scalar 라는 이름의 클래스 템플릿 이름의 재정이이며, 
scalar 클래슨는 vec 클래스를 상속받아 만들어 졌다.
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