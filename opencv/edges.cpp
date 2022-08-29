#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void sobel_derivative();
void sobel_edge();
void canny_edge();

// ����ũ ��� ���� ����

int main(void)
{
	sobel_derivative();
	sobel_edge();
	canny_edge();

	return 0;
}

// ���󿡼� ����(edge)�� ���� �������� �ȼ� ���� �ް��ϰ� �ٲ�� �κ��� ����Ų��
// ��, ��ο� �������� ���ڱ� ������ų� �Ǵ� �ݴ�� ���� �������� �ް��ϰ� ��ο����� �κ��� ������� �Ѵ�
// ��ü�� ����� ���, �Ǵ� ��ü�� �ٸ� ��ü�� ��迡�� ������ �߻��Ѵ�
// �׷��Ƿ� ���󿡼� ������ ã�Ƴ��� �۾��� ��ü�� ������ �˾Ƴ� �� �ִ� ������ ����̸� �پ��� ��ǻ�� ���� �ý��ۿ��� ��ü �Ǻ��� ���� ��ó���� ���� ������ ���
// ���󿡼� ������ ã�Ƴ����� �ȼ� ���� ��ȭ���� �����Ͽ� ��ȭ���� ū �ȼ��� �����ؾ� �Ѵ�
// ���п��� �Լ� �Ǵ� �������� ��ȭ���� �̺�(derivative)�̶�� �ϸ�, �� �� ��Ȯ�ϰ� ����ϸ� �Լ��� �̺��̶� �־��� �Լ��� ���� ��ȭ���� �ǹ��ϸ�, 1���� ���� �Լ� f(x)�� �̺��� ������ ���� ����
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

// OpenCV�� �Һ� ����ũ�� �̿��Ͽ� ������ �̺��ϴ� Sobel() �Լ��� ����
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
	* OpenCV�� �Һ� ����ũ�� �̿��Ͽ� ������ �̺��ϴ� Sobel() �Լ��� ����
	void Sobel(InputArray src, OutputArray dst, int ddepth,
			   int dx, int dy, int ksize = 3, double scale = 1, double delta = 0,
			   int borderType = BORDER_DEFAULT);
	* ���� ���� ����ũ�� �̿��Ͽ� ������ �̺��Ϸ��� Scharr() �Լ��� ���
	void Scharr(InputArray src, OutputArray dst, int ddepth,
				int dx, int dy, double scale = 1, double delta = 0,
				int borderType = BORDER_DEFAULT);

			   - src : �Է� ����
			   - dst : ��� ����. src�� ���� ũ��, ���� ä�� ���� ����
			   - ddepth : ��� ������ ����
			   - dx : x ���� �̺� ����
			   - dy : y ���� �̺� ����
			   - ksize : �Һ� Ŀ���� ũ��
			   - scale : ���͸� ���� �� �߰������� ���� ��
			   - delta : ���͸� ���� �� �߰������� ���� ��
			   - borderType : �����ڸ� �ȼ� Ȯ�� ���
	*/

	Mat fmag, mag;
	magnitude(dx, dy, fmag);
	/* 
	* openCV�� 2���� ������ x ���� ��ǥ�� y ���� ��ǥ�� �̿��Ͽ� ������ ũ�⸦ ����ϴ� magnitude() �Լ��� ����
	void magnitude(InputArray x, InputArray y, OutputArray magnitude);
		- x : ������ x ��ǥ�� ��Ÿ���� �Ǽ� ��� �Ǵ� ����
		- y : ������ y ��ǥ�� ��Ÿ���� �Ǽ� ��� �Ǵ� ����. x�� ũ��� Ÿ���� ���ƾ� �Ѵ�
		- magnitude : ������ ũ�⸦ ��Ÿ���� �Ǽ� ��� �Ǵ� ����. x�� ���� ũ��, ���� Ÿ���� ����

	* ���� x �������� �̺а� y �������� �̺��� ����� �� ���� ����� ���� ��, �׷����Ʈ�� ������ ����ϰ� �ʹٸ� phase() �Լ��� ���
	void phase(InputArray x, InputArray y, OutputArray angle, bool angleInDegrees = false);
		- x : ������ x ��ǥ�� ��Ÿ���� �Ǽ� ��� �Ǵ� ����
		- y : ������ y ��ǥ�� ��Ÿ���� �Ǽ� ��� �Ǵ� ����. x�� ũ��� ���� Ÿ��
		- angle : ������ ������ ��Ÿ���� �Ǽ� ��� �Ǵ� ����. x�� ���� ũ��, ���� Ÿ��
		- angleInDegrees : �� ���� true�̸� ����(degree) ������ ����ϰ�, false�̸� ����(radian) ������ ���
	*/
	fmag.convertTo(mag, CV_8UC1);

	Mat edge = mag > 150;

	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}

// ĳ�� ���� �����(canny edge detector)
/*
* ���� ���� ������� ����
* 1. ��Ȯ�� ����(good detection): ������ �������� ���ϰų� �Ǵ� ������ �ƴѵ� ������ �����ϴ� Ȯ���� �ּ�ȭ
* 2. ��Ȯ�� ��ġ(good localization): ���� ������ �߽��� ã�ƾ� �Ѵ�
* 3. ���� ����(single edge): �ϳ��� ������ �ϳ��� ������ ǥ��
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
			- image : 8��Ʈ �Է� ����
			- dx : �Է� ������ x ���� �̺� ����. CV_16SC1 �Ǵ� CV_16SC3
			- dy : �Է� ������ y ���� �̺� ����. CV_16SC1 �Ǵ� CV_16SC3
			- edges : ��� ���� ����. �Է� ����� ũ�Ⱑ ���� 8��Ʈ ���� ä�� ����
			- threshold1 : �����׸��ý� ���� ������ ���� ù ��° �Ӱ谪
			- threshold2 : �����׸��ý� ���� ������ ���� �� ��° �Ӱ谪
			- apertureSize : �׷����Ʈ ����� ���� �Һ� ����ũ ũ��
			- L2gradient : �׷����Ʈ ũ�� ��� �� L2 �븧�� ����Ϸ��� true�� ����(false�̸� L1 �븧�� ���)
	*/

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}