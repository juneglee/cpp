#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	Mat src1 = imread("images/lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("images/square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	// 영상의 비트 단위 논리 연산을 수행하는 bitwise_and(), bitwise_or(), bitwise_xor(), bitwise_not() 함수를 제공
	bitwise_and(src1, src2, dst1);
	bitwise_or(src1, src2, dst2);
	bitwise_xor(src1, src2, dst3);
	bitwise_not(src1, dst4);
	/*
	* 비트 단위 논리곱 
	* void bitwise_and(InputArray src1, InputArray src2,
                 OutputArray dst, InputArray mask = noArray());
	* 비트 단위 논리합 
	* void bitwise_or(InputArray src1, InputArray src2,
                 OutputArray dst, InputArray mask = noArray());
	* 비트 단위 배타적 논리합
	* void bitwise_xor(InputArray src1, InputArray src2,
                 OutputArray dst, InputArray mask = noArray());
	* 비트 단위 부정 연산
	* void bitwise_not(InputArray src1, OutputArray dst, InputArray mask = noArray());
			- src1 : 첫 번째 입력 행렬 또는 스칼라
			- src2 : 두 번째 입력 행렬 또는 스칼라. src1과 크기와 타입이 같아야 합니다.
			- dst  : 출력 행렬. src1과 같은 크기, 같은 타입으로 생성됩니다. dst 행렬 원소 값은 논리 연산 종류에 의해 각각 다르게 결정됩니다.
			- mask : 마스크 영상
	*/

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();

	return 0;
}