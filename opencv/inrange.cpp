#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int lower_hue = 40, upper_hue = 80;
Mat src, src_hsv, mask;

void on_hue_changed(int, void*);

// 색상 범위 지정에 의한 영역 분할
// HSV 색 공간에서 inRange() 함수를 이용하여 사용자가 지정한 색상 영역을 검출
// 예를 들어 입력 영상에서 빨간색 픽셀을 모두 찾아내면 빨간색 객체의 위치와 크기를 알 수 있다.
int main(int argc, char* argv[])
{
	src = imread("images/candies.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	cvtColor(src, src_hsv, COLOR_BGR2HSV);

	imshow("src", src);

	namedWindow("mask");
	// 색상의 하한 값과 상한 값을 조절할 수 있는 두 개의 트랙바를 생성
	// 색상의 최댓값을 179로 설정하고, 두 트랙바의 콜백 함수를 모두 on_hue_change() 함수로 설정
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
	on_hue_changed(0, 0);

	waitKey();
	return 0;
}

void on_hue_changed(int, void*)
{
	Scalar lowerb(lower_hue, 100, 0);
	Scalar upperb(upper_hue, 255, 255);
	inRange(src_hsv, lowerb, upperb, mask);
	// inRange() 함수는 입력 영상 src의 픽셀 값이 지정한 밝기 또는 색상 범위에 포함되어 있으면 흰색, 그렇지 않으면 검은색으로 채워진 마스크 영상 dst를 반환
	/*  행렬의 원소 값이 특정 범위 안에 있는지 확인하려면 inRange() 함수를 사용
	void inRange(InputArray src, InputArray lowerb,
				 InputArray upperb, OutputArray dst);
				 - src : 입력 영상
				 - lowerb : 하한 값. 주로 Mat 또는 Scalar 객체를 지정
				 - upperb : 상한 값. 주로 Mat 또는 Scalar 객체를 지정
				 - dst : 출력 마스크 영상. 입력 영상과 크기가 같고, 타입은 CV_8UC1
	*/
	imshow("mask", mask);
}