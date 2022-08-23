#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void noise_gaussian();
void filter_bilateral();
void filter_median();

// ��ȣ ó�� �������� ����(noise)�̶� ���� ��ȣ�� �߰��� ��ġ ���� ��ȣ�� �ǹ�
// ������ �����Ǵ� ����� ���� ��(noise model)�̶�� �ϸ�, �پ��� ���� �� �߿��� ���� ��ǥ���� ���� ���� ����þ� ���� ��(Gaussian noise model) dlek 
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
		* randn() �Լ��� ����þ� �������� ������ ����� �����Ͽ� ��ȯ
		* randn() �Լ��� dst ����� ����þ� ������ ������ ������ ä��
		 void randn(InputOutputArray dst, InputArray mean, InputArray stddev);
			- dst : ����þ� ������ ä���� ���. dst ����� �̸� �Ҵ��� �Ǿ� �־�� �մϴ�.
			- mean : ����þ� ���� ���
			- stddev : ����þ� ���� ǥ�� ����
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

// ����� ���� 
// ��κ��� ���󿡴� ����þ� ������ ���ԵǾ� ������ ���� ��ǻ�� ���� �ý����� ����þ� ������ �����ϱ� ���� ����þ� ���͸� ���
// �Է� ���󿡼� �ȼ� ���� ũ�� ������ �ʴ� ��ź�� ������ ����þ� ���Ͱ� ����� ���, 
// �ֺ� �ȼ� ���� �ε巴�� �����Ǹ鼭 ������ ���⵵ ũ�� �پ���. 
// �׷��� �ȼ� ���� �ް��ϰ� ����Ǵ� ���� �ٹ濡 ������ ����þ� ���Ͱ� ����Ǹ� �����Ӹ� �ƴ϶� ���� ���б��� �Բ� �����ϰ� �ȴ�. 
// ��, ������ �پ��鼭 �Բ� ������ �������� ������ ��ü�� ������ �帴�ϰ� �ٲ�� �ȴ� 

// ���� �����ϱ� ���� ���� ������� ���� ������ �״�� �����ϸ鼭 ������ �����ϴ� ���� ���� ���� ���� ����(edge-preserving noise removal filter)�� ���� �����Ͽ���. 
// Ư�� 1998�� �丶��(C. Tomasi)�� ������ ����� ����(bilateral filter)�� ���� ������ �״�� �����ϸ鼭 ����þ� ������ ȿ�������� �����ϴ� �˰���
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
	* bilateralFilter() �Լ��� �̿��Ͽ� ����� ���͸� ����
	void bilateralFilter(InputArray src, OutputArray dst, int d,
                     double sigmaColor, double sigmaSpace,
                     int borderType = BORDER_DEFAULT);
					 - src : �Է� ����. 8��Ʈ �Ǵ� �Ǽ���, 1ä�� �Ǵ� 3ä�� ����
					 - dst : ��� ����. src�� ���� ũ��, ���� Ÿ��
					 - d : ���͸��� ����� �̿� �ȼ����� �Ÿ�(����). ����� �ƴ� ��(���� ��� -1)�� �����ϸ� sigmaSpace�κ��� �ڵ� ���
					 - sigmaColor : �� ���������� ����þ� ���� ǥ�� ����
					 - sigmaSpace : ��ǥ ���������� ����þ� ���� ǥ�� ����
					 - borderType :�����ڸ� �ȼ� Ȯ�� ���
	*/
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}

// �̵�� ����(median filter)�� �Է� ���󿡼� �ڱ� �ڽ� �ȼ��� �ֺ� �ȼ� �� �߿��� �߰���(median)�� �����Ͽ� ��� ���� �ȼ� ������ �����ϴ� ���͸� ���
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
	* medianBlur() �Լ��� �̿��Ͽ� �̵�� ���͸��� ����
	void medianBlur(InputArray src, OutputArray dst, int ksize);
		- src : �Է� ����. 1, 3, 4ä�� ����. ksize�� 3 �Ǵ� 5�̸� src�� CV_8U, CV_16U, CV_32F�� ���̸� ���� �� �ְ�, 
				�� �̻��� ���� ũ�⿡���� CV_8U ���̸� ����� �� �ִ�
		- dst : ��� ����. src�� ���� ũ��, ���� Ÿ���� ���´�
		- ksize : ���� ũ��. 3���� ���ų� ū Ȧ���� ����
	*/

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}