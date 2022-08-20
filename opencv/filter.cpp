#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void filter_embossing();

// 영상 처리에서 필터링(filtering)이란 영상에서 원하는 정보만 통과시키고 원치 않는 정보는 걸러 내는 작업
// 영상의 필터링은 보통 마스크(mask)라고 부르는 작은 크기의 행렬을 이용
// 마스크는 필터링의 성격을 정의하는 행렬이며 커널(kernel), 윈도우(window)라고도 부르며, 경우에 따라서는 마스크 자체를 필터
int main(void)
{
	filter_embossing();

	return 0;
}

void filter_embossing()
{
	Mat src = imread("images/rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	float data[] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
	Mat emboss(3, 3, CV_32FC1, data); // 엠보싱(embossing) 필터링

	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);
	/*
	* 
	void filter2D(InputArray src, OutputArray dst, int ddepth,
              InputArray kernel, Point anchor = Point(-1,-1),
              double delta = 0, int borderType = BORDER_DEFAULT);
			  - src : 입력 영상
			  - dst : 출력 영상. src와 같은 크기, 같은 채널 수
			  - ddepth : 결과 영상의 깊이
			  - kernel : 필터링 커널. 1채널 실수형 행렬
			  - anchor : 고정점 좌표. Point(-1, -1)을 지정하면 커널 중심을 고정점으로 사용
			  - delta  : 필터링 연산 후 추가적으로 더할 값
			  - borderType : 가장자리 픽셀 확장 방식
	*/

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}