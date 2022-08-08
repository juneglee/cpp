#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void contrast1();
void contrast2();

// ��� ��� (��Ʈ��Ʈ(contrast))
// ��Ϻ�� ���󿡼� ���� ������ ��ο� ���� ���̿� �巯���� ��� ������ ������ �ǹ�
// ���� ���������� ��Ӱų� �Ǵ� ���������� ���� �ȼ��θ� ������ ���, ��Ϻ� ���ٰ� ǥ���մϴ�.
// �ݸ鿡 ���� ������ ��ο� ������ ���� ���� �ִ� ������ ��Ϻ� ���ٰ� ���մϴ�.
// �Ϲ������� ��Ϻ� ���� ������ ��ü ���� ������ �� ���� �ʾƼ� ���������� �帴�ϰ� ��������, 
// ��Ϻ� ���� ������ �繰�� ������ �� �Ǹ� ������ ������ �ش�. 

int main(void)
{
	contrast1();
	contrast2();

	return 0;
}

// �Ϲ������� ��Ϻ� ���� ������ �� ���� ����ó�� ���̱� ������ ��κ��� ������ ī�޶�� ��Ϻ� ���� ������ �Կ��ϵ��� ����
void contrast1()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// C/C++ �Ǽ��� �ڷ����� Mat ��ü ������ ���� ������ �����ǵ� �����ϸ�, 
	// �� ��� Mat ����� ��� ���ҿ� �־��� �Ǽ� ���� ���� ��� ����� ��ȯ
	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src); // src�� �Է� ����
	imshow("dst", dst); // dst�� ��� ����
	waitKey();

	destroyAllWindows();
}

// ȿ������ ��Ϻ� ���� ���
// ��Ϻ� ȿ�������� ���̱� ���ؼ��� ���� �ȼ��� ���� ���, ��ο� �ȼ��� ���� ��ο����� ����
void contrast2()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// �׷��̽����� ���� �߰����� 128�� �������� ��Ϻ� �����ϴ� ����� ����
	// �Է� ������ �ȼ� ���� 128���� ũ�� ���� ��� �����, 128���� ������ �ȼ� ���� �� �۰� ����� ���
	// �ݴ�� ��Ϻ� ���ҽ�Ű���� 128���� ū �Է� ���� �ȼ� ���� �� �� �۰� �����, 128���� ���� �ȼ� ���� ������ 128�� ������ ����
	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;


	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}