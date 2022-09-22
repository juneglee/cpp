#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// ������ ����ȭ(binarization)�� ������ �� �ȼ��� �� ���� �η��� ������ �۾�
// �Է� ������ �ֿ� ��ü ������ ��� �������� �����ų� 
// �Ǵ� ���󿡼� �߿䵵�� ���� ���� ����(ROI, Region Of Interest)�� �׷��� ���� ����� �������� �����ϴ� �뵵�� ����ȭ�� ���� �� �ִ�
// ������ ��ǻ�� �о߿��� ����ȭ�� �Է� ���� 0 �Ǵ� 1�� ���������� ������ ����ȭ������ �ȼ� ���� 0 �Ǵ� 255�� ����
// �׷��̽����� ���� ���� ����ȭ�� �����Ϸ��� ������ �ȼ� ���� Ư�� ������ ũ�� 255�� �����ϰ�, ������ 0���� ����
void on_threshold(int pos, void* userdata);

int main(int argc, char* argv[])
{
	Mat src;

	if (argc < 2)
		src = imread("images/neutrophils.png", IMREAD_GRAYSCALE);
	else
		src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src); // Ʈ������ �ִ��� 255�̰�, Ʈ���� �ݹ� �Լ� �̸��� on_threshold
	setTrackbarPos("Threshold", "dst", 128); // ���α׷��� ó�� ����� �� Ʈ���� ��ġ�� 128�� �ǵ��� �����Ͽ� on_threshold() �Լ��� ó���� �� �� ����

	waitKey();
	return 0;
}

void on_threshold(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;

	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY); 
	// ����ڰ� ������ Ʈ���� ��ġ�� �̿��Ͽ� ����ȭ�� ����
	/*
	* threshold() �Լ��� �Ӱ谪�� �̿��� �پ��� ������ �����ϴ� �Լ�
	double threshold(InputArray src, OutputArray dst,
		double thresh, double maxval, int type);
		- src : �Է� ����
		- dst : ��� ����. �Է� ����� ���� ũ��, ���� Ÿ��
		- thresh : �Ӱ谪
		- maxval : THRESH_BINARY �Ǵ� THRESH_BINARY_INV ����� ����� �� ��� ������ �ִ�
		- type : �Ӱ谪 ���� ���. ThresholdTypes ������ ����� ����
		- ��ȯ�� : ���� �Ӱ谪. THRESH_OTSU �Ǵ� THRESH_TRIANGLE ����� ����� �� �ڵ����� ������ �Ӱ谪�� ��ȯ
	*/
	// ThresholdTypes ������ ��� 
	// THRESH_BINARY, THRESH_BINARY_INV, THRESH_TRUNC, THRESH_TOZERO, THRESH_TOZERO_INV �ټ� ���� ����� threshold() �Լ��� ������ ����
	// THRESH_OTSU�� THRESH_TRIANGLE ����� ������ �ȼ� �� ������ �м��Ͽ� �Ӱ谪�� �ڵ����� �����Ͽ� ����ȭ�� ����
	
	imshow("dst", dst);
}