#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void blurring_mean();
void blurring_gaussian();

// ����(blurring)�� ��ġ ������ ���� ���� ����ó�� ������ �ε巴�� ����� ���͸� ����̸� ������(smoothing)�̶�� �Ѵ�
// ���󿡼� ������ �ȼ� ���� �ȼ� �� ��ȭ�� ũ�� ���� ��� �ε巯�� ������ ���� �� �ִ�. 
// ������ ��ģ ������ �Է� ������ �ε巴�� ����� �뵵�� ���Ǳ⵵ �ϰ�, Ȥ�� �Է� ���� �����ϴ� ������ ������ �����ϴ� ��ó�� �������ε� ���ȴ�. 
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
		* blur() �Լ��� �̿��Ͽ� ��հ� ���͸��� ����
		void blur(InputArray src, OutputArray dst, Size ksize,
				  Point anchor = Point(-1,-1), int borderType = BORDER_DEFAULT);
				  - src : �Է� ����. ��ä�� ������ �� ä�κ��� ������ �����մϴ�. �Է� ������ ���̴� CV_8U, CV_16U, CV_16S, CV_32F, CV_64F �� �ϳ����� �մϴ�.
				  - dst : ��� ����. src�� ���� ũ��, ���� ä�� ���� �����ϴ�.
				  - ksize : ���� Ŀ�� ũ��
				  - anchor : ������ ��ǥ. Point(-1, -1)�� �����ϸ� Ŀ�� �߽��� ���������� ����մϴ�.
				  - borderType : �����ڸ� �ȼ� Ȯ�� ���

		*/

		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}

// ����þ� ���ʹ� ����þ� ����(Gaussian distribution) �Լ��� �ٻ��Ͽ� ������ ���� ����ũ�� ����ϴ� ���͸� ���
// ����þ� ������ ����� �߽����� �¿� ��Ī�� �� ���(bell shape)�� ���� Ȯ�� ������ ���ϸ� ���� ����(normal distribution)��� �Ѵ�
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
				  - src : �Է� ����. ��ä�� ������ �� ä�κ��� ������ ����
				  - dst : ��� ����. src�� ���� ũ��, ���� Ÿ���� ���´�.
				  - ksize : ����þ� Ŀ�� ũ��. ksize.width�� ksize.height�� 0���� ū Ȧ���̾�� �մϴ�. ksize�� Size()�� �����ϸ� ǥ�� �����κ��� Ŀ�� ũ�⸦ �ڵ����� �����Ѵ�
				  - sigmaX : x ���������� ����þ� Ŀ�� ǥ�� ����
				  - sigmaY : y ���������� ����þ� Ŀ�� ǥ�� ����. ���� sigmaY = 0�̸� sigmaX�� ���� ���� ����Ѵ�. 
								���� sigmaX�� simgaY�� ��� 0�̸� ksize�� width�� height �����κ��� ǥ�� ������ ����Ͽ� ����Ѵ�.
				  - borderType : �����ڸ� �ȼ� Ȯ�� ���
		*/

		String desc = format("Gaussian: sigma = %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}