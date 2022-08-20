#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void filter_embossing();

// ���� ó������ ���͸�(filtering)�̶� ���󿡼� ���ϴ� ������ �����Ű�� ��ġ �ʴ� ������ �ɷ� ���� �۾�
// ������ ���͸��� ���� ����ũ(mask)��� �θ��� ���� ũ���� ����� �̿�
// ����ũ�� ���͸��� ������ �����ϴ� ����̸� Ŀ��(kernel), ������(window)��� �θ���, ��쿡 ���󼭴� ����ũ ��ü�� ����
int main(void)
{
	filter_embossing();

	return 0;
}

void filter_embossing()
{
	Mat src = imread("images/rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	float data[] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
	Mat emboss(3, 3, CV_32FC1, data); // ������(embossing) ���͸�

	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);
	/*
	* 
	void filter2D(InputArray src, OutputArray dst, int ddepth,
              InputArray kernel, Point anchor = Point(-1,-1),
              double delta = 0, int borderType = BORDER_DEFAULT);
			  - src : �Է� ����
			  - dst : ��� ����. src�� ���� ũ��, ���� ä�� ��
			  - ddepth : ��� ������ ����
			  - kernel : ���͸� Ŀ��. 1ä�� �Ǽ��� ���
			  - anchor : ������ ��ǥ. Point(-1, -1)�� �����ϸ� Ŀ�� �߽��� ���������� ���
			  - delta  : ���͸� ���� �� �߰������� ���� ��
			  - borderType : �����ڸ� �ȼ� Ȯ�� ���
	*/

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}