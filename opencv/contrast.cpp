#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void contrast1();
void contrast2();

// 명암 대비 (콘트라스트(contrast))
// 명암비란 영상에서 밝은 영역과 어두운 영역 사이에 드러나는 밝기 차이의 강도를 의미
// 상이 전반적으로 어둡거나 또는 전반적으로 밝은 픽셀로만 구성된 경우, 명암비가 낮다고 표현합니다.
// 반면에 밝은 영역과 어두운 영역이 골고루 섞여 있는 영상은 명암비가 높다고 말합니다.
// 일반적으로 명암비가 낮은 영상은 객체 간의 구분이 잘 되지 않아서 전반적으로 흐릿하게 느껴지고, 
// 명암비가 높은 영상은 사물의 구분이 잘 되며 선명한 느낌을 준다. 

int main(void)
{
	contrast1();
	contrast2();

	return 0;
}

// 일반적으로 명암비가 높은 사진이 잘 찍은 사진처럼 보이기 때문에 대부분의 디지털 카메라는 명암비가 높은 사진을 촬영하도록 설정
void contrast1()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// C/C++ 실수형 자료형과 Mat 객체 사이의 곱셈 연산자 재정의도 제공하며, 
	// 그 결과 Mat 행렬의 모든 원소에 주어진 실수 값을 곱한 결과 행렬을 반환
	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src); // src는 입력 영상
	imshow("dst", dst); // dst는 출력 영상
	waitKey();

	destroyAllWindows();
}

// 효과적인 명암비 조절 방법
// 명암비를 효과적으로 높이기 위해서는 밝은 픽셀은 더욱 밝게, 어두운 픽셀은 더욱 어두워지게 변경
void contrast2()
{
	Mat src = imread("images/lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 그레이스케일 범위 중간값인 128을 기준으로 명암비를 조절하는 방법을 구현
	// 입력 영상의 픽셀 값이 128보다 크면 더욱 밝게 만들고, 128보다 작으면 픽셀 값을 더 작게 만드는 방식
	// 반대로 명암비를 감소시키려면 128보다 큰 입력 영상 픽셀 값은 좀 더 작게 만들고, 128보다 작은 픽셀 값은 오히려 128에 가깝게 증가
	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;


	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}