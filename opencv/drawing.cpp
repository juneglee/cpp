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

// ���� �׸���
void drawLines()
{
	/*
	* void line(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
	- img        : ����� ����
	- pt1        : ������
	- pt2        : ����
	- color      : �� ���� (�Ǵ� ���)
	- thickness  : �� �β�
	- lineType   : �� Ÿ��. LINE_4, LINE_8, LINE_AA �� �ϳ��� �����մϴ�.
	- shift      : �׸��� ��ǥ ���� ��� ����(������ ��Ʈ ����Ʈ(>>) ����)
	*/
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));
	line(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);
	line(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);

	/*
	* lineTypes ������ ��� 
		FILLED / -1 / ���θ� ä��(���� �׸��� �Լ����� ��� �Ұ�)
		LINE_4 / 4 / 4���� ����
		LINE_8 / 8 / 8���� ����
		LINE_AA / 18 / ��Ƽ���ϸ����(anti-aliasing)
	*/
	line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);
	line(img, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);
	line(img, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);

	//  ȭ��ǥ ������ ������ �׷��� �ϴ� ��쿡�� arrowedLine() �Լ��� �̿�
	/*
	* void arrowedLine(InputOutputArray img, Point pt1, Point pt2, const Scalar& color,
                 int thickness=1, int line_type=8, int shift=0, double tipLength=0.1);
	- line ���� (img, pt1, pt2, color, thickness, linetype, shift)
	- tipLength  : ��ü ���� ���̿� ���� ȭ��ǥ ������ ����
	*/
	arrowedLine(img, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);
	arrowedLine(img, Point(50, 250), Point(350, 250), Scalar(255, 0, 255), 1);
	arrowedLine(img, Point(50, 300), Point(350, 300), Scalar(255, 0, 0), 1, LINE_8, 0, 0.05);

	// drawMarker() �Լ��� ���� �׸��� �Լ��� �̿��Ͽ� �پ��� ����� ��Ŀ(marker)�� �׸�
	/* 
	* void drawMarker(InputOutputArray img, Point position, const Scalar& color,
					int markerType = MARKER_CROSS, int markerSize=20, int thickness=1,
					int line_type=8);
	- line ���� (img, pt1, pt2, color, thickness, linetype, shift)
		MARKER_CROSS         : ���ڰ� ���(+ ���) 
		MARKER_TILTED_CROSS  : 45�� ȸ���� ���ڰ� ���(�� ���)
		MARKER_STAR          : MARKER_CROSS ���� MARKER_TILTED_CROSS ����� ������ ����( ���)
		MARKER_DIAMOND       : ������ ���(�� ���)
		MARKER_SQUARE        : ���簢�� ���(�� ���)
		MARKER_TRIANGLE_UP   : ���� ������ �ﰢ��(�� ���) 
		MARKER_TRIANGLE_DOWN : �Ʒ��� ������ �ﰢ��(�� ���)
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

// ���� �׸��� 
void drawPolys()
{

	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));
	/*
	* �ΰ��� ���
	* void rectangle(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
	* void rectangle(InputOutputArray img, Rect rec, const Scalar& color,int thickness = 1, int lineType = LINE_8, int shift = 0);
			- img        : ����� ����
			- pt1        : �簢�� ������ ��ǥ, point ��ü
			- pt2        : pt1�� �밢 ���⿡ �ִ� �簢�� ������ ��ǥ. Point ��ü
			- rec        : �簢�� ��ġ ����. Rect ��ü
			- color      : �簢�� ���� (�Ǵ� ���)
			- thickness  : �簢�� �ܰ��� �β�. �� ���� ����(-1 �Ǵ� FILLED)�̸� ���θ� ä��
			- lineType   : �� Ÿ��
			- shift      : �׸��� ��ǥ ���� ��� ����(������ ��Ʈ ����Ʈ(>>) ����)
	*/
	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2);
	rectangle(img, Rect(50, 150, 100, 50), Scalar(0, 0, 128), -1);
	/* 
	* void circle(InputOutputArray img, Point center, int radius,  const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
			- img        : ����� ����
			- center     : ���� �߽�
			- radius     : ���� ������
			- color      : �� ����
			- thickness  : �� �ܰ��� �β�. �� ���� ����(-1 �Ǵ� FILLED)�̸� ���θ� ä��
			- lineType   : �� Ÿ��
			- shift      : �׸��� ��ǥ ���� ��� ����(������ ��Ʈ ����Ʈ(>>) ����)
	*/
	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA);
	circle(img, Point(300, 120), 60, Scalar(255, 0, 0), 3, LINE_AA);

	/* 
	* void ellipse(InputOutputArray img, Point center, Size axes,  double angle, double startAngle, double endAngle, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
			- img        : ����� ����
			- center     : Ÿ����  �߽�
			- axes       : Ÿ����  ������, Size(x��_������, y��_������)
			- angle      : Ÿ�� ȸ�� ����(x�� ����, �ð� ����)
			- startAngle : Ÿ�� ȣ�� ���� ����(x�� ����, �ð� ����)
			- endAngle   : Ÿ�� ȣ�� �� ����(x�� ����, �ð� ����)
			- color      : Ÿ��  ����
			- thickness  : Ÿ��  �ܰ��� �β�. �� ���� ����(-1 �Ǵ� FILLED)�̸� ���θ� ä��
			- lineType   : �� Ÿ��
			- shift      : �׸��� ��ǥ ���� ��� ����(������ ��Ʈ ����Ʈ(>>) ����)
	*/
	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), FILLED, LINE_AA);
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);

	vector<Point> pts;
	pts.push_back(Point(250, 250)); pts.push_back(Point(300, 250));
	pts.push_back(Point(300, 300)); pts.push_back(Point(350, 300));
	pts.push_back(Point(350, 350)); pts.push_back(Point(250, 350));
	/* 
	* void polylines(InputOutputArray img, InputArrayOfArrays pts,  bool isClosed, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
			- img        : ����� ����
			- pts        : �ٰ��� �ܰ� ������ ��ǥ �迭. �ַ� vector<Point> Ÿ��
			- angle      : Ÿ�� ȸ�� ����(x�� ����, �ð� ����)
			- isClosed   : �ٰ����� ���� �ִ����� ��Ÿ���� �÷���. �� ���� true�̸� �ٰ����� ������ �������� ù ��° �������� �մ� ������ �߰��� �׸�
			- color      : �� ����
			- thickness  : �� �β�. �� ���� ����(-1 �Ǵ� FILLED)�̸� ���θ� ä��
			- lineType   : �� Ÿ��
			- shift      : �׸��� ��ǥ ���� ��� ����(������ ��Ʈ ����Ʈ(>>) ����)
	*/
	polylines(img, pts, true, Scalar(255, 0, 255), 2);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

