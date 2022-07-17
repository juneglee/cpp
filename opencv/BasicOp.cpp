#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void PointOp();
void SizeOp();
void RectOp();
void RotatedRectOp();
void RangeOp();
void StringOp();

int main()
{
	PointOp();
	SizeOp();
	RectOp();
	RotatedRectOp();
	RangeOp();
	StringOp();

	return 0;
}

void PointOp()
{
	/*
	point 클래스
	: point 클래스는 2차원 평면 위에 있는 점의 좌표를 표현하는 템플랫 클래스이다. 
	point 클래스는 2차원 좌표를 x와 y라는 이름의 멤버 변수를 가지고 있다. 
	*/
	Point pt1;				// pt1 = (0, 0)
	pt1.x = 5; pt1.y = 10;	// pt1 = (5, 10)
	Point pt2(10, 30);		// pt2 = (10, 30)

	Point pt3 = pt1 + pt2;	// pt3 = [15, 40]
	Point pt4 = pt1 * 2;	// pt4 = [10, 20]
	int d1 = pt1.dot(pt2);	// d1 = 350
	bool b1 = (pt1 == pt2);	// b1 = false

	cout << "pt1: " << pt1 << endl;
	cout << "pt2: " << pt2 << endl;
	cout << "pt3: " << pt3 << endl;
	cout << "pt4: " << pt4 << endl;
}

void SizeOp()
{
	/*
	영상 또는 사각형 영역의 크기를 표현할 때에는 Size 클래스를 사용 
	Size 클래스는 사각형 영역의 가로와 세로 크기를 나타내는 width와 height 변수를 가지고 있다
	*/
	Size sz1, sz2(10, 20);			// sz1 = [0 x 0], sz2 = [10 x 20]
	sz1.width = 5; sz1.height = 10;	// sz1 = [5 x 10]

	Size sz3 = sz1 + sz2;	// sz3 = [15 x 30]
	Size sz4 = sz1 * 2;		// sz4 = [10 x 20]
	int area1 = sz4.area();	// area1 = 200

	cout << "sz3: " << sz3 << endl;
	cout << "sz4: " << sz4 << endl;
}

void RectOp()
{
	/*
	Rect 
	:OpenCV 에서 가각형의 위치와 크기 정보를 표현할 때 Rect(Recatangle)을 사용
	Rect 클래스는 사격형의 좌측 상단 점의 좌표를 나타내는 x, y 멤버 변수와 가격형의 가로 및 세로를 나타내는 width, height 멤버 변수를 가지고 있다.
	*/
	Rect rc1;					// rc1 = [0 x 0 from (0, 0)]
	Rect rc2(10, 10, 60, 40);	// rc2 = [60 x 40 from (10, 10)]

	Rect rc3 = rc1 + Size(50, 40);	// rc3 = [50 x 40 from (0, 0)]
	Rect rc4 = rc2 + Point(10, 10);	// rc4 = [60 x 40 from (20, 20)]

	Rect rc5 = rc3 & rc4;		// rc5 = [30 x 20 from (10, 10)]
	Rect rc6 = rc3 | rc4;		// rc6 = [80 x 60 from (0, 0)]

	cout << "rc5: " << rc5 << endl;
	cout << "rc6: " << rc6 << endl;
}

void RotatedRectOp()
{
	/*
	RotatedRect 
	RotatedRect 클래스는 회전된 사각형을 표현하는 클래스입니다. 
	RotatedRect 클래스는 회전된 사각형의 중심 좌표를 나타내는 center, 
	사각형의 가로 및 세로 크기를 나타내는 size, 
	회전 각도 정보를 나타내는 angle을 멤버 변수로 가집니다
	*/
	RotatedRect rr1(Point2f(40, 30), Size2f(40, 20), 30.f);

	Point2f pts[4];
	rr1.points(pts);

	Rect br = rr1.boundingRect();
}

void RangeOp()
{
	/*
	Range 클래스
	Range 클래스는 범위 또는 구간을 표현하는 클래스
	Range 클래스는 범위의 시작과 끝을 나타내는 start와 end 멤버 변수를 가지고 있다.
	*/
	// Range(int _start, int _end);
	Range r1(0, 10);
	cout << "r1: " << r1 << endl;
}

void StringOp()
{
	/*
	String 클래스
	:OpenCV에서는 영상 출력 창에 고유의 문자열을 지정하여 구분하고, 영상에 문자열을 출력하는 기능도 제공
	OpenCV 4.0 버전부터 std::string 클래스와 String 클래스는 완전히 같은 클래스입니다. 
	다만 코드 호환성을 위하여 여전히 OpenCV 코드에서는 std::string 대신 String 클래스 이름을 사용
	*/
	String str1 = "Hello";
	String str2 = "world";
	String str3 = str1 + " " + str2;	// str3 = "Hello world"

	bool ret = (str2 == "WORLD");

	Mat imgs[3];
	for (int i = 0; i < 3; i++) {
		String filename = format("data%02d.bmp", i + 1);
		cout << filename << endl;
		imgs[i] = imread(filename);
	}
}