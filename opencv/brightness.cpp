#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void brightness1();
void brightness2();
void brightness3();
void brightness4();
void on_brightness(int pos, void* userdata);

int main(void)
{
	brightness1();
	brightness2();
	brightness3();
	brightness4();

	return 0;
}

// �׷��̽����� ���� �ٷ��
// Mat img1 = imread(��lenna.bmp��, IMREAD_GRAYSCALE);

void brightness1()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst = src + 100;
	// src�� dst ������ Mat Ŭ���� Ÿ���̰�, ���� 100�� �Ϲ����� int �ڷ���
	// OpenCV������ ����, ���� �����ڿ� ���Ͽ� ������ �����ǰ� �Ǿ� �־ Mat ��ü�� C/C++ �⺻ �ڷ������� ���� �� ���� ������ ����
	// ��, src�� �׷��̽����� �����̹Ƿ� ���� ���� ����� 255���� Ŭ ��� dst ������ �ȼ� ���� 255�� ����

	imshow("src", src);
	imshow("dst", dst);
	// rc â�� �Է� ���� �����̰�, dst â�� ��Ⱑ 100��ŭ ������ ��� ������ ��Ÿ����
	waitKey();

	destroyAllWindows();
}

void brightness2()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

void brightness3()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			/*
			template<> inline
			uchar saturate_cast<uchar>( int v );
				- v      : int �ڷ����� ǥ���� �� �ִ� ������ ����
				- ��ȯ�� : 0~255 ������ ����
			saturate_cast() �Լ��� ���� ���ø����� ���ǵ� �Լ��̱� ������ <> ��ȣ ���̿� ����ϴ� �ڷ����� ����ؾ� �մϴ�. 
			�տ� ��Ÿ�� saturate_cast() �Լ� ������ int �ڷ����� ���� uchar �ڷ��� ������ ��ȭ ������ �����մϴ�. 
			�׷��̽����� ���󿡼��� uchar Ÿ������ �ȼ� ���� ǥ���ϱ� ������ ��� ���� �ڵ忡 ��ȭ ������ �߰��Ϸ��� ������ ���� �ڵ带 �ۼ�
			*/
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
			// 	��� ������ �ȼ� ���� saturate_cast() �Լ��� �̿��Ͽ� ��ȭ ������ ������ �� ��� ���� �ȼ� ������ ����
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

void brightness4()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src); 
	// reateTrackbar() �Լ��� ȣ���� �� Ʈ������ �ִ��� 100���� �����Ͽ��⿡ ���� dst â�� ��Ÿ�� Ʈ���ٴ� 0���� 100 ���̿��� �� ��ġ�� ������ �� �ִ�
	on_brightness(0, (void*)&src); 
	//  on_brightness() �ݹ� �Լ��� ������ ȣ���ϴ� �ڵ�

	waitKey();
	destroyAllWindows();
}

void on_brightness(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst);
}