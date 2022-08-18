#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	Mat src1 = imread("images/lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("images/square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	// ������ ��Ʈ ���� �� ������ �����ϴ� bitwise_and(), bitwise_or(), bitwise_xor(), bitwise_not() �Լ��� ����
	bitwise_and(src1, src2, dst1);
	bitwise_or(src1, src2, dst2);
	bitwise_xor(src1, src2, dst3);
	bitwise_not(src1, dst4);
	/*
	* ��Ʈ ���� ���� 
	* void bitwise_and(InputArray src1, InputArray src2,
                 OutputArray dst, InputArray mask = noArray());
	* ��Ʈ ���� ���� 
	* void bitwise_or(InputArray src1, InputArray src2,
                 OutputArray dst, InputArray mask = noArray());
	* ��Ʈ ���� ��Ÿ�� ����
	* void bitwise_xor(InputArray src1, InputArray src2,
                 OutputArray dst, InputArray mask = noArray());
	* ��Ʈ ���� ���� ����
	* void bitwise_not(InputArray src1, OutputArray dst, InputArray mask = noArray());
			- src1 : ù ��° �Է� ��� �Ǵ� ��Į��
			- src2 : �� ��° �Է� ��� �Ǵ� ��Į��. src1�� ũ��� Ÿ���� ���ƾ� �մϴ�.
			- dst  : ��� ���. src1�� ���� ũ��, ���� Ÿ������ �����˴ϴ�. dst ��� ���� ���� �� ���� ������ ���� ���� �ٸ��� �����˴ϴ�.
			- mask : ����ũ ����
	*/

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();

	return 0;
}