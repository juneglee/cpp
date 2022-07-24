#include "opencv2/opencv.hpp"
#include <iostream>

// VideoCapture 클래스
/*
* 동영상이란 일련의 정지 영상을 압축하여 파일로 저장한 형태입니다. 
* 이때 동영상에 저장되어 있는 일련의 정지 영상을 프레임(frame)이라고 합니다. 
* 그러므로 동영상을 처리하는 작업은 동영상에서 프레임을 추출한 후, 각각의 프레임에 영상 처리 기법을 적용하는 형태로 이루어집니다. 
* 컴퓨터에 연결된 카메라 장치를 사용하는 작업도 카메라로부터 일정 시간 간격으로 정지 영상 프레임을 받아 와서 처리하는 형태입니다.
* 그러므로 카메라와 동영상 파일을 다루는 작업은 연속적인 프레임 영상을 받아 와서 처리한다는 공통점이 있
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
	* 컴퓨터에 연결된 카메라 장치를 사용하는 방법
	* VideoCapture::VideoCapture(int index, int apiPreference = CAP_ANY);
	* bool VideoCapture::open(int index, int apiPreference = CAP_ANY);
		- index         : 카메라와 장치 사용 방식 지정 번호
		- apiPreference : 사용할 카메라 캡처 API 백엔드
		- 반환값        : (VideoCapture::open() 함수) 열기가 성공하면 true, 실패하면 false
	*/
	// 컴퓨터에 연결된 기본 카메라로부터 한 프레임의 정지 영상을 받아 오려면 다음과 같은 형태로 코드를 작성
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
	* 동영상 파일을 불러오는 기능
	* VideoCapture::VideoCapture(const String& filename, int apiPreference = CAP_ANY);
	* bool VideoCapture::open(const String& filename, int apiPreference = CAP_ANY);
		- filename      : 동영상 파일 이름 (.avi, *.mpg, *.mp4 등 확장자) --( “img%04d.jpg”)
		- apiPreference : 사용할 비디오 캡처 API 백엔드
		- 반환값        : (VideoCapture::open() 함수) 열기가 성공하면 true, 실패하면 false

	* 주요 VideoCaptureAPIs 열거형 상수
	CAP_ANY                                  : 자동 선택
	CAP_V4L, CAP_V4L2                        : V4L/V4L2(리눅스)
	CAP_FIREWIRE, CAP_FIREWARE, CAP_IEEE1394 : IEEE 1394 드라이버
	CAP_DSHOW								 : 다이렉트쇼(DirectShow)
	CAP_PVAPI								 : PvAPI, Prosilica GigE SDK
	CAP_OPENNI								 : OpenNI
	CAP_MSMF							     : 마이크로소프트 미디어 파운데이션 (Microsoft Media Foundation)
	CAP_GSTREAMER							 : GStreamer
	CAP_FFMPEG								 : FFMPEG 라이브러리
	CAPIMAGES								 : OpenCV에서 지원하는 일련의 영상 파일 (예) img%02d.jpg
	CAP_OPENCV_MJPEG						 : OpenCV에 내장된 MotionJPEG 코덱
	*/
	VideoCapture cap("video/stopwatch.avi");

	// 동영상 파일 열기를 수행한 후에는 VideoCapture::isOpened() 멤버 함수를 이용하여 열기 작업이 성공적으로 수행되었는지 확인
	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return;
	}

	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;

	// 현재 열려 있는 카메라 장치 또는 동영상 파일로부터 여러 가지 정보를 받아 오기 위해서는 VideoCapture::get() 함수를 사용
	// VideoCapture::get() 함수와 반대로 현재 열려 있는 카메라 또는 비디오 파일 재생과 관련된 속성 값을 설정할 때에는 VideoCapture::set() 함수를 사용
	/*
	주요 VideoCaptureProperties 열거형 상수
	CAP_PROP_POS_MSEC      : 비디오 파일에서 현재 위치(밀리초 단위)
	CAP_PROP_POS_FRAMES    : 현재 프레임 위치(0-기반)
	CAP_PROP_POS_FRAMES    : [0, 1] 구간으로 표현한 동영상 프레임의 상대적 위치(0: 시작, 1: 끝)
	CAP_PROP_FRAME_WIDTH   : 비디오 프레임의 가로 크기
	CAP_PROP_FRAME_HEIGHT  : 비디오 프레임의 세로 크기  
	CAP_PROP_FPS		   : 초당 프레임 수  
	CAP_PROP_FOURCC        : fourcc 코드(코덱을 표현하는 정수 값)  
	CAP_PROP_FRAME_COUNT   : 비디오 파일의 전체 프레임 수  
	CAP_PROP_BRIGHTNESS    : (카메라에서 지원하는 경우) 밝기 조절  
	CAP_PROP_CONTRAST      : (카메라에서 지원하는 경우) 명암비 조절  
	CAP_PROP_SATURATION    : (카메라에서 지원하는 경우) 채도 조절 
	CAP_PROP_HUE           : (카메라에서 지원하는 경우) 색상 조절  
	CAP_PROP_GAIN          : (카메라에서 지원하는 경우) 감도 조절  
	CAP_PROP_EXPOSURE      : (카메라에서 지원하는 경우) 노출 조절  
	CAP_PROP_ZOOM          : (카메라에서 지원하는 경우) 줌 조절  
	CAP_PROP_FOCUS         : (카메라에서 지원하는 경우) 초점 조절  
	*/
	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;

	// VideoCapture::get() 함수는 카메라 또는 동영상 파일 속성을 double 자료형으로 반환
	// cvRound() 함수는 OpenCV에서 제공하는 반올림 함수이고, 변수 w에는 프레임 가로 크기, h에는 프레임 세로 크기가 저장
	int delay = cvRound(1000 / fps);

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;
		/*
		* 카메라 장치를 사용할 수 있는 상태라면 이제 카메라 장치로부터 프레임을 받아 올 수 있습니다. 
		* 하나의 프레임은 한 장의 정지 영상을 의미하기 때문에 Mat 클래스 객체에 저장할 수 있고, 
		* Mat 객체에 저장된 영상은 imshow() 함수를 사용하여 화면에 출력할 수 있습니다.
		*/
		imshow("frame", frame);
		imshow("inversed", inversed);

		// 정수 27은 키보드에서 Esc 키에 해당하는 키 값이며, 이 예제 코드는 사용자가 Esc 키를 누를 때 while 반복문을 빠져나오게 됩니다.
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
	// c1, c2, c3, c4 코덱을 표현하는 1byte 문자 네 개
	//  반환값	정수형 4 - 문자 코드
	/* 
	VideoWriter::fourcc(’D’, ‘I’, ‘V’, ‘X’) DivX MPEG-4 코덱
	VideoWriter::fourcc(‘X’, ‘V’, ‘I’, ’D’) XVID MPEG-4 코덱
	VideoWriter::fourcc(‘F’, ’M’, ‘P’, ‘4’) FFMPEG MPEG4 코덱
	VideoWriter::fourcc(‘W’, ’M’, ‘V’, ‘2’) Windows Media Video 8 코덱
	VideoWriter::fourcc(’M’, ‘J’, ‘P’, ‘G’) 모션 JPEG 코덱
	VideoWriter::fourcc(‘Y’, ‘V’, ‘1’, ‘2’) YUV 4:2:0 Planar(비압축)
	VideoWriter::fourcc(‘X’, ‘2’, ‘6’, ‘4’) H.264/AVC 코덱
	VideoWriter::fourcc(‘A’, ‘V’, ‘C’, ‘1’) Advanced Video 코덱
	*/
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps);

	/* 
	VideoWriter::VideoWriter(const String& filename, int fourcc, double fps,Size frameSize, bool isColor = true);
	bool VideoWriter::open(const String& filename, int fourcc, double fps, Size frameSize, bool isColor = true);
		- filename      : 저장할 동영상 파일 이름
		- apiPreference : 동영상 압축 코덱을 표현하는 4-문자 코드
		- fps           : 저장할 동영상의 초당 프레임 수
		- frameSize     : 동영상 프레임의 가로 및 세로 크기
		- isColor       : 이 값이 true이면 컬러 동영상으로 저장하고, false이면 그레이스케일 동영상으로 저장합니다. 이 플래그는 Windows 운영 체제에서만 지원합
		- 반환값        : (VideoCapture::open() 함수) 열기가 성공하면 true, 실패하면 false
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