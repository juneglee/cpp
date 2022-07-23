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

// FileStorage Ŭ����
/*
* virtual bool FileStorage::open(const String& filename, int flags, const String& encoding = String());
	- filename  : ���� �̸�
	- flags     : ���� ���� ���
	- encoding  : (XML) ���� ���ڵ� ���
	- ��ȯ��    : ���������� ������ ���� true, �����ϸ� false�� ��ȯ
*/

// �ֿ� FileStorage::mode ������ ���
// FileStorage::READ   : �б� ���
// FileStorage::WRITE  : ���� ���(���� ����)
// FileStorage::APPEND : �߰��� ���� ���
// FileStorage::MEMORY : ���� ������(|)�� �̿��Ͽ� FileStorage::READ �Ǵ� FileStorage::WRITE ����� �Բ� ���� ���, ���� ���� ����� ��� �޸� ���۸� �̿��� ������� ����
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