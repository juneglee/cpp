#include "opencv2/opencv.hpp"
#include <iostream>

// VideoCapture Ŭ����
/*
* �������̶� �Ϸ��� ���� ������ �����Ͽ� ���Ϸ� ������ �����Դϴ�. 
* �̶� ������ ����Ǿ� �ִ� �Ϸ��� ���� ������ ������(frame)�̶�� �մϴ�. 
* �׷��Ƿ� �������� ó���ϴ� �۾��� �����󿡼� �������� ������ ��, ������ �����ӿ� ���� ó�� ����� �����ϴ� ���·� �̷�����ϴ�. 
* ��ǻ�Ϳ� ����� ī�޶� ��ġ�� ����ϴ� �۾��� ī�޶�κ��� ���� �ð� �������� ���� ���� �������� �޾� �ͼ� ó���ϴ� �����Դϴ�.
* �׷��Ƿ� ī�޶�� ������ ������ �ٷ�� �۾��� �������� ������ ������ �޾� �ͼ� ó���Ѵٴ� �������� ��
*/

using namespace cv;
using namespace std;

void camera_in();
void video_in();
void camera_in_video_out();

int main(void)
{
	camera_in();
	video_in();
	camera_in_video_out();

	return 0;
}

void camera_in()
{
	/*
	* ��ǻ�Ϳ� ����� ī�޶� ��ġ�� ����ϴ� ���
	* VideoCapture::VideoCapture(int index, int apiPreference = CAP_ANY);
	* bool VideoCapture::open(int index, int apiPreference = CAP_ANY);
		- index         : ī�޶�� ��ġ ��� ��� ���� ��ȣ
		- apiPreference : ����� ī�޶� ĸó API �鿣��
		- ��ȯ��        : (VideoCapture::open() �Լ�) ���Ⱑ �����ϸ� true, �����ϸ� false
	*/
	// ��ǻ�Ϳ� ����� �⺻ ī�޶�κ��� �� �������� ���� ������ �޾� ������ ������ ���� ���·� �ڵ带 �ۼ�
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27) // ESC key
			break;
	}

	destroyAllWindows();
}

void video_in()
{
	/*
	* ������ ������ �ҷ����� ���
	* VideoCapture::VideoCapture(const String& filename, int apiPreference = CAP_ANY);
	* bool VideoCapture::open(const String& filename, int apiPreference = CAP_ANY);
		- filename      : ������ ���� �̸� (.avi, *.mpg, *.mp4 �� Ȯ����) --( ��img%04d.jpg��)
		- apiPreference : ����� ���� ĸó API �鿣��
		- ��ȯ��        : (VideoCapture::open() �Լ�) ���Ⱑ �����ϸ� true, �����ϸ� false

	* �ֿ� VideoCaptureAPIs ������ ���
	CAP_ANY                                  : �ڵ� ����
	CAP_V4L, CAP_V4L2                        : V4L/V4L2(������)
	CAP_FIREWIRE, CAP_FIREWARE, CAP_IEEE1394 : IEEE 1394 ����̹�
	CAP_DSHOW								 : ���̷�Ʈ��(DirectShow)
	CAP_PVAPI								 : PvAPI, Prosilica GigE SDK
	CAP_OPENNI								 : OpenNI
	CAP_MSMF							     : ����ũ�μ���Ʈ �̵�� �Ŀ�̼� (Microsoft Media Foundation)
	CAP_GSTREAMER							 : GStreamer
	CAP_FFMPEG								 : FFMPEG ���̺귯��
	CAPIMAGES								 : OpenCV���� �����ϴ� �Ϸ��� ���� ���� (��) img%02d.jpg
	CAP_OPENCV_MJPEG						 : OpenCV�� ����� MotionJPEG �ڵ�
	*/
	VideoCapture cap("video/stopwatch.avi");

	// ������ ���� ���⸦ ������ �Ŀ��� VideoCapture::isOpened() ��� �Լ��� �̿��Ͽ� ���� �۾��� ���������� ����Ǿ����� Ȯ��
	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return;
	}

	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;

	// ���� ���� �ִ� ī�޶� ��ġ �Ǵ� ������ ���Ϸκ��� ���� ���� ������ �޾� ���� ���ؼ��� VideoCapture::get() �Լ��� ���
	// VideoCapture::get() �Լ��� �ݴ�� ���� ���� �ִ� ī�޶� �Ǵ� ���� ���� ����� ���õ� �Ӽ� ���� ������ ������ VideoCapture::set() �Լ��� ���
	/*
	�ֿ� VideoCaptureProperties ������ ���
	CAP_PROP_POS_MSEC      : ���� ���Ͽ��� ���� ��ġ(�и��� ����)
	CAP_PROP_POS_FRAMES    : ���� ������ ��ġ(0-���)
	CAP_PROP_POS_FRAMES    : [0, 1] �������� ǥ���� ������ �������� ����� ��ġ(0: ����, 1: ��)
	CAP_PROP_FRAME_WIDTH   : ���� �������� ���� ũ��
	CAP_PROP_FRAME_HEIGHT  : ���� �������� ���� ũ��  
	CAP_PROP_FPS		   : �ʴ� ������ ��  
	CAP_PROP_FOURCC        : fourcc �ڵ�(�ڵ��� ǥ���ϴ� ���� ��)  
	CAP_PROP_FRAME_COUNT   : ���� ������ ��ü ������ ��  
	CAP_PROP_BRIGHTNESS    : (ī�޶󿡼� �����ϴ� ���) ��� ����  
	CAP_PROP_CONTRAST      : (ī�޶󿡼� �����ϴ� ���) ��Ϻ� ����  
	CAP_PROP_SATURATION    : (ī�޶󿡼� �����ϴ� ���) ä�� ���� 
	CAP_PROP_HUE           : (ī�޶󿡼� �����ϴ� ���) ���� ����  
	CAP_PROP_GAIN          : (ī�޶󿡼� �����ϴ� ���) ���� ����  
	CAP_PROP_EXPOSURE      : (ī�޶󿡼� �����ϴ� ���) ���� ����  
	CAP_PROP_ZOOM          : (ī�޶󿡼� �����ϴ� ���) �� ����  
	CAP_PROP_FOCUS         : (ī�޶󿡼� �����ϴ� ���) ���� ����  
	*/
	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;

	// VideoCapture::get() �Լ��� ī�޶� �Ǵ� ������ ���� �Ӽ��� double �ڷ������� ��ȯ
	// cvRound() �Լ��� OpenCV���� �����ϴ� �ݿø� �Լ��̰�, ���� w���� ������ ���� ũ��, h���� ������ ���� ũ�Ⱑ ����
	int delay = cvRound(1000 / fps);

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;
		/*
		* ī�޶� ��ġ�� ����� �� �ִ� ���¶�� ���� ī�޶� ��ġ�κ��� �������� �޾� �� �� �ֽ��ϴ�. 
		* �ϳ��� �������� �� ���� ���� ������ �ǹ��ϱ� ������ Mat Ŭ���� ��ü�� ������ �� �ְ�, 
		* Mat ��ü�� ����� ������ imshow() �Լ��� ����Ͽ� ȭ�鿡 ����� �� �ֽ��ϴ�.
		*/
		imshow("frame", frame);
		imshow("inversed", inversed);

		// ���� 27�� Ű���忡�� Esc Ű�� �ش��ϴ� Ű ���̸�, �� ���� �ڵ�� ����ڰ� Esc Ű�� ���� �� while �ݺ����� ���������� �˴ϴ�.
		if (waitKey(delay) == 27) // ESC key
			break;
	}

	destroyAllWindows();
}

