#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void drawLines();
void drawPolys();
void drawText1();
void drawText2();

// opencv drawing
int main(void)
{
	drawLines();
	drawPolys();
	drawText1();
	drawText2();

	return 0;
}

// 직선 그리기
void drawLines()
{
	/*
	* void line(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
	- img        : 입출력 영상
	- pt1        : 시작점
	- pt2        : 끝점
	- color      : 선 색상 (또는 밝기)
	- thickness  : 선 두께
	- lineType   : 선 타입. LINE_4, LINE_8, LINE_AA 중 하나를 지정합니다.
	- shift      : 그리기 좌표 값의 축소 비율(오른쪽 비트 시프트(>>) 연산)
	*/
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));
	line(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);
	line(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);

	/*
	* lineTypes 열거형 상수 
		FILLED / -1 / 내부를 채움(직선 그리기 함수에는 사용 불가)
		LINE_4 / 4 / 4방향 연결
		LINE_8 / 8 / 8방향 연결
		LINE_AA / 18 / 안티에일리어싱(anti-aliasing)
	*/
	line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);
	line(img, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);
	line(img, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);

	//  화살표 형태의 직선을 그려야 하는 경우에는 arrowedLine() 함수를 이용
	/*
	* void arrowedLine(InputOutputArray img, Point pt1, Point pt2, const Scalar& color,
                 int thickness=1, int line_type=8, int shift=0, double tipLength=0.1);
	- line 동일 (img, pt1, pt2, color, thickness, linetype, shift)
	- tipLength  : 전체 직선 길이에 대한 화살표 길이의 비율
	*/
	arrowedLine(img, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);
	arrowedLine(img, Point(50, 250), Point(350, 250), Scalar(255, 0, 255), 1);
	arrowedLine(img, Point(50, 300), Point(350, 300), Scalar(255, 0, 0), 1, LINE_8, 0, 0.05);

	// drawMarker() 함수는 직선 그리기 함수를 이용하여 다양한 모양의 마커(marker)를 그림
	/* 
	* void drawMarker(InputOutputArray img, Point position, const Scalar& color,
					int markerType = MARKER_CROSS, int markerSize=20, int thickness=1,
					int line_type=8);
	- line 동일 (img, pt1, pt2, color, thickness, linetype, shift)
		MARKER_CROSS         : 십자가 모양(+ 모양) 
		MARKER_TILTED_CROSS  : 45도 회전된 십자가 모양(× 모양)
		MARKER_STAR          : MARKER_CROSS 모양과 MARKER_TILTED_CROSS 모양이 합쳐진 형태( 모양)
		MARKER_DIAMOND       : 마름모 모양(◇ 모양)
		MARKER_SQUARE        : 정사각형 모양(□ 모양)
		MARKER_TRIANGLE_UP   : 위로 뾰족한 삼각형(△ 모양) 
		MARKER_TRIANGLE_DOWN : 아래로 뾰족한 삼각형(▽ 모양)
	*/
	drawMarker(img, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS);
	drawMarker(img, Point(100, 350), Scalar(0, 0, 255), MARKER_TILTED_CROSS);
	drawMarker(img, Point(150, 350), Scalar(0, 0, 255), MARKER_STAR);
	drawMarker(img, Point(200, 350), Scalar(0, 0, 255), MARKER_DIAMOND);
	drawMarker(img, Point(250, 350), Scalar(0, 0, 255), MARKER_SQUARE);
	drawMarker(img, Point(300, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_UP);
	drawMarker(img, Point(350, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_DOWN);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

// 도형 그리기 
void drawPolys()
{

	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));
	/*
	* 두가지 방법
	* void rectangle(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
	* void rectangle(InputOutputArray img, Rect rec, const Scalar& color,int thickness = 1, int lineType = LINE_8, int shift = 0);
			- img        : 입출력 영상
			- pt1        : 사각형 꼭지점 좌표, point 갹체
			- pt2        : pt1과 대각 방향에 있는 사각형 꼭지점 좌표. Point 객체
			- rec        : 사각형 위치 정보. Rect 객체
			- color      : 사각형 색상 (또는 밝기)
			- thickness  : 사각형 외곽선 두께. 이 값이 음수(-1 또는 FILLED)이면 내부를 채움
			- lineType   : 선 타입
			- shift      : 그리기 좌표 값의 축소 비율(오른쪽 비트 시프트(>>) 연산)
	*/
	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2);
	rectangle(img, Rect(50, 150, 100, 50), Scalar(0, 0, 128), -1);
	/* 
	* void circle(InputOutputArray img, Point center, int radius,  const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
			- img        : 입출력 영상
			- center     : 원의 중심
			- radius     : 원의 반지름
			- color      : 원 색상
			- thickness  : 원 외곽선 두께. 이 값이 음수(-1 또는 FILLED)이면 내부를 채움
			- lineType   : 선 타입
			- shift      : 그리기 좌표 값의 축소 비율(오른쪽 비트 시프트(>>) 연산)
	*/
	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA);
	circle(img, Point(300, 120), 60, Scalar(255, 0, 0), 3, LINE_AA);

	/* 
	* void ellipse(InputOutputArray img, Point center, Size axes,  double angle, double startAngle, double endAngle, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
			- img        : 입출력 영상
			- center     : 타원의  중심
			- axes       : 타원의  반지름, Size(x축_반지름, y축_반지름)
			- angle      : 타원 회전 각도(x축 기준, 시계 방향)
			- startAngle : 타원 호의 시작 각도(x축 기준, 시계 방향)
			- endAngle   : 타원 호의 끝 각도(x축 기준, 시계 방향)
			- color      : 타원  색상
			- thickness  : 타원  외곽선 두께. 이 값이 음수(-1 또는 FILLED)이면 내부를 채움
			- lineType   : 선 타입
			- shift      : 그리기 좌표 값의 축소 비율(오른쪽 비트 시프트(>>) 연산)
	*/
	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), FILLED, LINE_AA);
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);

	vector<Point> pts;
	pts.push_back(Point(250, 250)); pts.push_back(Point(300, 250));
	pts.push_back(Point(300, 300)); pts.push_back(Point(350, 300));
	pts.push_back(Point(350, 350)); pts.push_back(Point(250, 350));
	/* 
	* void polylines(InputOutputArray img, InputArrayOfArrays pts,  bool isClosed, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
			- img        : 입출력 영상
			- pts        : 다각형 외곽 점들의 좌표 배열. 주로 vector<Point> 타입
			- angle      : 타원 회전 각도(x축 기준, 시계 방향)
			- isClosed   : 다각형이 닫혀 있는지를 나타내는 플래그. 이 값이 true이면 다각형의 마지막 꼭지점과 첫 번째 꼭지점을 잇는 직선을 추가로 그림
			- color      : 선 색상
			- thickness  : 선 두께. 이 값이 음수(-1 또는 FILLED)이면 내부를 채움
			- lineType   : 선 타입
			- shift      : 그리기 좌표 값의 축소 비율(오른쪽 비트 시프트(>>) 연산)
	*/
	polylines(img, pts, true, Scalar(255, 0, 255), 2);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

