#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void hough_lines();
void hough_line_segments();
void hough_circles();

int main(void)
{
	hough_lines();
	hough_line_segments();
	hough_circles();

	return 0;
}

// ���󿡼� ������ ã�� ���� �뵵�� ���� ��ȯ(hough transform) ���
void hough_lines()
{
	Mat src = imread("images/building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);
	/*
	* HoughLines() �Լ��� ����Ͽ� ���� ��ȯ ���� ������ ����
	void HoughLines(InputArray image, OutputArray lines,
                double rho, double theta, int threshold,
                double srn = 0, double stn = 0,
                double min_theta = 0, double max_theta = CV_PI);
				- image : 8��Ʈ ���� ä�� �Է� ����. �ַ� ���� ������ ����
				- lines : ���� ����(rho, theta)�� ������ ��� ����
				- rho : ���� �迭���� �� ���� �ػ�(�ȼ� ����)
				- theta : ���� �迭���� �� ���� �ػ�(���� ����)
				- threshold : ���� �迭���� �������� �Ǵ��� �Ӱ谪
				- srn : ��Ƽ������ ���� ��ȯ���� rho �ػ󵵸� ������ ��. 
						srn�� ���� �Ǽ��� �����ϸ� rho �ػ󵵿� rho/srn �ػ󵵸� ���� �̿��Ͽ� ��Ƽ������ ���� ��ȯ�� ����
						srn�� stn�� ��� 0�̸� �Ϲ� ���� ��ȯ�� ����
				- stn : ��Ƽ������ ���� ��ȯ���� theta �ػ󵵸� ������ ��
				- min_theta : ������ ������ �ּ� theta ��
				- max_theta : ������ ������ �ִ� theta ��
	*/

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		float cos_t = cos(theta), sin_t = sin(theta);
		float x0 = rho * cos_t, y0 = rho * sin_t;
		float alpha = 1000;

		Point pt1(cvRound(x0 - alpha * sin_t), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 + alpha * sin_t), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

// �⺻���� ���� ��ȯ ���� ���� ��� �ܿ� Ȯ���� ���� ��ȯ(probabilistic Hough transform)�� ���� ���� ���� ����� ����
void hough_line_segments()
{
	Mat src = imread("images/building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);
	/* 
	* Ȯ���� ���� ��ȯ ����� HoughLinesP()
	* Ȯ���� ���� ��ȯ ����� ������ ������ �Ķ���� ��� �踦 ��ȯ�ϴ� ���� �ƴ϶� ������ �������� ���� ��ǥ�� ��ȯ
	void HoughLinesP(InputArray image, OutputArray lines,
					 double rho, double theta, int threshold,
					 double minLineLength = 0, double maxLineGap = 0);
					 - image : 8��Ʈ ���� ä�� �Է� ����. �ַ� ���� ������ ����
					 - lines : ������ �������� ������ ����(x1, y1, x2, y2)�� ������ ��� ����
					 - rho : ���� �迭���� �� ���� �ػ�(�ȼ� ����)
					 - theta : ���� �迭���� �� ���� �ػ�(���� ����)
					 - threshold : ���� �迭���� �������� �Ǵ��� �Ӱ谪
					 - minLineLength : ������ ������ �ּ� ����
					 - maxLineGap : �������� ������ �ִ� ���� �� ����
	*/

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (Vec4i l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

// �Ϲ����� ���� ��ȯ ��� ���� �׷����Ʈ ���(Hough gradient method)�� ����Ͽ� ���� ����
void hough_circles()
{
	Mat src = imread("images/coins.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat blurred;
	blur(src, blurred, Size(3, 3));

	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);
	/*
	* HoughCircles() �Լ��� ����Ͽ� ���� ����
	void HoughCircles(InputArray image, OutputArray circles,
					  int method, double dp, double minDist,
					  double param1 = 100, double param2 = 100,
					  int minRadius = 0, int maxRadius = 0);
					  - image : �Է� ����. ���� ������ �ƴ� ���� �׷��̽����� ������ ����
					  - circles : ����� �� ������ ������ ��� ����
					  - method : HOUGH_GRADIENT�� ���� ����
					  - dp : �Է� ����� ���� �迭�� ũ�� ����
					  - minDist : ������ �� �߽��� �ּ� �Ÿ�
					  - param1 : Canny ���� ������� ���� �Ӱ谪
					  - param2 : ���� �迭���� �� ������ ���� �Ӱ谪
					  - minRadius : ������ ���� �ּ� ������
					  - maxRadius : ������ ���� �ִ� ������
	*/

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles) {
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}