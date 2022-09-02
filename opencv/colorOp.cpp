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
	Mat img = imread("images/butterfly.jpg", IMREAD_COLOR); // IMREAD_COLOR�� �����ϸ� ������ 3ä�� �÷� ���� 

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	// �÷� ������ ���� RGB��� �θ��� ������(R), ���(G), �Ķ���(B) ���� ������ �������� �ȼ� ���� ǥ��
	// ���� ���� ���� 0�̸� �ش� ���� ������ ���� ���� �����̰�, 255�̸� �ش� ���� ������ ���� �� ������ �ǹ�
	// Vec3b Ŭ������ ũ�Ⱑ 3�� uchar �ڷ��� �迭�� ��� ������ ������ �ִ� Ŭ����
	// Vec3b Ŭ������ ����Ʈ ũ��� ��Ȯ�ϰ� 3����Ʈ�̸�, �̴� ���� 3ä�� �÷� ������ �� �ȼ��� �����ϴ� ����Ʈ ���� ����
	// �÷� ���󿡼� �ȼ� ���� ������ ������ Mat::at() �Լ��� ���
	Vec3b& pixel = img.at<Vec3b>(0, 0);
	uchar b1 = pixel[0];
	uchar g1 = pixel[1];
	uchar r1 = pixel[2];

	Vec3b* ptr = img.ptr<Vec3b>(0);
	uchar b2 = ptr[0][0];
	uchar g2 = ptr[0][1];
	uchar r2 = ptr[0][2];
}

// �ȼ� �� ���� ����� �̿��Ͽ� �÷� ������ ����
void color_inverse()
{
	Mat src = imread("images/butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	// src ����� dst ������ (i, j) ��ġ �ȼ� ���� ���� Vec3b �ڷ��� ���� p1�� p2�� ������ �Ŀ� ����
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
	*  ������ �� ������ �ٸ� �� �������� ��ȯ�� ������ cvtColor() �Լ��� ���
	void cvtColor(InputArray src, OutputArray dst, int code, int dstCn = 0);
		- src : �Է� ����. CV_8U, CV_16U, CV_32F �� �ϳ��� ���̸� ���
		- dst : ��� ����. src�� ũ�� �� ���̰� ����
		- code : �� ���� ��ȯ �ڵ�. ColorConversionCodes ������ ��� �� �ϳ��� ����
		- dstCn : ��� ������ ä�� ��. 0�̸� �ڵ����� ����
	*/

	/* 
	* �ֿ� �� ���� ��ȯ �ڵ� 
	- COLOR_BGR2RGB  : BGR ä�� ������ RGB ä�� ������ ��ȣ ��ȯ
	  COLOR_RGB2BGR
	- COLOR_BGR2GRAY : 3ä�� BGR �÷� ������ 1ä�� �׷��̽����� �������� ��ȯ
	- COLOR_GRAY2BGR : 1ä�� �׷��̽����� ������ 3ä�� BGR �÷� �������� ��ȯ
	- COLOR_BGR2XYZ : BGR �� ������ CIE XYZ �� �������� ��ȯ
	- COLOR_XYZ2BGR : CIE XYZ �� ������ BGR �� �������� ��ȯ
	- COLOR_BGR2YCrCb : BGR �� ������ YCrCb �� �������� ��ȯ
	- COLOR_YCrCb2BGR : YCrCb �� ������ BGR �� �������� ��ȯ
	- COLOR_BGR2HSV : BGR �� ������ HSV �� �������� ��ȯ
	- COLOR_HSV2BGR : HSV �� ������ BGR �� �������� ��ȯ
	- COLOR_BGR2Lab : BGR �� ������ CIE Lab �� �������� ��ȯ
	- COLOR_Lab2BGR : CIE Lab �� ������ BGR �� �������� ��ȯ
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
	* ��ä�� ����� 1ä�� ��� ���� ���� ��ȯ�� ������ split() �Լ��� ���
	void split(const Mat& src, Mat* mvbegin);
	void split(InputArray src, OutputArrayOfArrays mv);
		- src : �Է� ��ä�� ���
		- mvbegin : �и��� 1ä�� ����� ������ Mat �迭 �ּ�. 
					���� �迭 ������ src ���� ä�� ���� ���ƾ� �Ѵ�
		- mv : �и��� 1ä�� ����� ������ ����
	*/

	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);
	imshow("G_plane", bgr_planes[1]);
	imshow("R_plane", bgr_planes[2]);

	waitKey();
	destroyAllWindows();
}