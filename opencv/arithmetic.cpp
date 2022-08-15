#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	Mat src1 = imread("images/lenna.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("images/field.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	add(src1, src2, dst1);
	/* ������ ����
	* add() �Լ��� �� ���� ��� �Ǵ� ������ �Է����� �ް�, �ϳ��� ��� �Ǵ� ������ ������� ����
	void add(InputArray src1, InputArray src2, OutputArray dst,
         InputArray mask = noArray(), int dtype = -1);
		 - src1 : ù ��° �Է� ��� �Ǵ� ��Į��
		 - src2 : �� ��° �Է� ��� �Ǵ� ��Į��
		 - dst : �Է� ��İ� ���� ũ��, ���� ä�� ���� ���� ��� ���.
					dst�� ���̴� src1, src2�� ���̿� ���ų� �Ǵ� dtype ���ڿ� ���� �����˴ϴ�.
		 - mask : 8��Ʈ 1ä�� ����ũ ����. mask ��� ���� ���� 0�� �ƴ� ��ġ������ ���� ������ �����մϴ�.
		 - dtype : ��� ����� ����. src1�� src2�� ���̰� ���� ��쿡�� dtype�� -1�� ������ �� �ְ�, �� ��� dst�� ���̴� src1, src2�� ���� ���̷� ����
					src1�� src2�� ���̰� ���� �ٸ� ��쿡�� dtype�� �ݵ�� �����ؾ� �Ѵ�
	*/
	addWeighted(src1, 0.5, src2, 0.5, 0, dst2);
	/* �� ������ ����ġ ��
	* addWeighted() �Լ��� gamma ���ڸ� ���� ����ġ�� �տ� �߰����� ������ �Ѳ����� ����
	void addWeighted(InputArray src1, double alpha, InputArray src2,
					 double beta, double gamma, OutputArray dst, int dtype = -1);
		 - src1  : ù ��° �Է� ���
		 - alpha : src1 ����� ����ġ
		 - src2  : �� ��° �Է� ���. (src1�� ũ��� ä�� ���� ���ƾ� �Ѵ� )
		 - beta  : src2 ����� ����ġ
		 - gamma : ������ ����� �߰������� ���� ��
		 - dst   : ��� ���. �Է� ��İ� ���� ũ��, ���� ä�� ���� ����� ����
		 - dtype : ��� ����� ����. 
				   src1�� src2�� ���̰� ���� ��쿡�� dtype�� -1�� ������ �� �ְ�, �� ��� dst�� ���̴� src1, src2�� ���� ���̷� ����
				   src1�� src2�� ���̰� ���� �ٸ� ��쿡�� dtype�� �ݵ�� �����ؾ� �մϴ�.
	*/
	subtract(src1, src2, dst3);
	/* �� ������ ���� ���� 
	void subtract(InputArray src1, InputArray src2, OutputArray dst,
              InputArray mask = noArray(), int dtype = -1);
		 - src1  : ù ��° �Է� ��� �Ǵ� ��Į��
		 - src2  : �� ��° �Է� ��� �Ǵ� ��Į��
		 - dst   : �Է� ��İ� ���� ũ��, ���� ä�� ���� ���� ��� ���.
				   dst�� ���̴� src1, src2�� ���̿� ���ų� �Ǵ� dtype ���ڿ� ���� �����˴ϴ�.
		 - mask  : 8��Ʈ 1ä�� ����ũ ����. mask ��� ���� ���� 0�� �ƴ� ��ġ������ ���� ������ �����մϴ�.
		 - dtype : ��� ����� ����. src1�� src2�� ���̰� ���� ��쿡�� dtype�� -1�� ������ �� �ְ�, �� ��� dst�� ���̴� src1, src2�� ���� ���̷� ����
				   src1�� src2�� ���̰� ���� �ٸ� ��쿡�� dtype�� �ݵ�� �����ؾ� �Ѵ�
	*/
	absdiff(src1, src2, dst4);
	/* ���� ����
	* �� ������ ���� ������ ������� �ȼ� �� ���̰� ū ������ �ε巯���� ��Ÿ���� �ʹٸ� ���� ������ ����
	* ���� ������ ���� ���� ����� ������ ���ϴ� �����̸�, ���� �������� ���� ��� ������ ������(difference image)�̶� �Ѵ�
	void absdiff(InputArray src1, InputArray src2, OutputArray dst);
		 - src1  : ù ��° �Է� ��� �Ǵ� ��Į��
		 - src2  : �� ��° �Է� ��� �Ǵ� ��Į��
		 - dst   : ��� ���. �Է� ����� ���� ũ��, ���� ä�� ���� ����� ���� 

	*/

	// ���� ������ ����̹Ƿ� �� �Է� ������ ��ķ� �����Ͽ� ����� �������� ������ �� �ִ� 
	//  �׷��� ������ �̿��Ͽ� ����� ������ �����ϴ� ���� ���� ����. �ٸ� �� ���󿡼� ���� ��ġ�� �ִ� �ȼ� ������ ���� ���ϰų� ������ ������ ������ �� ������ 
	// �̸� ���� opencv������ multiply()�Լ��� divide() �Լ��� ����
	/*
	void multiply(InputArray src1, InputArray src2,
              OutputArray dst, double scale = 1, int dtype = -1);
		 - src1  : ù ��° �Է� ��� 
		 - src2  : �� ��° �Է� ���, src1�� ũ��� Ÿ���� ���ƾ� �Ѵ� 
		 - dst   : ��� ���. src1�� ���� ũ��, ���� Ÿ��
			dst(x, y)��saturate(scale��src1(x, y)��src2(x, y))
		 - scale : �߰������� Ȯ��/����� ����
		 - dtype : ��� ����� ����

	void divide(InputArray src1, InputArray src2, OutputArray dst,
            double scale = 1, int dtype = -1);
		 - src1  : ù ��° �Է� ���
		 - src2  : �� ��° �Է� ���, src1�� ũ��� Ÿ���� ���ƾ� �Ѵ�
		 - dst   : ��� ���. src1�� ���� ũ��, ���� Ÿ��
			dst(x, y)��saturate(scale��src1(x, y)��src2(x, y))
		 - scale : �߰������� Ȯ��/����� ����
		 - dtype : ��� ����� ����
	*/
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();

	return 0;
}