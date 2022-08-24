#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void affine_transform();
void affine_translation();
void affine_shear();
void affine_scale();
void affine_rotation();
void affine_flip();

// ������ ��ȯ�� ������ ���� �̵�, Ȯ�� �� ���, ȸ�� ���� �������� ���� �� �ִ� �������� ��ȯ
int main(void)
{
	// ������ ��ȯ�� ��� ���� ���� �Ķ���͸� �̿��� �������� ����
	affine_transform();
	affine_translation();
	affine_shear();
	affine_scale();
	affine_rotation();
	affine_flip();

	return 0;
}

void affine_transform()
{
	Mat src = imread("images/tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(50, 50);
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);

	Mat M = getAffineTransform(srcPts, dstPts);
	/*
	* ������ ��ȯ ����� ���ϴ� �Լ� �̸��� getAffineTransform()
	Mat getAffineTransform(const Point2f src[], const Point2f dst[]);
	Mat getAffineTransform(InputArray src, InputArray dst);
		- src : �Է� ���󿡼� �� ���� ��ǥ
		- dst : ��� ���󿡼� �� ���� ��ǥ
		- ��ȯ�� : 2��3 ������ ��ȯ ���. CV_64FC1
	*/

	Mat dst;
	warpAffine(src, dst, M, Size());
	/* 
	* 2��3 ������ ��ȯ ����� ������ ���� ��, ������ ������ ��ȯ�� ��� ������ �����Ϸ��� warpAffine() �Լ��� ���
	void warpAffine(InputArray src, OutputArray dst,
                InputArray M, Size dsize,
                int flags = INTER_LINEAR,
                int borderMode = BORDER_CONSTANT,
                const Scalar& borderValue = Scalar());
				- src : �Է� ����
				- dst : ��� ����. src�� ���� Ÿ���̰�, ũ��� dsize�� ���� �����˴ϴ�.
				- M : 2��3 ������ ��ȯ ���
				- dsize : ��� ���� ũ��
				- flags : ������ �˰���. ���� OR �����ڸ� �̿��Ͽ� WARP_INVERSE_MAP �÷��׸� �Բ� �����ϸ� ���������� ��ȯ�� �����մϴ�.
				- borderMode : �����ڸ� �ȼ� Ȯ�� ���. BorderTypes ������ ��� �� �ϳ��� �����մϴ�. 
							���� BORDER_TRANSPARENT�� �����ϸ� �Է� ������ �ȼ� ���� ������� �ʴ� ������ dst �ȼ� ���� �״�� �����մϴ�.
				- borderValue : borderMode�� BORDER_CONSTANT�� �� ����� ��� ��. �⺻������ �������� �����Ǿ� �ֽ��ϴ�.
	*/

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

// ������ �̵� ��ȯ(translation transformation)�� ������ ���� �Ǵ� ���� �������� ���� ũ�⸸ŭ �̵���Ű�� ������ �ǹ��ϸ� ����Ʈ(shift) �����̶�� �Ѵ� 
void affine_translation()
{
	Mat src = imread("images/tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat M = Mat_<double>({ 2, 3 }, { 1, 0, 150, 0, 1, 100 });

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

// ���� ��ȯ(shear transformation)�� ���簢�� ������ ������ ���� �������� �о ����纯�� ������� �����Ǵ� ��ȯ�̸� ���и� ��ȯ�̶�� �Ѵ�
void affine_shear()
{
	Mat src = imread("images/tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	double mx = 0.3;
	Mat M = Mat_<double>({ 2, 3 }, { 1, mx, 0, 0, 1, 0 });

	Mat dst;
	warpAffine(src, dst, M, Size(cvRound(src.cols + src.rows * mx), src.rows));

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

// ������ ũ�� ��ȯ(scale transformation)�� ������ ��ü���� ũ�⸦ Ȯ�� �Ǵ� ����ϴ� ��ȯ
void affine_scale()
{
	Mat src = imread("images/rose.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2, dst3, dst4;
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST);
	resize(src, dst2, Size(1920, 1280));
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);
	/* 
	* ũ�⸦ ������ �� �ִ� resize() �Լ�
	void resize(InputArray src, OutputArray dst,
				Size dsize, double fx = 0, double fy = 0,
				int interpolation = INTER_LINEAR);
				- src : �Է� ����
				- dst : ��� ����
				- dsize : ��� ���� ũ��
				- fx : x�� ���������� ũ�� ��ȯ ����. dsize�� Size()�� ������ ��쿡 ���
				- fy : y�� ���������� ũ�� ��ȯ ����. dsize�� Size()�� ������ ��쿡 ���
				- interpolation : ������ ����. INTER_NEAREST, INTER_LINEAR, INTER_CUBIC, INTER_AREA, INTER_LANCZOS4 �� �ϳ��� ����
						- INTER_NEAREST  : �ֱٹ� �̿� ������
						- INTER_LINEAR   : �缱�� ������
						- INTER_CUBIC    : 3�� ������
						- INTER_AREA     : �ȼ� ���� �����ø�
						- INTER_LANCZOS4 : 8��8 �̿� �ȼ��� ����ϴ� ���ʽ�(Lanczos) ������
	*/

	imshow("src", src);
	imshow("dst1", dst1(Rect(400, 500, 400, 400)));
	imshow("dst2", dst2(Rect(400, 500, 400, 400)));
	imshow("dst3", dst3(Rect(400, 500, 400, 400)));
	imshow("dst4", dst4(Rect(400, 500, 400, 400)));

	waitKey();
	destroyAllWindows();
}

// ������ ȸ�� ��ȯ(rotation transformation)�� Ư�� ��ǥ�� �������� ������ ���ϴ� ������ŭ ȸ���ϴ� ��ȯ
void affine_rotation()
{
	Mat src = imread("images/tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Point2f cp(src.cols / 2.f, src.rows / 2.f);
	Mat M = getRotationMatrix2D(cp, 20, 1);
	/*
	*  ������ ȸ���� ���� ������ ��ȯ ����� �����ϴ� getRotationMatrix2D() �Լ��� ����
	Mat getRotationMatrix2D(Point2f center, double angle, double scale);
		- center : ȸ�� �߽� ��ǥ
		- angle  : ȸ�� ����. ����� �ݽð� ����, ������ �ð� ������ �ǹ��մϴ�.
		- scale  : ȸ�� �� �߰������� Ȯ�� �Ǵ� ����� ����. ũ�� ��ȯ�� �������� �������� 1�� �����մϴ�.
		- ��ȯ�� : 2��3 ������ ��ȯ ���(CV_64F)
	*/

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

// ������ �������� ��ȯ �߿� ������ �¿츦 ���� �ٲٰų�, �Ǵ� ���ϸ� ������ ������ ��ȯ
void affine_flip()
{
	Mat src = imread("images/eastsea.bmp");

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	int flipCode[] = { 1, 0, -1 };
	for (int i = 0; i < 3; i++) {
		flip(src, dst, flipCode[i]);
		/* 
		* flip() �Լ��� ������ ���� ����, ���� ����, �Ǵ� ���ο� ���� �� ���⿡ ���� ��Ī ��ȯ�� ������ ����
		void flip(InputArray src, OutputArray dst, int flipCode);
			- src : �Է� ����
			- dst : ��� ����. src�� ���� ũ��, Ÿ��
			- flipCode : ��Ī ��� ���� �÷���. flipCode�� ����̸� �¿� ��Ī, 0�̸� ���� ��Ī, �����̸� ���� ��Ī�� �¿� ��Ī�� ��� ����
		*/

		String desc = format("flipCode: %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}