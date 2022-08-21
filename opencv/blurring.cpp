#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void blurring_mean();
void blurring_gaussian();

// 블러링(blurring)은 마치 초점이 맞지 않은 사진처럼 영상을 부드럽게 만드는 필터링 기법이며 스무딩(smoothing)이라고도 한다
// 영상에서 인접한 픽셀 간의 픽셀 값 변화가 크지 않은 경우 부드러운 느낌을 받을 수 있다. 
// 블러링은 거친 느낌의 입력 영상을 부드럽게 만드는 용도로 사용되기도 하고, 혹은 입력 영상에 존재하는 잡음의 영향을 제거하는 전처리 과정으로도 사용된다. 
int main(void)
{
	blurring_mean();
	blurring_gaussian();

	return 0;
}

void blurring_mean()
{
	Mat src = imread("images/rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	for (int ksize = 3; ksize <= 7; ksize += 2) {
		blur(src, dst, Size(ksize, ksize));
		/*
		* blur() 함수를 이용하여 평균값 필터링을 수행
		void blur(InputArray src, OutputArray dst, Size ksize,
				  Point anchor = Point(-1,-1), int borderType = BORDER_DEFAULT);
				  - src : 입력 영상. 다채널 영상은 각 채널별로 블러링을 수행합니다. 입력 영상의 깊이는 CV_8U, CV_16U, CV_16S, CV_32F, CV_64F 중 하나여야 합니다.
				  - dst : 출력 영상. src와 같은 크기, 같은 채널 수를 갖습니다.
				  - ksize : 블러링 커널 크기
				  - anchor : 고정점 좌표. Point(-1, -1)을 지정하면 커널 중심을 고정점으로 사용합니다.
				  - borderType : 가장자리 픽셀 확장 방식

		*/

		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}

// 가우시안 필터는 가우시안 분포(Gaussian distribution) 함수를 근사하여 생성한 필터 마스크를 사용하는 필터링 기법
// 가우시안 분포는 평균을 중심으로 좌우 대칭의 종 모양(bell shape)을 갖는 확률 분포를 말하며 정규 분포(normal distribution)라고도 한다
void blurring_gaussian()
{
	Mat src = imread("images/rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	for (int sigma = 1; sigma <= 5; sigma++) {
		GaussianBlur(src, dst, Size(0, 0), (double)sigma);
		/* 
		* 
		void GaussianBlur(InputArray src, OutputArray dst, Size ksize,
						  double sigmaX, double sigmaY = 0,
						  int borderType = BORDER_DEFAULT);
				  - src : 입력 영상. 다채널 영상은 각 채널별로 블러링을 수행
				  - dst : 출력 영상. src와 같은 크기, 같은 타입을 갖는다.
				  - ksize : 가우시안 커널 크기. ksize.width와 ksize.height는 0보다 큰 홀수이어야 합니다. ksize에 Size()를 지정하면 표준 편차로부터 커널 크기를 자동으로 결정한다
				  - sigmaX : x 방향으로의 가우시안 커널 표준 편차
				  - sigmaY : y 방향으로의 가우시안 커널 표준 편차. 만약 sigmaY = 0이면 sigmaX와 같은 값을 사용한다. 
								만약 sigmaX와 simgaY가 모두 0이면 ksize의 width와 height 값으로부터 표준 편차를 계산하여 사용한다.
				  - borderType : 가장자리 픽셀 확장 방식
		*/

		String desc = format("Gaussian: sigma = %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}