#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void noise_gaussian();
void filter_bilateral();
void filter_median();

// 신호 처리 관점에서 잡음(noise)이란 원본 신호에 추가된 원치 않은 신호를 의미
// 잡음이 생성되는 방식을 잡음 모델(noise model)이라고 하며, 다양한 잡음 모델 중에서 가장 대표적인 잡음 모델은 가우시안 잡음 모델(Gaussian noise model) dlek 
int main(void)
{
	noise_gaussian();
	filter_bilateral();
	filter_median();

	return 0;
}

void noise_gaussian()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);

	for (int stddev = 10; stddev <= 30; stddev += 10) {
		Mat noise(src.size(), CV_32SC1);
		randn(noise, 0, stddev);
		/*
		* randn() 함수는 가우시안 잡음으로 구성된 행렬을 생성하여 반환
		* randn() 함수는 dst 행렬을 가우시안 분포를 따르는 난수로 채움
		 void randn(InputOutputArray dst, InputArray mean, InputArray stddev);
			- dst : 가우시안 난수로 채워질 행렬. dst 행렬은 미리 할당이 되어 있어야 합니다.
			- mean : 가우시안 분포 평균
			- stddev : 가우시안 분포 표준 편차
		*/

		Mat dst;
		add(src, noise, dst, Mat(), CV_8U);

		String desc = format("stddev = %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}

// 양방향 필터 
// 대부분의 영상에는 가우시안 잡음이 포함되어 있으며 많은 컴퓨터 비전 시스템이 가우시안 잡음을 제거하기 위해 가우시안 필터를 사용
// 입력 영상에서 픽셀 값이 크게 변하지 않는 평탄한 영역에 가우시안 필터가 적용될 경우, 
// 주변 픽셀 값이 부드럽게 블러링되면서 잡음의 영향도 크게 줄어든다. 
// 그러나 픽셀 값이 급격하게 변경되는 에지 근방에 동일한 가우시안 필터가 적용되면 잡음뿐만 아니라 에지 성분까지 함께 감소하게 된다. 
// 즉, 잡음이 줄어들면서 함께 에지도 무뎌지기 때문에 객체의 윤곽이 흐릿하게 바뀌게 된다 

// 점을 보완하기 위해 많은 사람들이 에지 정보는 그대로 유지하면서 잡음만 제거하는 에지 보전 잡음 제거 필터(edge-preserving noise removal filter)에 대해 연구하였다. 
// 특히 1998년 토마시(C. Tomasi)가 제안한 양방향 필터(bilateral filter)는 에지 성분은 그대로 유지하면서 가우시안 잡음을 효과적으로 제거하는 알고리즘
void filter_bilateral()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, 5);
	add(src, noise, src, Mat(), CV_8U);

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);
	/*
	* bilateralFilter() 함수를 이용하여 양방향 필터를 수행
	void bilateralFilter(InputArray src, OutputArray dst, int d,
                     double sigmaColor, double sigmaSpace,
                     int borderType = BORDER_DEFAULT);
					 - src : 입력 영상. 8비트 또는 실수형, 1채널 또는 3채널 영상
					 - dst : 출력 영상. src와 같은 크기, 같은 타입
					 - d : 필터링에 사용할 이웃 픽셀과의 거리(지름). 양수가 아닌 값(예를 들어 -1)을 지정하면 sigmaSpace로부터 자동 계산
					 - sigmaColor : 색 공간에서의 가우시안 필터 표준 편차
					 - sigmaSpace : 좌표 공간에서의 가우시안 필터 표준 편차
					 - borderType :가장자리 픽셀 확장 방식
	*/
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}

// 미디언 필터(median filter)는 입력 영상에서 자기 자신 픽셀과 주변 픽셀 값 중에서 중간값(median)을 선택하여 결과 영상 픽셀 값으로 설정하는 필터링 기법
void filter_median()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	int num = (int)(src.total() * 0.1);
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.at<uchar>(y, x) = (i % 2) * 255;
	}

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);

	Mat dst2;
	medianBlur(src, dst2, 3);
	/* 
	* medianBlur() 함수를 이용하여 미디언 필터링을 수행
	void medianBlur(InputArray src, OutputArray dst, int ksize);
		- src : 입력 영상. 1, 3, 4채널 영상. ksize가 3 또는 5이면 src는 CV_8U, CV_16U, CV_32F의 깊이를 가질 수 있고, 
				그 이상의 필터 크기에서는 CV_8U 깊이만 사용할 수 있다
		- dst : 출력 영상. src와 같은 크기, 같은 타입을 갖는다
		- ksize : 필터 크기. 3보다 같거나 큰 홀수를 지정
	*/

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}