void camera_in_video_out()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(CAP_PROP_FPS);

	// static int VideoWriter::fourcc(char c1, char c2, char c3, char c4);
	// c1, c2, c3, c4 �ڵ��� ǥ���ϴ� 1byte ���� �� ��
	//  ��ȯ��	������ 4 - ���� �ڵ�
	/* 
	VideoWriter::fourcc(��D��, ��I��, ��V��, ��X��) DivX MPEG-4 �ڵ�
	VideoWriter::fourcc(��X��, ��V��, ��I��, ��D��) XVID MPEG-4 �ڵ�
	VideoWriter::fourcc(��F��, ��M��, ��P��, ��4��) FFMPEG MPEG4 �ڵ�
	VideoWriter::fourcc(��W��, ��M��, ��V��, ��2��) Windows Media Video 8 �ڵ�
	VideoWriter::fourcc(��M��, ��J��, ��P��, ��G��) ��� JPEG �ڵ�
	VideoWriter::fourcc(��Y��, ��V��, ��1��, ��2��) YUV 4:2:0 Planar(�����)
	VideoWriter::fourcc(��X��, ��2��, ��6��, ��4��) H.264/AVC �ڵ�
	VideoWriter::fourcc(��A��, ��V��, ��C��, ��1��) Advanced Video �ڵ�
	*/
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps);

	/* 
	VideoWriter::VideoWriter(const String& filename, int fourcc, double fps,Size frameSize, bool isColor = true);
	bool VideoWriter::open(const String& filename, int fourcc, double fps, Size frameSize, bool isColor = true);
		- filename      : ������ ������ ���� �̸�
		- apiPreference : ������ ���� �ڵ��� ǥ���ϴ� 4-���� �ڵ�
		- fps           : ������ �������� �ʴ� ������ ��
		- frameSize     : ������ �������� ���� �� ���� ũ��
		- isColor       : �� ���� true�̸� �÷� ���������� �����ϰ�, false�̸� �׷��̽����� ���������� �����մϴ�. �� �÷��״� Windows � ü�������� ������
		- ��ȯ��        : (VideoCapture::open() �Լ�) ���Ⱑ �����ϸ� true, �����ϸ� false
	*/
	VideoWriter outputVideo("video/output.avi", fourcc, fps, Size(w, h));

	if (!outputVideo.isOpened()) {
		cout << "File open failed!" << endl;
		return;
	}

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;
		outputVideo << inversed;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}

	destroyAllWindows();
}