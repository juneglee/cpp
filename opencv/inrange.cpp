#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int lower_hue = 40, upper_hue = 80;
Mat src, src_hsv, mask;

void on_hue_changed(int, void*);

// ���� ���� ������ ���� ���� ����
// HSV �� �������� inRange() �Լ��� �̿��Ͽ� ����ڰ� ������ ���� ������ ����
// ���� ��� �Է� ���󿡼� ������ �ȼ��� ��� ã�Ƴ��� ������ ��ü�� ��ġ�� ũ�⸦ �� �� �ִ�.
int main(int argc, char* argv[])
{
	src = imread("images/candies.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	cvtColor(src, src_hsv, COLOR_BGR2HSV);

	imshow("src", src);

	namedWindow("mask");
	// ������ ���� ���� ���� ���� ������ �� �ִ� �� ���� Ʈ���ٸ� ����
	// ������ �ִ��� 179�� �����ϰ�, �� Ʈ������ �ݹ� �Լ��� ��� on_hue_change() �Լ��� ����
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
	on_hue_changed(0, 0);

	waitKey();
	return 0;
}

void on_hue_changed(int, void*)
{
	Scalar lowerb(lower_hue, 100, 0);
	Scalar upperb(upper_hue, 255, 255);
	inRange(src_hsv, lowerb, upperb, mask);
	// inRange() �Լ��� �Է� ���� src�� �ȼ� ���� ������ ��� �Ǵ� ���� ������ ���ԵǾ� ������ ���, �׷��� ������ ���������� ä���� ����ũ ���� dst�� ��ȯ
	/*  ����� ���� ���� Ư�� ���� �ȿ� �ִ��� Ȯ���Ϸ��� inRange() �Լ��� ���
	void inRange(InputArray src, InputArray lowerb,
				 InputArray upperb, OutputArray dst);
				 - src : �Է� ����
				 - lowerb : ���� ��. �ַ� Mat �Ǵ� Scalar ��ü�� ����
				 - upperb : ���� ��. �ַ� Mat �Ǵ� Scalar ��ü�� ����
				 - dst : ��� ����ũ ����. �Է� ����� ũ�Ⱑ ����, Ÿ���� CV_8UC1
	*/
	imshow("mask", mask);
}