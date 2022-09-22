#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 영상의 이진화(binarization)는 영상의 각 픽셀을 두 개의 부류로 나누는 작업
// 입력 영상을 주요 객체 영역과 배경 영역으로 나누거나 
// 또는 영상에서 중요도가 높은 관심 영역(ROI, Region Of Interest)과 그렇지 않은 비관심 영역으로 구분하는 용도로 이진화가 사용될 수 있다
// 디지털 컴퓨팅 분야에서 이진화는 입력 값을 0 또는 1로 설정하지만 영상의 이진화에서는 픽셀 값을 0 또는 255로 설정
// 그레이스케일 영상에 대해 이진화를 수행하려면 영상의 픽셀 값이 특정 값보다 크면 255로 설정하고, 작으면 0으로 설정
void on_threshold(int pos, void* userdata);

int main(int argc, char* argv[])
{
	Mat src;

	if (argc < 2)
		src = imread("images/neutrophils.png", IMREAD_GRAYSCALE);
	else
		src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src); // 트랙바의 최댓값은 255이고, 트랙바 콜백 함수 이름은 on_threshold
	setTrackbarPos("Threshold", "dst", 128); // 프로그램이 처음 실행될 때 트랙바 위치가 128이 되도록 설정하여 on_threshold() 함수가 처음에 한 번 실행

	waitKey();
	return 0;
}

void on_threshold(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;

	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY); 
	// 사용자가 지정한 트랙바 위치를 이용하여 이진화를 수행
	/*
	* threshold() 함수는 임계값을 이용한 다양한 연산을 지원하는 함수
	double threshold(InputArray src, OutputArray dst,
		double thresh, double maxval, int type);
		- src : 입력 영상
		- dst : 출력 영상. 입력 영상과 같은 크기, 같은 타입
		- thresh : 임계값
		- maxval : THRESH_BINARY 또는 THRESH_BINARY_INV 방법을 사용할 때 결과 영상의 최댓값
		- type : 임계값 연산 방법. ThresholdTypes 열거형 상수를 지정
		- 반환값 : 사용된 임계값. THRESH_OTSU 또는 THRESH_TRIANGLE 방법을 사용할 때 자동으로 결정된 임계값을 반환
	*/
	// ThresholdTypes 열거형 상수 
	// THRESH_BINARY, THRESH_BINARY_INV, THRESH_TRUNC, THRESH_TOZERO, THRESH_TOZERO_INV 다섯 개의 상수가 threshold() 함수의 동작을 결정
	// THRESH_OTSU와 THRESH_TRIANGLE 상수는 영상의 픽셀 값 분포를 분석하여 임계값을 자동으로 결정하여 이진화를 수행
	
	imshow("dst", dst);
}