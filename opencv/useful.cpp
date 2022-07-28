#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void mask_setTo();
void mask_copyTo();
void time_inverse();
void useful_func();

int main(void)
{
	mask_setTo();
	mask_copyTo();
	time_inverse();
	useful_func();

	return 0;
}

// Mat::setTo() 함수는 마스크 연산을 지원하는 함수
/* 
* Mat& Mat::setTo(InputArray value, InputArray mask = noArray());
	- value  : 행렬 원소에 설정할 값
	- mask   : 마스크 행렬. 마스크 행렬의 원소가 0이 아닌 위치에서만 value 값이 설정( 행렬 전체 원소 값을 설정하려면 noArray() 또는 Mat()을 지정)
	- 반환값 : Mat 객체의 참조
*/
void mask_setTo()
{
	Mat src = imread("images/lenna.bmp", IMREAD_COLOR);
	Mat mask = imread("images/mask_smile.bmp", IMREAD_GRAYSCALE);

	if (src.empty() || mask.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	src.setTo(Scalar(0, 255, 255), mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}

// Mat::copyTo() 함수는 두 가지 형태로 정의
// 하나는 복사할 대상 행렬 하나만 인자로 받고, 다른 하나는 복사할 대상 행렬과 마스크 영상 두 개를 인자
/*
* void Mat::copyTo(OutputArray m, InputArray mask) const;
	- m    : 복사본이 저장될 행렬. 만약 *this 행렬과 크기 및 타입이 다르면 메모리를 새로 할당한 후 픽셀 값을 복사
	- mask : 마스크 행렬. 마스크 행렬 원소 값이 0이 아닌 좌표에서만 행렬 원소를 복사 ( mask 행렬은 *this와 같은 크기이고 깊이는 CV_8U이어야 한다)
*/

void mask_copyTo()
{
	Mat src = imread("images/airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("images/mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat dst = imread("images/field.bmp", IMREAD_COLOR);

	if (src.empty() || mask.empty() || dst.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	src.copyTo(dst, mask);

	imshow("src", src);
	imshow("dst", dst);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}
// 특정 연산이 수행되는 시간을 측정하기 위해서는 getTickCount() 함수와 getTickFrequency() 함수를 같이 조합해서 사용
// getTimeMicro() 함수는 연산 시간을 마이크로 초 단위로 반환
// getTimeMilli() 함수는 연산 시간을 밀리초 단위로 반환
// int64 getTickCount(void) : 반환값 시스템의 현재 틱(tick) 횟수
// double getTickFrequency(void) : 반환값 시스템의 초당 틱 횟수
void time_inverse()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	TickMeter tm;
	tm.start();

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
		}
	}

	tm.stop();
	cout << "Image inverse took " << tm.getTimeMilli() << "ms." << endl;
}

void useful_func()
{
	Mat img = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	/* 행렬의 합과 평균
	Scalar sum(InputArray src);
		- src    : 입력 행렬(1~4채널)
		- 반환값 : 각 채널의 합
	Scalar mean(InputArray src, InputArray mask = noArray());
		- src    : 입력 행렬(1~4채널)
		- mask   : 마스크 영상
		- 반환값 : 각 채널의 평균
	*/
	cout << "Sum: " << (int)sum(img)[0] << endl;
	cout << "Mean: " << (int)mean(img)[0] << endl;

	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);
	/*
	행렬의 최솟값, 최댓값을 찾는 minMaxLoc() 함수
	void minMaxLoc(InputArray src, double* minVal,
				   double* maxVal = 0, Point* minLoc = 0,
				   Point* maxLoc = 0, InputArray mask = noArray()
		- src    : 입력 영상. 단일 채널
		- minVal : 최솟값을 받을 double형 변수의 주소. 필요 없으면 0을 지정
		- maxVal : 최댓값을 받을 double형 변수의 주소. 필요 없으면 0을 지정
		- minLoc : 최솟값 위치 좌표를 받을 Point형 변수의 주소. 필요 없으면 0을 지정
		- maxLoc : 최댓값 위치 좌표를 받을 Point형 변수의 주소. 필요 없으면 0을 지정
		- mask   : 마스크 영상. 마스크 영상의 픽셀 값이 0이 아닌 위치에서만 연산을 수행
	*/
	cout << "minVal: " << minVal << " at " << minPos << endl;
	cout << "maxVal: " << maxVal << " at " << maxPos << endl;

	Mat src = Mat_<float>({ 1, 5 }, { -1.f, -0.5f, 0.f, 0.5f, 1.f });

	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	// 	normalize( ) 함수 : 행렬의 노름(norm) 값을 정규화하거나 또는 원소 값 범위를 특정 범위로 정규화
	/*
	void normalize(InputArray src, InputOutputArray dst,
				   double alpha = 1, double beta = 0,
				   int norm_type = NORM_L2, int dtype = -1,
	 InputArray mask = noArray());
		- src       : 입력 행렬
		- dst       : 출력 행렬. src와 같은 크기 
		- alpha     : (노름 정규화인 경우) 목표 노름 값, (원소 값 범위 정규화인 경우) 최솟값
		- beta      : (원소 값 범위 정규화인 경우) 최댓값 
		- norm_type : 정규화 타입. NORM_INF, NORM_L1, NORM_L2, NORM_MINMAX 중 하나를 지정합니다.
		- dtype     : 결과 영상의 타입 
		- mask      : 마스크 영상
	*/
	cout << "src: " << src << endl;
	cout << "dst: " << dst << endl;

	// cvRound( ) 함수 :  실수 값을 정수로 변환할 때는 주로 반올림을 사용
	/*
	int cvRound(double value);
	int cvRound(float value);
		- value  : 입력 실수 값. 만약 value가 INT_MIN과 INT_MAX 사이를 벗어날 경우 알 수 없는 값이 반환됩니다.
		- 반환값 : 반올림한 정수 값
	*/
	cout << "cvRound(2.5): " << cvRound(2.5) << endl;
	cout << "cvRound(2.51): " << cvRound(2.51) << endl;
	cout << "cvRound(3.4999): " << cvRound(3.4999) << endl;
	cout << "cvRound(3.5): " << cvRound(3.5) << endl;
}