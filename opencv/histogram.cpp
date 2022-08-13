#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat calcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);

void histogram_stretching();
void histogram_equalization();

// 히스토그램(histogram)이란 영상의 픽셀 값 분포를 그래프 형태로 표현한 것을 의미
// 그레이스케일 영상의 경우, 각 그레이스케일 값에 해당하는 픽셀의 개수를 구하고 이를 막대 그래프 형태로 표현함
// 컬러 영상에 대해서도 세 개의 색상 성분 조합에 따른 픽셀 개수를 계산하여 히스토그램을 구함
int main(void)
{
	histogram_stretching();
	histogram_equalization();

	return 0;
}
// calcHist() 함수
// calcHist() 함수는 한 장의 영상뿐만 아니라 여러 장의 영상으로부터 히스토그램을 구할 수 있고, 
// 여러 채널로부터 히스토그램을 구할 수도 있다
Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);
	/* 
	* void calcHist(const Mat* images, int nimages,
              const int* channels, InputArray mask,
              OutputArray hist, int dims, const int* histSize,
              const float** ranges, bool uniform = true, bool accumulate = false);
			- images : 입력 영상의 배열 또는 입력 영상의 주소. (영상의 배열인 경우, 모든 영상의 크기와 깊이는 같아야 한다)
			- nimages : 입력 영상 개수
			- channels : 히스토그램을 구할 채널을 나타내는 정수형 배열
			- mask : 마스크 영상. ( 입력 영상과 크기가 같은 8비트 배열이어야 합니다).
			         마스크 행렬의 원소 값이 0이 아닌 좌표의 픽셀만 히스토그램 계산에 사용됩니다. 
					 mask 인자에 Mat() 또는 noArray()를 지정하면 입력 영상 전체에 대해 히스토그램을 구합니다.
			- hist : 출력 히스토그램. CV_32F 깊이를 사용하는 dims-차원의 행렬입니다.
			- dims : 출력 히스토그램의 차원 수
			- histSize : 각 차원의 히스토그램 배열 크기를 나타내는 배열(즉, 각 차원의 히스토그램 빈 개수를 나타내는 배열)
			- ranges : 각 차원의 히스토그램 범위. 등간격 히스토그램이면(uniform = true), 
					   ranges[i]는 각 차원의 최솟값과 최댓값으로 구성된 배열이고 [최솟값, 최댓값)2 범위를 나타냅니다. 
					   비등간격 히스토그램이면(uniform = false), ranges[i]는 각각의 구역을 나타내는 histSize[i]+1개의 원소로 구성된 배열입니다.
			- uniform : 히스토그램 빈의 간격이 균등한지를 나타내는 플래그
			- accumulate : 적 플래그. 이 값이 true이면 hist 배열을 초기화하지 않고 누적하여 히스토그램을 계산
	*/

	return hist;
}

Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0, &histMax);

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}

void histogram_stretching()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

void histogram_equalization()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	equalizeHist(src, dst);
	/* void equalizeHist( InputArray src, OutputArray dst );
		-  src : 입력 영상. 8비트 1채널
		-  dst : 출력 영상. src와 크기와 타입이 같음
	
	*/

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}