// 문자열 출력
void drawText1()
{
	Mat img(500, 800, CV_8UC3, Scalar(255, 255, 255));
	/*
	* void putText(InputOutputArray img, const String& text, Point org, int fontFace, double fontScale, Scalar color,
             int thickness = 1, int lineType = LINE_8,bool bottomLeftOrigin = false);
			- img              : 입출력 영상
			- text             : 출력할 문자열
			- org              : 영상에서 문자열을 출력할 위치의 좌측 하단 좌표
			- fontFace         : 폰트 종류. cv::HersheyFonts에서 선택
			- fontScale        : 폰트 크기 확대/축소 비율
			- color            : 문자열 색상
			- thickness        : 문자열을 그릴 때 사용할 선 두께
			- lineType         : 선 타입. LINE_4, LINE_8, LINE_AA 중 하나를 지정
			- bottomLeftOrigin : 이 값이 true이면 영상의 좌측 하단을 원점으로 간주합니다. false이면 좌측 상단이 원점
	*/
	putText(img, "FONT_HERSHEY_SIMPLEX", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_PLAIN", Point(20, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_DUPLEX", Point(20, 150), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX", Point(20, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_TRIPLEX", Point(20, 250), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_COMPLEX_SMALL", Point(20, 300), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_SCRIPT_SIMPLEX", Point(20, 350), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(255, 0, 255));
	putText(img, "FONT_HERSHEY_SCRIPT_COMPLEX", Point(20, 400), FONT_HERSHEY_SCRIPT_COMPLEX, 1, Scalar(255, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX | FONT_ITALIC", Point(20, 450), FONT_HERSHEY_COMPLEX | FONT_ITALIC, 1, Scalar(255, 0, 0));
	/* 
	* HersheyFonts 열거형 상수
		FONT_HERSHEY_SIMPLEX        : 일반 크기의 산세리프 폰트
		FONT_HERSHEY_PLAIN          : 작은 크기의 산세리프 폰트
		FONT_HERSHEY_DUPLEX         : 일반 크기의 산세리프 폰트(FONT_HERSHEY_SIMPLEX보다 복잡한 형태)
		FONT_HERSHEY_COMPLEX        : 일반 크기의 세리프 폰트
		FONT_HERSHEY_TRIPLEX        : 일반 크기의 세리프 폰트(FONT_HERSHEY_COMPLEX보다 복잡한 형태)
		FONT_HERSHEY_COMPLEX_SMALL  : FONT_HERSHEY_COMPLEX보다 작은 폰트
		FONT_HERSHEY_SCRIPT_SIMPLEX : 필기체 스타일의 폰트
		FONT_HERSHEY_SCRIPT_COMPLEX : 필기체 스타일의 폰트(FONT_HERSHEY_SCRIPT_SIMPLEX보다 복잡한 형태)
		FONT_ITALIC                 : 이탤릭체를 위한 플래그
	
	*/
	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

void drawText2()
{
	Mat img(200, 640, CV_8UC3, Scalar(255, 255, 255));

	const String text = "Hello, OpenCV";
	int fontFace = FONT_HERSHEY_TRIPLEX;
	double fontScale = 2.0;
	int thickness = 1;

	// 문자열 출력을 위한 필요한 사각형 영역 크기를 가늠할 수 있는 getTextSize() 함수도 제공. 
	// 이 함수를 잘 이용하면 문자열이 한쪽으로 치우치지 않고 적당한 위치에 출력되도록 설정할 수 있다 
	/*
	Size getTextSize(const String& text, int fontFace, double fontScale, int thickness, int* baseLine);
			- text       : 출력할 문자열
			- fontFace   : 폰트 종류
			- fontScale  : 폰트 크기 확대/축소 비율
			- thickness  : 문자열을 그릴 때 사용할 선 두께
			- baseLine   : (출력) 가장 하단의 텍스트 위치를 기준으로 하는 기준선(baseline)의 y 좌표, 필요 없으면 0 지정
			- 반환값     : 지정한 문자열 출력 시 차지하는 사각형 크기
	*/
	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0);
	Size sizeImg = img.size();

	Point org((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2);
	putText(img, text, org, fontFace, fontScale, Scalar(255, 0, 0), thickness);
	rectangle(img, org, org + Point(sizeText.width, -sizeText.height), Scalar(0, 255, 0), 1);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}
// 주의 : OpenCV의 그리기 함수는 영상의 픽셀 값을 변경시켜 그림을 그린다. 그러므로 일반 영상 위에 그리기 함수 직선, 도형, 문자열을 출력하면 우너본 영상의 픽셀 값을 복구 할 수 없게 된다.
//        만약 영상에 그리기를 수행한 후에 다시 원본 영상을 사용할 필요가 있다면 미리 원본을 복사해 두고 사용해야 한다.
//        이때, 대입 연산자 혹은 Mat 클래스 복사 생성자를 사용하여 복사하는 것이 아니라  아니라 Mat::clone() 또는 Mat::copyTo() 함수를 사용해야 한다