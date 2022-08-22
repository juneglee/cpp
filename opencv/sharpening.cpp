#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void unsharp_mask();

// ������(sharpening)�̶� ������ ��ī�ο� ������ ������ �����ϴ� ���͸� ���
// ��ī�ο� ������ �����̶� ������ �� ���� ����ó�� ��ü�� ������ �ѷ��ϰ� ���еǴ� ������ �ǹ�
// �̹� �Կ��� ������ ������ �� ���� ����ó�� ���̰Բ� �����Ϸ��� ���� ���� �ٹ濡�� �ȼ� ���� ��Ϻ� Ŀ������ �����ؾ� �Ѵ�
int main(void)
{
	unsharp_mask();

	return 0;
}

// ������ ����� �����ؼ� ��̷ο� ����� �������� �����ϱ� ���� ������ ������ ����Ѵ�
//  ������ ����Ǿ� �ε巯���� ������ Ȱ���Ͽ� �ݴ�� ��ī�ο� ������ ����
// ������ ����� ����, �� ��ī���� ���� ������ �����(unsharp)�ϴٰ� ���ϱ⵵ �Ѵ�

void unsharp_mask()
{
	Mat src = imread("images/rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);

	// 	����þ� ������ ǥ�� ���� sigma ���� 1���� 5���� ������Ű�鼭 ����� ����ũ ���͸��� ����
	for (int sigma = 1; sigma <= 5; sigma++) {
		Mat blurred;
		// 	����þ� ���͸� �̿��� ���� ������ blurred�� ����
		GaussianBlur(src, blurred, Size(), sigma); 

		// ����� ����ũ ���͸��� ����
		float alpha = 1.f;
		Mat dst = (1 + alpha) * src - alpha * blurred;

		// 	������ ��� ���� dst�� ���� sigma ���� ���
		String desc = format("sigma: %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}