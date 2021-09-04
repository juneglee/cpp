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
// 1. 시스템 환경 변수 편집
//  - OPENCV_DIR
//  - paht (opencv/build/x64/vc15/bin)

// 2. Visual Studio 프로젝트 setting (프로젝트 - 속성)
// 2.1 Debug (x64)
// - C/C++ 
//  -->> 일반 - 추가 포함 디렉터리 - path (opencv/build/include)
// - 링커 
//  -->> 일반 - 추가 라이브러리 디렉터리 - path (opencv/build/x64/vc15/lib)
//  -->> 입력 - 추가 종속성 - opencv_world453d.lib (이때, 453은 opencv_version)
// 2.2 Release
// - C/C++ 
//  -->> 일반 - 추가 포함 디렉터리 - Debug와 동일
// - 링커 
//  -->> 일반 - 추가 라이브러리 디렉터리 -  Debug와 동일
//  -->> 입력 - 추가 종속성 - opencv_world453.lib (주의, 453d => 453)