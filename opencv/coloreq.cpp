#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// �÷� ������׷� ��Ȱȭ�� ����
// ������׷� ��Ȱȭ : ������׷� ������ �̿��Ͽ� ��Ϻ� ����
// OpenCV������ equalizeHist() �Լ��� ���� ������׷� ��Ȱȭ�� ������ �� ������ equalizeHist() �Լ��� �׷��̽����� ���� �Է��� ����
// �׷��Ƿ� 3ä�� �÷� ���� ���� ������׷� ��Ȱȭ�� �����Ϸ��� openCV �Լ��� �����ؾ� �Ѵ� 
int main(void)
{
	Mat src = imread("images/pepper.bmp", IMREAD_COLOR); // ä�� BGR ����

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb); // BGR �� ������ src ������ YCrCb �� �������� �����Ͽ� src_ycrcb�� ����

	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);// src_ycrcb ������ ä���� �и��Ͽ� ycrcb_planes�� ����

	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]); // 	Y ���п� �ش��ϴ� ycrcb_planes[0] ���� ���ؼ��� ������׷� ��Ȱȭ�� ����

	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb); // 	ycrcb_planes ���Ϳ� ��� �ִ� �� ������ ���ļ� dst_ycrcb ������ ����

	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR); // 	dst_ycrcb ������ �� ������ BGR �� �������� ��ȯ�Ͽ� dst�� ����

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	return 0;
}