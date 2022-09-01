#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void hough_lines();
void hough_line_segments();
void hough_circles();

int main(void)
{
	hough_lines();
	hough_line_segments();
	hough_circles();

	return 0;
}

// 영상에서 직선을 찾기 위한 용도로 허프 변환(hough transform) 기법
void hough_lines()
{
	Mat src = imread("images/building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);
	/*
	* HoughLines() 함수를 사용하여 허프 변환 직선 검출을 수행
	void HoughLines(InputArray image, OutputArray lines,
                double rho, double theta, int threshold,
                double srn = 0, double stn = 0,
                double min_theta = 0, double max_theta = CV_PI);
				- image : 8비트 단일 채널 입력 영상. 주로 에지 영상을 지정
				- lines : 직선 정보(rho, theta)를 저장할 출력 벡터
				- rho : 축적 배열에서 ρ 값의 해상도(픽셀 단위)
				- theta : 축적 배열에서 θ 값의 해상도(라디안 단위)
				- threshold : 축적 배열에서 직선으로 판단할 임계값
				- srn : 멀티스케일 허프 변환에서 rho 해상도를 나누는 값. 
						srn에 양의 실수를 지정하면 rho 해상도와 rho/srn 해상도를 각각 이용하여 멀티스케일 허프 변환을 수행
						srn과 stn이 모두 0이면 일반 허프 변환을 수행
				- stn : 멀티스케일 허프 변환에서 theta 해상도를 나누는 값
				- min_theta : 검출할 직선의 최소 theta 값
				- max_theta : 검출할 직선의 최대 theta 값
	*/

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		float cos_t = cos(theta), sin_t = sin(theta);
		float x0 = rho * cos_t, y0 = rho * sin_t;
		float alpha = 1000;

		Point pt1(cvRound(x0 - alpha * sin_t), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 + alpha * sin_t), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

// 기본적인 허프 변환 직선 검출 방법 외에 확률적 허프 변환(probabilistic Hough transform)에 의한 직선 검출 방법도 제공
void hough_line_segments()
{
	Mat src = imread("images/building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);
	/* 
	* 확률적 허프 변환 방법은 HoughLinesP()
	* 확률적 허프 변환 방법은 직선의 방정식 파라미터 ρ와 θ를 반환하는 것이 아니라 직선의 시작점과 끝점 좌표를 반환
	void HoughLinesP(InputArray image, OutputArray lines,
					 double rho, double theta, int threshold,
					 double minLineLength = 0, double maxLineGap = 0);
					 - image : 8비트 단일 채널 입력 영상. 주로 에지 영상을 지정
					 - lines : 선분의 시작점과 끝점의 정보(x1, y1, x2, y2)를 저장할 출력 벡터
					 - rho : 축적 배열에서 ρ 값의 해상도(픽셀 단위)
					 - theta : 축적 배열에서 θ 값의 해상도(라디안 단위)
					 - threshold : 축적 배열에서 직선으로 판단할 임계값
					 - minLineLength : 검출할 선분의 최소 길이
					 - maxLineGap : 직선으로 간주할 최대 에지 점 간격
	*/

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (Vec4i l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

// 일반적인 허프 변환 대신 허프 그래디언트 방법(Hough gradient method)을 사용하여 원을 검출
void hough_circles()
{
	Mat src = imread("images/coins.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat blurred;
	blur(src, blurred, Size(3, 3));

	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);
	/*
	* HoughCircles() 함수를 사용하여 원을 검출
	void HoughCircles(InputArray image, OutputArray circles,
					  int method, double dp, double minDist,
					  double param1 = 100, double param2 = 100,
					  int minRadius = 0, int maxRadius = 0);
					  - image : 입력 영상. 에지 영상이 아닌 원본 그레이스케일 영상을 지정
					  - circles : 검출된 원 정보를 저장할 출력 벡터
					  - method : HOUGH_GRADIENT만 지정 가능
					  - dp : 입력 영상과 축적 배열의 크기 비율
					  - minDist : 인접한 원 중심의 최소 거리
					  - param1 : Canny 에지 검출기의 높은 임계값
					  - param2 : 축적 배열에서 원 검출을 위한 임계값
					  - minRadius : 검출할 원의 최소 반지름
					  - maxRadius : 검출할 원의 최대 반지름
	*/

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles) {
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}