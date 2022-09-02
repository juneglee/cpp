#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void color_op();
void color_inverse();
void color_grayscale();
void color_split();

int main(void)
{
	color_op();
	color_inverse();
	color_grayscale();
	color_split();

	return 0;
}

void color_op()
{
	Mat img = imread("images/butterfly.jpg", IMREAD_COLOR); // IMREAD_COLOR로 설정하면 영상을 3채널 컬러 영상 

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// 컬러 영상은 흔히 RGB라고 부르는 빨간색(R), 녹색(G), 파란색(B) 색상 성분의 조합으로 픽셀 값을 표현
	// 색상 성분 값이 0이면 해당 색상 성분이 전혀 없는 상태이고, 255이면 해당 색상 성분이 가득 차 있음을 의미
	// Vec3b 클래스는 크기가 3인 uchar 자료형 배열을 멤버 변수로 가지고 있는 클래스
	// Vec3b 클래스의 바이트 크기는 정확하게 3바이트이며, 이는 실제 3채널 컬러 영상의 한 픽셀이 차지하는 바이트 수와 같음
	// 컬러 영상에서 픽셀 값을 참조할 때에도 Mat::at() 함수를 사용
	Vec3b& pixel = img.at<Vec3b>(0, 0);
	uchar b1 = pixel[0];
	uchar g1 = pixel[1];
	uchar r1 = pixel[2];

	Vec3b* ptr = img.ptr<Vec3b>(0);
	uchar b2 = ptr[0][0];
	uchar g2 = ptr[0][1];
	uchar r2 = ptr[0][2];
}

// 픽셀 값 참조 방법을 이용하여 컬러 영상을 반전
void color_inverse()
{
	Mat src = imread("images/butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	// src 영상과 dst 영상의 (i, j) 위치 픽셀 값을 각각 Vec3b 자료형 변수 p1과 p2로 참조한 후에 반전
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			p2[0] = 255 - p1[0]; // B
			p2[1] = 255 - p1[1]; // G
			p2[2] = 255 - p1[2]; // R
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


void color_grayscale()
{
	Mat src = imread("images/butterfly.jpg");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	/*
	*  영상의 색 공간을 다른 색 공간으로 변환할 때에는 cvtColor() 함수를 사용
	void cvtColor(InputArray src, OutputArray dst, int code, int dstCn = 0);
		- src : 입력 영상. CV_8U, CV_16U, CV_32F 중 하나의 깊이를 사용
		- dst : 결과 영상. src와 크기 및 깊이가 같음
		- code : 색 공간 변환 코드. ColorConversionCodes 열거형 상수 중 하나를 지정
		- dstCn : 결과 영상의 채널 수. 0이면 자동으로 결정
	*/

	/* 
	* 주요 색 공간 변환 코드 
	- COLOR_BGR2RGB  : BGR 채널 순서와 RGB 채널 순서를 상호 변환
	  COLOR_RGB2BGR
	- COLOR_BGR2GRAY : 3채널 BGR 컬러 영상을 1채널 그레이스케일 영상으로 변환
	- COLOR_GRAY2BGR : 1채널 그레이스케일 영상을 3채널 BGR 컬러 영상으로 변환
	- COLOR_BGR2XYZ : BGR 색 공간을 CIE XYZ 색 공간으로 변환
	- COLOR_XYZ2BGR : CIE XYZ 색 공간을 BGR 색 공간으로 변환
	- COLOR_BGR2YCrCb : BGR 색 공간을 YCrCb 색 공간으로 변환
	- COLOR_YCrCb2BGR : YCrCb 색 공간을 BGR 색 공간으로 변환
	- COLOR_BGR2HSV : BGR 색 공간을 HSV 색 공간으로 변환
	- COLOR_HSV2BGR : HSV 색 공간을 BGR 색 공간으로 변환
	- COLOR_BGR2Lab : BGR 색 공간을 CIE Lab 색 공간으로 변환
	- COLOR_Lab2BGR : CIE Lab 색 공간을 BGR 색 공간으로 변환
	*/

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void color_split()
{
	Mat src = imread("images/candies.png");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<Mat> bgr_planes;
	split(src, bgr_planes);
	/*
	* 다채널 행렬을 1채널 행렬 여러 개로 변환할 때에는 split() 함수를 사용
	void split(const Mat& src, Mat* mvbegin);
	void split(InputArray src, OutputArrayOfArrays mv);
		- src : 입력 다채널 행렬
		- mvbegin : 분리된 1채널 행렬을 저장할 Mat 배열 주소. 
					영상 배열 개수는 src 영상 채널 수와 같아야 한다
		- mv : 분리된 1채널 행렬을 저장할 벡터
	*/

	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);
	imshow("G_plane", bgr_planes[1]);
	imshow("R_plane", bgr_planes[2]);

	waitKey();
	destroyAllWindows();
}