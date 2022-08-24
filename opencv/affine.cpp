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

// 어파인 변환은 영상의 평행 이동, 확대 및 축소, 회전 등의 조합으로 만들 수 있는 기하학적 변환
int main(void)
{
	// 어파인 변환은 모두 여섯 개의 파라미터를 이용한 수식으로 정의
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
	* 어파인 변환 행렬을 구하는 함수 이름은 getAffineTransform()
	Mat getAffineTransform(const Point2f src[], const Point2f dst[]);
	Mat getAffineTransform(InputArray src, InputArray dst);
		- src : 입력 영상에서 세 점의 좌표
		- dst : 결과 영상에서 세 점의 좌표
		- 반환값 : 2×3 어파인 변환 행렬. CV_64FC1
	*/

	Mat dst;
	warpAffine(src, dst, M, Size());
	/* 
	* 2×3 어파인 변환 행렬을 가지고 있을 때, 영상을 어파인 변환한 결과 영상을 생성하려면 warpAffine() 함수를 사용
	void warpAffine(InputArray src, OutputArray dst,
                InputArray M, Size dsize,
                int flags = INTER_LINEAR,
                int borderMode = BORDER_CONSTANT,
                const Scalar& borderValue = Scalar());
				- src : 입력 영상
				- dst : 결과 영상. src와 같은 타입이고, 크기는 dsize에 의해 결정됩니다.
				- M : 2×3 어파인 변환 행렬
				- dsize : 결과 영상 크기
				- flags : 보간법 알고리즘. 만약 OR 연산자를 이용하여 WARP_INVERSE_MAP 플래그를 함께 지정하면 역방향으로 변환을 수행합니다.
				- borderMode : 가장자리 픽셀 확장 방식. BorderTypes 열거형 상수 중 하나를 지정합니다. 
							만약 BORDER_TRANSPARENT를 지정하면 입력 영상의 픽셀 값이 복사되지 않는 영역은 dst 픽셀 값을 그대로 유지합니다.
				- borderValue : borderMode가 BORDER_CONSTANT일 때 사용할 상수 값. 기본값으로 검은색이 지정되어 있습니다.
	*/

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

// 영상의 이동 변환(translation transformation)은 영상을 가로 또는 세로 방향으로 일정 크기만큼 이동시키는 연산을 의미하며 시프트(shift) 연산이라고도 한다 
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

// 전단 변환(shear transformation)은 직사각형 형태의 영상을 한쪽 방향으로 밀어서 평행사변형 모양으로 변형되는 변환이며 층밀림 변환이라고도 한다
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

// 영상의 크기 변환(scale transformation)은 영상의 전체적인 크기를 확대 또는 축소하는 변환
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
	* 크기를 변경할 수 있는 resize() 함수
	void resize(InputArray src, OutputArray dst,
				Size dsize, double fx = 0, double fy = 0,
				int interpolation = INTER_LINEAR);
				- src : 입력 영상
				- dst : 결과 영상
				- dsize : 결과 영상 크기
				- fx : x축 방향으로의 크기 변환 비율. dsize에 Size()를 지정한 경우에 사용
				- fy : y축 방향으로의 크기 변환 비율. dsize에 Size()를 지정한 경우에 사용
				- interpolation : 보간법 지정. INTER_NEAREST, INTER_LINEAR, INTER_CUBIC, INTER_AREA, INTER_LANCZOS4 중 하나를 지정
						- INTER_NEAREST  : 최근방 이웃 보간법
						- INTER_LINEAR   : 양선형 보간법
						- INTER_CUBIC    : 3차 보간법
						- INTER_AREA     : 픽셀 영역 리샘플링
						- INTER_LANCZOS4 : 8×8 이웃 픽셀을 사용하는 란초스(Lanczos) 보간법
	*/

	imshow("src", src);
	imshow("dst1", dst1(Rect(400, 500, 400, 400)));
	imshow("dst2", dst2(Rect(400, 500, 400, 400)));
	imshow("dst3", dst3(Rect(400, 500, 400, 400)));
	imshow("dst4", dst4(Rect(400, 500, 400, 400)));

	waitKey();
	destroyAllWindows();
}

// 영상의 회전 변환(rotation transformation)은 특정 좌표를 기준으로 영상을 원하는 각도만큼 회전하는 변환
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
	*  영상의 회전을 위한 어파인 변환 행렬을 생성하는 getRotationMatrix2D() 함수를 제공
	Mat getRotationMatrix2D(Point2f center, double angle, double scale);
		- center : 회전 중심 좌표
		- angle  : 회전 각도. 양수는 반시계 방향, 음수는 시계 방향을 의미합니다.
		- scale  : 회전 후 추가적으로 확대 또는 축소할 비율. 크기 변환은 수행하지 않으려면 1을 지정합니다.
		- 반환값 : 2×3 어파인 변환 행렬(CV_64F)
	*/

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

// 영상의 기하학적 변환 중에 영상의 좌우를 서로 바꾸거나, 또는 상하를 뒤집는 형태의 변환
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
		* flip() 함수는 영상을 가로 방향, 세로 방향, 또는 가로와 세로 양 방향에 대해 대칭 변환한 영상을 생성
		void flip(InputArray src, OutputArray dst, int flipCode);
			- src : 입력 영상
			- dst : 결과 영상. src와 같은 크기, 타입
			- flipCode : 대칭 방법 지정 플래그. flipCode가 양수이면 좌우 대칭, 0이면 상하 대칭, 음수이면 상하 대칭과 좌우 대칭을 모두 수행
		*/

		String desc = format("flipCode: %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}