#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 컬러 히스토그램 평활화를 수행
// 히스토그램 평활화 : 히스토그램 정보를 이용하여 명암비를 증가
// OpenCV에서는 equalizeHist() 함수를 통해 히스토그램 평활화를 수행할 수 있지만 equalizeHist() 함수는 그레이스케일 영상만 입력을 받음
// 그러므로 3채널 컬러 영상에 대해 히스토그램 평활화를 수행하려면 openCV 함수를 조합해야 한다 
int main(void)
{
	Mat src = imread("images/pepper.bmp", IMREAD_COLOR); // 채널 BGR 영상

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb); // BGR 색 공간의 src 영상을 YCrCb 색 공간으로 변경하여 src_ycrcb에 저장

	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);// src_ycrcb 영상의 채널을 분리하여 ycrcb_planes에 저장

	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]); // 	Y 성분에 해당하는 ycrcb_planes[0] 영상에 대해서만 히스토그램 평활화를 수행

	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb); // 	ycrcb_planes 벡터에 들어 있는 세 영상을 합쳐서 dst_ycrcb 영상을 생성

	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR); // 	dst_ycrcb 영상의 색 공간을 BGR 색 공간으로 변환하여 dst에 저장

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	return 0;
}