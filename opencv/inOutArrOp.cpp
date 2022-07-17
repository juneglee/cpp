#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/*
InputArray
InputArray 타입의 인자를 사용하는 함수를 자주 볼 수 있으며, 영상의 화면 출력 함수인 imshow() 함수도 영상을 InputArray 타입으로 전달하도록 선언되어 있다. 
InputArray 클래스는 Mat, vector<T> 등 다양한 타입을 표현할 수 있는 인터페이스 클래스로서 주로 OpenCV 함수의 입력 인자 자료형으로 사용

OutputArray
OpenCV 함수는 영상을 입력으로 받아 영상 처리를 수행하고, 그 결과를 다시 영상으로 생성하여 반환
이때 출력 영상을 함수의 return 구문으로 반환하는 것이 아니라 보통 OutputArray 클래스의 참조를 함수 인자로 사용하여 결과 영상을 전달
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