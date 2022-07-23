#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void writeData();
void readData();

// String filename = "mydata.xml";
// String filename = "mydata.yml";
String filename = "mydata.json";

int main(void)
{
	writeData();
	readData();

	return 0;
}

// FileStorage 클래스
/*
* virtual bool FileStorage::open(const String& filename, int flags, const String& encoding = String());
	- filename  : 파일 이름
	- flags     : 파일 열기 모드
	- encoding  : (XML) 파일 인코딩 방식
	- 반환값    : 정상적으로 파일을 열면 true, 실패하면 false를 반환
*/

// 주요 FileStorage::mode 열거형 상수
// FileStorage::READ   : 읽기 모드
// FileStorage::WRITE  : 쓰기 모드(새로 생성)
// FileStorage::APPEND : 추가로 쓰기 모드
// FileStorage::MEMORY : 논리합 연산자(|)를 이용하여 FileStorage::READ 또는 FileStorage::WRITE 상수와 함께 사용될 경우, 실제 파일 입출력 대신 메모리 버퍼를 이용한 입출력을 수행
void writeData()
{
	String name = "Jane";
	int age = 10;
	Point pt1(100, 200);
	vector<int> scores = { 80, 90, 50 };
	Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);

	FileStorage fs;
	fs.open(filename, FileStorage::WRITE);

	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}

	fs << "name" << name;
	fs << "age" << age;
	fs << "point" << pt1;
	fs << "scores" << scores;
	fs << "data" << mat1;

	fs.release();
}

void readData()
{
	String name;
	int age;
	Point pt1;
	vector<int> scores;
	Mat mat1;

	FileStorage fs(filename, FileStorage::READ);

	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}

	fs["name"] >> name;
	fs["age"] >> age;
	fs["point"] >> pt1;
	fs["scores"] >> scores;
	fs["data"] >> mat1;

	fs.release();

	cout << "name: " << name << endl;
	cout << "age: " << age << endl;
	cout << "point: " << pt1 << endl;
	cout << "scores: " << Mat(scores).t() << endl;
	cout << "data:\n" << mat1 << endl;
	
	// mydata.json
	/* 
	{
		"name": "Jane",
		"age": 10,
		"point": [ 100, 200 ],
		"scores": [ 80, 90, 50 ],
		"data": {
			"type_id": "opencv-matrix",
			"rows": 2,
			"cols": 2,
			"dt": "f",
			"data": [ 1.0, 1.50000000e+00, 2.0, 3.20000005e+00 ]
		}
	}
	*/
}