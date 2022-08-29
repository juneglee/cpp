#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void sobel_derivative();
void sobel_edge();
void canny_edge();

// 마스크 기반 에지 검출

int main(void)
{
	sobel_derivative();
	sobel_edge();
	canny_edge();

	return 0;
}

// 영상에서 에지(edge)는 한쪽 방향으로 픽셀 값이 급격하게 바뀌는 부분을 가리킨다
// 즉, 어두운 영역에서 갑자기 밝아지거나 또는 반대로 밝은 영역에서 급격하게 어두워지는 부분을 에지라고 한다
// 객체와 배경의 경계, 또는 객체와 다른 객체의 경계에서 에지가 발생한다
// 그러므로 영상에서 에지를 찾아내는 작업은 객체의 윤곽을 알아낼 수 있는 유용한 방법이며 다양한 컴퓨터 비전 시스템에서 객체 판별을 위한 전처리로 에지 검출이 사용
// 영상에서 에지를 찾아내려면 픽셀 값의 변화율을 측정하여 변화율이 큰 픽셀을 선택해야 한다
// 수학에서 함수 또는 데이터의 변화율을 미분(derivative)이라고 하며, 좀 더 정확하게 기술하면 함수의 미분이란 주어진 함수의 순간 변화율을 의미하며, 1차원 연속 함수 f(x)의 미분은 다음과 같이 정의
void sobel_derivative()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat mx = Mat_<float>({ 1, 3 }, { -1 / 2.f, 0, 1 / 2.f });
	Mat my = Mat_<float>({ 3, 1 }, { -1 / 2.f, 0, 1 / 2.f });

	Mat dx, dy;
	filter2D(src, dx, -1, mx, Point(-1, -1), 128);
	filter2D(src, dy, -1, my, Point(-1, -1), 128);

	imshow("src", src);
	imshow("dx", dx);
	imshow("dy", dy);

	waitKey();
	destroyAllWindows();
}

// OpenCV는 소벨 마스크를 이용하여 영상을 미분하는 Sobel() 함수를 제공
void sobel_edge()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);
	/* 
	* OpenCV는 소벨 마스크를 이용하여 영상을 미분하는 Sobel() 함수를 제공
	void Sobel(InputArray src, OutputArray dst, int ddepth,
			   int dx, int dy, int ksize = 3, double scale = 1, double delta = 0,
			   int borderType = BORDER_DEFAULT);
	* 샤르 필터 마스크를 이용하여 영상을 미분하려면 Scharr() 함수를 사용
	void Scharr(InputArray src, OutputArray dst, int ddepth,
				int dx, int dy, double scale = 1, double delta = 0,
				int borderType = BORDER_DEFAULT);

			   - src : 입력 영상
			   - dst : 출력 영상. src와 같은 크기, 같은 채널 수를 갖음
			   - ddepth : 출력 영상의 깊이
			   - dx : x 방향 미분 차수
			   - dy : y 방향 미분 차수
			   - ksize : 소벨 커널의 크기
			   - scale : 필터링 연산 후 추가적으로 곱할 값
			   - delta : 필터링 연산 후 추가적으로 더할 값
			   - borderType : 가장자리 픽셀 확장 방식
	*/

	Mat fmag, mag;
	magnitude(dx, dy, fmag);
	/* 
	* openCV는 2차원 벡터의 x 방향 좌표와 y 방향 좌표를 이용하여 벡터의 크기를 계산하는 magnitude() 함수를 제공
	void magnitude(InputArray x, InputArray y, OutputArray magnitude);
		- x : 벡터의 x 좌표를 나타내는 실수 행렬 또는 벡터
		- y : 벡터의 y 좌표를 나타내는 실수 행렬 또는 벡터. x와 크기와 타입이 같아야 한다
		- magnitude : 벡터의 크기를 나타내는 실수 행렬 또는 벡터. x와 같은 크기, 같은 타입을 갖음

	* 만약 x 방향으로 미분과 y 방향으로 미분이 저장된 두 개의 행렬이 있을 때, 그래디언트의 방향을 계산하고 싶다면 phase() 함수를 사용
	void phase(InputArray x, InputArray y, OutputArray angle, bool angleInDegrees = false);
		- x : 벡터의 x 좌표를 나타내는 실수 행렬 또는 벡터
		- y : 벡터의 y 좌표를 나타내는 실수 행렬 또는 벡터. x와 크기와 같은 타입
		- angle : 벡터의 방향을 나타내는 실수 행렬 또는 벡터. x와 같은 크기, 같은 타입
		- angleInDegrees : 이 값이 true이면 각도(degree) 단위를 사용하고, false이면 라디안(radian) 단위를 사용
	*/
	fmag.convertTo(mag, CV_8UC1);

	Mat edge = mag > 150;

	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}

// 캐니 에지 검출기(canny edge detector)
/*
* 좋은 에지 검출기의 조건
* 1. 정확한 검출(good detection): 에지를 검출하지 못하거나 또는 에지가 아닌데 에지로 검출하는 확률을 최소화
* 2. 정확한 위치(good localization): 실제 에지의 중심을 찾아야 한다
* 3. 단일 에지(single edge): 하나의 에지는 하나의 점으로 표현
*/

void canny_edge()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2;
	Canny(src, dst1, 50, 100);
	Canny(src, dst2, 50, 150);
	/*
	void Canny(InputArray image, OutputArray edges,
           double threshold1, double threshold2,
           int apertureSize = 3, bool L2gradient = false);
	void Canny(InputArray dx, InputArray dy, OutputArray edges,
			   double threshold1, double threshold2,
			   bool L2gradient = false);
			- image : 8비트 입력 영상
			- dx : 입력 영상의 x 방향 미분 영상. CV_16SC1 또는 CV_16SC3
			- dy : 입력 영상의 y 방향 미분 영상. CV_16SC1 또는 CV_16SC3
			- edges : 출력 에지 영상. 입력 영상과 크기가 같은 8비트 단일 채널 영상
			- threshold1 : 히스테리시스 에지 검출을 위한 첫 번째 임계값
			- threshold2 : 히스테리시스 에지 검출을 위한 두 번째 임계값
			- apertureSize : 그래디언트 계산을 위한 소벨 마스크 크기
			- L2gradient : 그래디언트 크기 계산 시 L2 노름을 사용하려면 true를 지정(false이면 L1 노름을 사용)
	*/

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}