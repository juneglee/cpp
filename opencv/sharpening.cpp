#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void unsharp_mask();

// 샤프닝(sharpening)이란 영상을 날카로운 느낌이 나도록 변경하는 필터링 기법
// 날카로운 느낌의 영상이란 초점이 잘 맞은 사진처럼 객체의 윤곽이 뚜렷하게 구분되는 영상을 의미
// 이미 촬영된 사진을 초점이 잘 맞은 사진처럼 보이게끔 변경하려면 영상 에지 근방에서 픽셀 값의 명암비가 커지도록 수정해야 한다
int main(void)
{
	unsharp_mask();

	return 0;
}

// 샤프닝 기법과 관련해서 흥미로운 사실은 샤프닝을 구현하기 위해 블러링된 영상을 사용한다
//  블러링이 적용되어 부드러워진 영상을 활용하여 반대로 날카로운 영상을 생성
// 블러링이 적용된 영상, 즉 날카롭지 않은 영상을 언샤프(unsharp)하다고 말하기도 한다

void unsharp_mask()
{
	Mat src = imread("images/rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);

	// 	가우시안 필터의 표준 편차 sigma 값을 1부터 5까지 증가시키면서 언샤프 마스크 필터링을 수행
	for (int sigma = 1; sigma <= 5; sigma++) {
		Mat blurred;
		// 	가우시안 필터를 이용한 블러링 영상을 blurred에 저장
		GaussianBlur(src, blurred, Size(), sigma); 

		// 언샤프 마스크 필터링을 수행
		float alpha = 1.f;
		Mat dst = (1 + alpha) * src - alpha * blurred;

		// 	샤프닝 결과 영상 dst에 사용된 sigma 값을 출력
		String desc = format("sigma: %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}