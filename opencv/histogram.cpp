#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat calcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);

void histogram_stretching();
void histogram_equalization();

// ������׷�(histogram)�̶� ������ �ȼ� �� ������ �׷��� ���·� ǥ���� ���� �ǹ�
// �׷��̽����� ������ ���, �� �׷��̽����� ���� �ش��ϴ� �ȼ��� ������ ���ϰ� �̸� ���� �׷��� ���·� ǥ����
// �÷� ���� ���ؼ��� �� ���� ���� ���� ���տ� ���� �ȼ� ������ ����Ͽ� ������׷��� ����
int main(void)
{
	histogram_stretching();
	histogram_equalization();

	return 0;
}
// calcHist() �Լ�
// calcHist() �Լ��� �� ���� ����Ӹ� �ƴ϶� ���� ���� �������κ��� ������׷��� ���� �� �ְ�, 
// ���� ä�ηκ��� ������׷��� ���� ���� �ִ�
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
			- images : �Է� ������ �迭 �Ǵ� �Է� ������ �ּ�. (������ �迭�� ���, ��� ������ ũ��� ���̴� ���ƾ� �Ѵ�)
			- nimages : �Է� ���� ����
			- channels : ������׷��� ���� ä���� ��Ÿ���� ������ �迭
			- mask : ����ũ ����. ( �Է� ����� ũ�Ⱑ ���� 8��Ʈ �迭�̾�� �մϴ�).
			         ����ũ ����� ���� ���� 0�� �ƴ� ��ǥ�� �ȼ��� ������׷� ��꿡 ���˴ϴ�. 
					 mask ���ڿ� Mat() �Ǵ� noArray()�� �����ϸ� �Է� ���� ��ü�� ���� ������׷��� ���մϴ�.
			- hist : ��� ������׷�. CV_32F ���̸� ����ϴ� dims-������ ����Դϴ�.
			- dims : ��� ������׷��� ���� ��
			- histSize : �� ������ ������׷� �迭 ũ�⸦ ��Ÿ���� �迭(��, �� ������ ������׷� �� ������ ��Ÿ���� �迭)
			- ranges : �� ������ ������׷� ����. ��� ������׷��̸�(uniform = true), 
					   ranges[i]�� �� ������ �ּڰ��� �ִ����� ������ �迭�̰� [�ּڰ�, �ִ�)2 ������ ��Ÿ���ϴ�. 
					   ���� ������׷��̸�(uniform = false), ranges[i]�� ������ ������ ��Ÿ���� histSize[i]+1���� ���ҷ� ������ �迭�Դϴ�.
			- uniform : ������׷� ���� ������ �յ������� ��Ÿ���� �÷���
			- accumulate : �� �÷���. �� ���� true�̸� hist �迭�� �ʱ�ȭ���� �ʰ� �����Ͽ� ������׷��� ���
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
		-  src : �Է� ����. 8��Ʈ 1ä��
		-  dst : ��� ����. src�� ũ��� Ÿ���� ����
	
	*/

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}