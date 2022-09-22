#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// ������׷� ������ 
// ���� �������κ��� ã���� �ϴ� ��ü�� �÷� ������׷��� �̸� ���ϰ�, �־��� �Է� ���󿡼� �ش� ������׷��� �����ϴ� ������ ã�Ƴ��� ���
// ��ó�� �־��� ������׷� �𵨰� ��ġ�ϴ� �ȼ��� ã�Ƴ��� ����� ������׷� ������(histogram backprojection)�̶�� �Ѵ�
// ���� ��� �Ǻλ��� ���� ���� ������׷��� ������ �ִٸ� ������ ����� ����Ͽ� ���󿡼� �Ǻλ� ������ ������ �� �ִ�
int main()
{
	// Calculate CrCb histogram from a reference image
	Mat ref, ref_ycrcb, mask;
	ref = imread("images/ref.png", IMREAD_COLOR);
	mask = imread("images/mask.bmp", IMREAD_GRAYSCALE);
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

	Mat hist;
	int channels[] = { 1, 2 };
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = { cr_bins, cb_bins };
	float cr_range[] = { 0, 256 };
	float cb_range[] = { 0, 256 };
	const float* ranges[] = { cr_range, cb_range };

	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

	// Apply histogram backprojection to an input image
	Mat src, src_ycrcb;
	src = imread("images/kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	Mat backproj;
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);
	/* ������׷� �������� calcBackProject() �Լ��� �̿��Ͽ� ����
	void calcBackProject(const Mat* images, int nimages,
		 const int* channels, InputArray hist,
		 OutputArray backProject, const float** ranges,
		 double scale = 1, bool uniform = true);
		 - images : �Է� ������ �迭 �Ǵ� �Է� ������ �ּ�. ������ �迭�� ���, ��� ������ ũ��� ���̴� ���ƾ� �Ѵ� 
		 - nimages : �Է� ���� ����
		 - channels : ������ ��� �� ����� ä�� ��ȣ �迭
		 - hist : �Է� ������׷�
		 - backProject : ��� ������׷� ������ ����. �Է� ����� ���� ũ��, ���� ���̸� ���� 1ä�� ���
		 - ranges : �� ������ ������׷� �� ������ ��Ÿ���� �迭�� �迭
		 - scale : ������׷� ������ ���� �߰������� ���� ��
		 - uniform : ������׷� ���� ������ �յ������� ��Ÿ���� �÷���
	*/

	imshow("src", src);
	imshow("backproj", backproj);
	waitKey();

	return 0;
}