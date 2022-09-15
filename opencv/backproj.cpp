#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 히스토그램 역투영 
// 기준 영상으로부터 찾고자 하는 객체의 컬러 히스토그램을 미리 구하고, 주어진 입력 영상에서 해당 히스토그램에 부합하는 영역을 찾아내는 방식
// 이처럼 주어진 히스토그램 모델과 일치하는 픽셀을 찾아내는 기법을 히스토그램 역투영(histogram backprojection)이라고 한다
// 예를 들어 피부색에 대한 색상 히스토그램을 가지고 있다면 역투영 방법을 사용하여 영상에서 피부색 영역을 검출할 수 있다
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
	/* 히스토그램 역투영은 calcBackProject() 함수를 이용하여 수행
	void calcBackProject(const Mat* images, int nimages,
		 const int* channels, InputArray hist,
		 OutputArray backProject, const float** ranges,
		 double scale = 1, bool uniform = true);
		 - images : 입력 영상의 배열 또는 입력 영상의 주소. 영상의 배열인 경우, 모든 영상의 크기와 깊이는 같아야 한다 
		 - nimages : 입력 영상 개수
		 - channels : 역투영 계산 시 사용할 채널 번호 배열
		 - hist : 입력 히스토그램
		 - backProject : 출력 히스토그램 역투영 영상. 입력 영상과 같은 크기, 같은 깊이를 갖는 1채널 행렬
		 - ranges : 각 차원의 히스토그램 빈 범위를 나타내는 배열의 배열
		 - scale : 히스토그램 역투영 값에 추가적으로 곱할 값
		 - uniform : 히스토그램 빈의 간격이 균등한지를 나타내는 플래그
	*/

	imshow("src", src);
	imshow("backproj", backproj);
	waitKey();

	return 0;
}