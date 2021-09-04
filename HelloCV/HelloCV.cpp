#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	cout << "Hello OpenCV " << CV_VERSION << endl;

	Mat img;
	img = imread("lenna.bmp");

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("image");
	imshow("image", img);

	waitKey();

	return 0;
}

// opencv setting
// 1. �ý��� ȯ�� ���� ����
//  - OPENCV_DIR
//  - paht (opencv/build/x64/vc15/bin)

// 2. Visual Studio ������Ʈ setting (������Ʈ - �Ӽ�)
// 2.1 Debug (x64)
// - C/C++ 
//  -->> �Ϲ� - �߰� ���� ���͸� - path (opencv/build/include)
// - ��Ŀ 
//  -->> �Ϲ� - �߰� ���̺귯�� ���͸� - path (opencv/build/x64/vc15/lib)
//  -->> �Է� - �߰� ���Ӽ� - opencv_world453d.lib (�̶�, 453�� opencv_version)
// 2.2 Release
// - C/C++ 
//  -->> �Ϲ� - �߰� ���� ���͸� - Debug�� ����
// - ��Ŀ 
//  -->> �Ϲ� - �߰� ���̺귯�� ���͸� -  Debug�� ����
//  -->> �Է� - �߰� ���Ӽ� - opencv_world453.lib (����, 453d => 453)