// ���ڿ� ���
void drawText1()
{
	Mat img(500, 800, CV_8UC3, Scalar(255, 255, 255));
	/*
	* void putText(InputOutputArray img, const String& text, Point org, int fontFace, double fontScale, Scalar color,
             int thickness = 1, int lineType = LINE_8,bool bottomLeftOrigin = false);
			- img              : ����� ����
			- text             : ����� ���ڿ�
			- org              : ���󿡼� ���ڿ��� ����� ��ġ�� ���� �ϴ� ��ǥ
			- fontFace         : ��Ʈ ����. cv::HersheyFonts���� ����
			- fontScale        : ��Ʈ ũ�� Ȯ��/��� ����
			- color            : ���ڿ� ����
			- thickness        : ���ڿ��� �׸� �� ����� �� �β�
			- lineType         : �� Ÿ��. LINE_4, LINE_8, LINE_AA �� �ϳ��� ����
			- bottomLeftOrigin : �� ���� true�̸� ������ ���� �ϴ��� �������� �����մϴ�. false�̸� ���� ����� ����
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
	* HersheyFonts ������ ���
		FONT_HERSHEY_SIMPLEX        : �Ϲ� ũ���� �꼼���� ��Ʈ
		FONT_HERSHEY_PLAIN          : ���� ũ���� �꼼���� ��Ʈ
		FONT_HERSHEY_DUPLEX         : �Ϲ� ũ���� �꼼���� ��Ʈ(FONT_HERSHEY_SIMPLEX���� ������ ����)
		FONT_HERSHEY_COMPLEX        : �Ϲ� ũ���� ������ ��Ʈ
		FONT_HERSHEY_TRIPLEX        : �Ϲ� ũ���� ������ ��Ʈ(FONT_HERSHEY_COMPLEX���� ������ ����)
		FONT_HERSHEY_COMPLEX_SMALL  : FONT_HERSHEY_COMPLEX���� ���� ��Ʈ
		FONT_HERSHEY_SCRIPT_SIMPLEX : �ʱ�ü ��Ÿ���� ��Ʈ
		FONT_HERSHEY_SCRIPT_COMPLEX : �ʱ�ü ��Ÿ���� ��Ʈ(FONT_HERSHEY_SCRIPT_SIMPLEX���� ������ ����)
		FONT_ITALIC                 : ���Ÿ�ü�� ���� �÷���
	
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

	// ���ڿ� ����� ���� �ʿ��� �簢�� ���� ũ�⸦ ������ �� �ִ� getTextSize() �Լ��� ����. 
	// �� �Լ��� �� �̿��ϸ� ���ڿ��� �������� ġ��ġ�� �ʰ� ������ ��ġ�� ��µǵ��� ������ �� �ִ� 
	/*
	Size getTextSize(const String& text, int fontFace, double fontScale, int thickness, int* baseLine);
			- text       : ����� ���ڿ�
			- fontFace   : ��Ʈ ����
			- fontScale  : ��Ʈ ũ�� Ȯ��/��� ����
			- thickness  : ���ڿ��� �׸� �� ����� �� �β�
			- baseLine   : (���) ���� �ϴ��� �ؽ�Ʈ ��ġ�� �������� �ϴ� ���ؼ�(baseline)�� y ��ǥ, �ʿ� ������ 0 ����
			- ��ȯ��     : ������ ���ڿ� ��� �� �����ϴ� �簢�� ũ��
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
// ���� : OpenCV�� �׸��� �Լ��� ������ �ȼ� ���� ������� �׸��� �׸���. �׷��Ƿ� �Ϲ� ���� ���� �׸��� �Լ� ����, ����, ���ڿ��� ����ϸ� ��ʺ� ������ �ȼ� ���� ���� �� �� ���� �ȴ�.
//        ���� ���� �׸��⸦ ������ �Ŀ� �ٽ� ���� ������ ����� �ʿ䰡 �ִٸ� �̸� ������ ������ �ΰ� ����ؾ� �Ѵ�.
//        �̶�, ���� ������ Ȥ�� Mat Ŭ���� ���� �����ڸ� ����Ͽ� �����ϴ� ���� �ƴ϶�  �ƴ϶� Mat::clone() �Ǵ� Mat::copyTo() �Լ��� ����ؾ� �Ѵ