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

// Mat::setTo() �Լ��� ����ũ ������ �����ϴ� �Լ�
/* 
* Mat& Mat::setTo(InputArray value, InputArray mask = noArray());
	- value  : ��� ���ҿ� ������ ��
	- mask   : ����ũ ���. ����ũ ����� ���Ұ� 0�� �ƴ� ��ġ������ value ���� ����( ��� ��ü ���� ���� �����Ϸ��� noArray() �Ǵ� Mat()�� ����)
	- ��ȯ�� : Mat ��ü�� ����
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

// Mat::copyTo() �Լ��� �� ���� ���·� ����
// �ϳ��� ������ ��� ��� �ϳ��� ���ڷ� �ް�, �ٸ� �ϳ��� ������ ��� ��İ� ����ũ ���� �� ���� ����
/*
* void Mat::copyTo(OutputArray m, InputArray mask) const;
	- m    : ���纻�� ����� ���. ���� *this ��İ� ũ�� �� Ÿ���� �ٸ��� �޸𸮸� ���� �Ҵ��� �� �ȼ� ���� ����
	- mask : ����ũ ���. ����ũ ��� ���� ���� 0�� �ƴ� ��ǥ������ ��� ���Ҹ� ���� ( mask ����� *this�� ���� ũ���̰� ���̴� CV_8U�̾�� �Ѵ�)
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
// Ư�� ������ ����Ǵ� �ð��� �����ϱ� ���ؼ��� getTickCount() �Լ��� getTickFrequency() �Լ��� ���� �����ؼ� ���
// getTimeMicro() �Լ��� ���� �ð��� ����ũ�� �� ������ ��ȯ
// getTimeMilli() �Լ��� ���� �ð��� �и��� ������ ��ȯ
// int64 getTickCount(void) : ��ȯ�� �ý����� ���� ƽ(tick) Ƚ��
// double getTickFrequency(void) : ��ȯ�� �ý����� �ʴ� ƽ Ƚ��
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
	/* ����� �հ� ���
	Scalar sum(InputArray src);
		- src    : �Է� ���(1~4ä��)
		- ��ȯ�� : �� ä���� ��
	Scalar mean(InputArray src, InputArray mask = noArray());
		- src    : �Է� ���(1~4ä��)
		- mask   : ����ũ ����
		- ��ȯ�� : �� ä���� ���
	*/
	cout << "Sum: " << (int)sum(img)[0] << endl;
	cout << "Mean: " << (int)mean(img)[0] << endl;

	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);
	/*
	����� �ּڰ�, �ִ��� ã�� minMaxLoc() �Լ�
	void minMaxLoc(InputArray src, double* minVal,
				   double* maxVal = 0, Point* minLoc = 0,
				   Point* maxLoc = 0, InputArray mask = noArray()
		- src    : �Է� ����. ���� ä��
		- minVal : �ּڰ��� ���� double�� ������ �ּ�. �ʿ� ������ 0�� ����
		- maxVal : �ִ��� ���� double�� ������ �ּ�. �ʿ� ������ 0�� ����
		- minLoc : �ּڰ� ��ġ ��ǥ�� ���� Point�� ������ �ּ�. �ʿ� ������ 0�� ����
		- maxLoc : �ִ� ��ġ ��ǥ�� ���� Point�� ������ �ּ�. �ʿ� ������ 0�� ����
		- mask   : ����ũ ����. ����ũ ������ �ȼ� ���� 0�� �ƴ� ��ġ������ ������ ����
	*/
	cout << "minVal: " << minVal << " at " << minPos << endl;
	cout << "maxVal: " << maxVal << " at " << maxPos << endl;

	Mat src = Mat_<float>({ 1, 5 }, { -1.f, -0.5f, 0.f, 0.5f, 1.f });

	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	// 	normalize( ) �Լ� : ����� �븧(norm) ���� ����ȭ�ϰų� �Ǵ� ���� �� ������ Ư�� ������ ����ȭ
	/*
	void normalize(InputArray src, InputOutputArray dst,
				   double alpha = 1, double beta = 0,
				   int norm_type = NORM_L2, int dtype = -1,
	 InputArray mask = noArray());
		- src       : �Է� ���
		- dst       : ��� ���. src�� ���� ũ�� 
		- alpha     : (�븧 ����ȭ�� ���) ��ǥ �븧 ��, (���� �� ���� ����ȭ�� ���) �ּڰ�
		- beta      : (���� �� ���� ����ȭ�� ���) �ִ� 
		- norm_type : ����ȭ Ÿ��. NORM_INF, NORM_L1, NORM_L2, NORM_MINMAX �� �ϳ��� �����մϴ�.
		- dtype     : ��� ������ Ÿ�� 
		- mask      : ����ũ ����
	*/
	cout << "src: " << src << endl;
	cout << "dst: " << dst << endl;

	// cvRound( ) �Լ� :  �Ǽ� ���� ������ ��ȯ�� ���� �ַ� �ݿø��� ���
	/*
	int cvRound(double value);
	int cvRound(float value);
		- value  : �Է� �Ǽ� ��. ���� value�� INT_MIN�� INT_MAX ���̸� ��� ��� �� �� ���� ���� ��ȯ�˴ϴ�.
		- ��ȯ�� : �ݿø��� ���� ��
	*/
	cout << "cvRound(2.5): " << cvRound(2.5) << endl;
	cout << "cvRound(2.51): " << cvRound(2.51) << endl;
	cout << "cvRound(3.4999): " << cvRound(3.4999) << endl;
	cout << "cvRound(3.5): " << cvRound(3.5) << endl;
}