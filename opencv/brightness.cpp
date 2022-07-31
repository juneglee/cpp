#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void brightness1();
void brightness2();
void brightness3();
void brightness4();
void on_brightness(int pos, void* userdata);

int main(void)
{
	brightness1();
	brightness2();
	brightness3();
	brightness4();

	return 0;
}

// 그레이스케일 영상 다루기
// Mat img1 = imread(“lenna.bmp”, IMREAD_GRAYSCALE);

void brightness1()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst = src + 100;
	// src와 dst 변수는 Mat 클래스 타입이고, 숫자 100은 일반적인 int 자료형
	// OpenCV에서는 덧셈, 뺄셈 연산자에 대하여 연산자 재정의가 되어 있어서 Mat 객체와 C/C++ 기본 자료형과의 덧셈 및 뺄셈 연산이 가능
	// 즉, src가 그레이스케일 영상이므로 덧셈 연산 결과가 255보다 클 경우 dst 영상의 픽셀 값을 255로 설정

	imshow("src", src);
	imshow("dst", dst);
	// rc 창은 입력 레나 영상이고, dst 창은 밝기가 100만큼 증가된 결과 영상을 나타낸다
	waitKey();

	destroyAllWindows();
}

void brightness2()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

void brightness3()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			/*
			template<> inline
			uchar saturate_cast<uchar>( int v );
				- v      : int 자료형이 표현할 수 있는 범위의 정수
				- 반환값 : 0~255 사이의 정수
			saturate_cast() 함수는 원래 템플릿으로 정의된 함수이기 때문에 <> 괄호 사이에 사용하는 자료형을 명시해야 합니다. 
			앞에 나타낸 saturate_cast() 함수 형식은 int 자료형의 값을 uchar 자료형 범위로 포화 연산을 수행합니다. 
			그레이스케일 영상에서는 uchar 타입으로 픽셀 값을 표현하기 때문에 밝기 조절 코드에 포화 연산을 추가하려면 다음과 같이 코드를 작성
			*/
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
			// 	밝기 조절된 픽셀 값에 saturate_cast() 함수를 이용하여 포화 연산을 수행한 후 결과 영상 픽셀 값으로 설정
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

void brightness4()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src); 
	// reateTrackbar() 함수를 호출할 때 트랙바의 최댓값을 100으로 설정하였기에 실제 dst 창에 나타난 트랙바는 0부터 100 사이에서 그 위치를 선택할 수 있다
	on_brightness(0, (void*)&src); 
	//  on_brightness() 콜백 함수를 강제로 호출하는 코드

	waitKey();
	destroyAllWindows();
}

void on_brightness(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst);
}