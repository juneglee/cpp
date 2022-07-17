#include "opencv2/opencv.hpp"
#include <iostream>


/*
Mat 클래스 
opencv 에서 가장 많이 사용하는 클래스는 행렬을 표현하는 Mat클래스 이다 
Mat 클래스는 일반적인 2차원 행렬뿐만 아니라 고차원 행렬을 표현할 수 있으며, 한 개이상의 채널(channel)을 가질 수 있다 
Mat 클래스에서는 정수, 실수, 복소수 등으로 구성된 행렬 또는 벡터(vector)를 저장할 수 있고, 크레이스 케일 또는 컬러 영상을 저장할 수 있다 
경우에 따라서는 벡터 필드(vector field), 포인트 클라우드(point cloud), 텐서(tensor), 히스토그램(histogram) 등 정보를 저장하는 용도로 사용
(그러나 실제적으로는 2차원 영상 데이터를 저장하고 처리하는 용도로 가장 많이 사용)
*/
using namespace cv;
using namespace std;

void MatOp1();
void MatOp2();
void MatOp3();
void MatOp4();
void MatOp5();
void MatOp6();
void MatOp7();

int main()
{
	MatOp1();
	MatOp2();
	MatOp3();
	MatOp4();
	MatOp5();
	MatOp6();
	MatOp7();

	return 0;
}

void MatOp1()
{
	/*
	Mat::Mat(int rows, int cols, int type);
		row 새로 만들 행렬의 행 개수(영상의 세로 크기)
		cols 새로 만들 행렬의 열 개수(영상의 가로 크기)
		type 새로 만들 행렬의 타입
	*/
	Mat img1; 	// empty matrix

	Mat img2(480, 640, CV_8UC1);		// unsigned char, 1-channel
	Mat img3(480, 640, CV_8UC3);		// unsigned char, 3-channels
	Mat img4(Size(640, 480), CV_8UC3);	// Size(width, height)

	Mat img5(480, 640, CV_8UC1, Scalar(128));		// initial values, 128
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));	// initial values, red

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1);	// 0's matrix
	Mat mat2 = Mat::ones(3, 3, CV_32FC1);	// 1's matrix
	Mat mat3 = Mat::eye(3, 3, CV_32FC1);	// identity matrix

	float data[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat4(2, 3, CV_32FC1, data);

	Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	Mat mat6 = Mat_<uchar>({ 2, 3 }, { 1, 2, 3, 4, 5, 6 });

	mat4.create(256, 256, CV_8UC3);	// uchar, 3-channels
	mat5.create(4, 4, CV_32FC1);	// float, 1-channel

	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f);
}

void MatOp2()
{
	Mat img1 = imread("images/dog.bmp");

	Mat img2 = img1;
	Mat img3;
	img3 = img1;

	Mat img4 = img1.clone();
	Mat img5;
	img1.copyTo(img5);

	img1.setTo(Scalar(0, 255, 255));	// yellow

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);

	waitKey();
	destroyAllWindows();
}

void MatOp3()
{
	Mat img1 = imread("images/cat.bmp");

	if (img1.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat img2 = img1(Rect(220, 120, 340, 240));
	Mat img3 = img1(Rect(220, 120, 340, 240)).clone();

	img2 = ~img2;

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);

	waitKey();
	destroyAllWindows();
}

void MatOp4()
{
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);

	for (int j = 0; j < mat1.rows; j++) {
		for (int i = 0; i < mat1.cols; i++) {
			mat1.at<uchar>(j, i)++;
		}
	}

	for (int j = 0; j < mat1.rows; j++) {
		uchar* p = mat1.ptr<uchar>(j);
		for (int i = 0; i < mat1.cols; i++) {
			p[i]++;
		}
	}

	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it) {
		(*it)++;
	}

	cout << "mat1:\n" << mat1 << endl;
	/*
	mat1:
	[  3,   3,   3,   3;
	   3,   3,   3,   3;
	   3,   3,   3,   3]
	*/
}

void MatOp5()
{
	Mat img1 = imread("images/lena.bmp");

	cout << "Width: " << img1.cols << endl;
	cout << "Height: " << img1.rows << endl;
	cout << "Channels: " << img1.channels() << endl;
	/*
	Width: 512
	Height: 512
	Channels: 3
	*/

	if (img1.type() == CV_8UC1)
		cout << "img1 is a grayscale image." << endl;
	else if (img1.type() == CV_8UC3)
		cout << "img1 is a truecolor image." << endl;
	// img1 is a truecolor image.

	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;
	/*
	mat1:
	[2, 1.414;
	 3, 1.732]
	*/
}

void MatOp6()
{
	float data[] = { 1, 1, 2, 3 };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;

	Mat mat2 = mat1.inv();
	cout << "mat2:\n" << mat2 << endl;

	cout << "mat1.t():\n" << mat1.t() << endl;
	cout << "mat1 + 3:\n" << mat1 + 3 << endl;
	cout << "mat1 + mat2:\n" << mat1 + mat2 << endl;
	cout << "mat1 * mat2:\n" << mat1 * mat2 << endl;
	/*
	mat1:
	[1, 1;
	 2, 3]
	mat2:
	[3, -1;
	 -2, 1]
	mat1.t():
	[1, 2;
	 1, 3]
	mat1 + 3:
	[4, 4;
	 5, 6]
	mat1 + mat2:
	[4, 0;
	 0, 4]
	mat1 * mat2:
	[1, 0;
	 0, 1]
	*/
}

void MatOp7()
{
	Mat img1 = imread("images/lena.bmp", IMREAD_GRAYSCALE);

	Mat img1f;
	img1.convertTo(img1f, CV_32FC1);

	uchar data1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	Mat mat1(3, 4, CV_8UC1, data1);
	Mat mat2 = mat1.reshape(0, 1);

	cout << "mat1:\n" << mat1 << endl;
	cout << "mat2:\n" << mat2 << endl;

	mat1.resize(5, 100);
	cout << "mat1:\n" << mat1 << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3);
	cout << "mat1:\n" << mat1 << endl;
	/*
	mat1:
	[  1,   2,   3,   4;
	   5,   6,   7,   8;
	   9,  10,  11,  12]
	mat2:
	[  1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12]
	mat1:
	[  1,   2,   3,   4;
	   5,   6,   7,   8;
	   9,  10,  11,  12;
	 100, 100, 100, 100;
	 100, 100, 100, 100]
	mat1:
	[  1,   2,   3,   4;
	   5,   6,   7,   8;
	   9,  10,  11,  12;
	 100, 100, 100, 100;
	 100, 100, 100, 100;
	 255, 255, 255, 255]
	*/
}