#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	Mat src1 = imread("images/lenna.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("images/field.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	add(src1, src2, dst1);
	/* 영상의 덧셈
	* add() 함수는 두 개의 행렬 또는 영상을 입력으로 받고, 하나의 행렬 또는 영상을 출력으로 생성
	void add(InputArray src1, InputArray src2, OutputArray dst,
         InputArray mask = noArray(), int dtype = -1);
		 - src1 : 첫 번째 입력 행렬 또는 스칼라
		 - src2 : 두 번째 입력 행렬 또는 스칼라
		 - dst : 입력 행렬과 같은 크기, 같은 채널 수를 갖는 출력 행렬.
					dst의 깊이는 src1, src2의 깊이와 같거나 또는 dtype 인자에 의해 결정됩니다.
		 - mask : 8비트 1채널 마스크 영상. mask 행렬 원소 값이 0이 아닌 위치에서만 덧셈 연산을 수행합니다.
		 - dtype : 출력 행렬의 깊이. src1과 src2의 깊이가 같은 경우에는 dtype에 -1을 지정할 수 있고, 이 경우 dst의 깊이는 src1, src2와 같은 깊이로 설정
					src1과 src2의 깊이가 서로 다른 경우에는 dtype을 반드시 지정해야 한다
	*/
	addWeighted(src1, 0.5, src2, 0.5, 0, dst2);
	/* 두 영상의 가중치 합
	* addWeighted() 함수는 gamma 인자를 통해 가중치의 합에 추가적인 덧셈을 한꺼번에 수행
	void addWeighted(InputArray src1, double alpha, InputArray src2,
					 double beta, double gamma, OutputArray dst, int dtype = -1);
		 - src1  : 첫 번째 입력 행렬
		 - alpha : src1 행렬의 가중치
		 - src2  : 두 번째 입력 행렬. (src1과 크기와 채널 수가 같아야 한다 )
		 - beta  : src2 행렬의 가중치
		 - gamma : 가중합 결과에 추가적으로 더할 값
		 - dst   : 출력 행렬. 입력 행렬과 같은 크기, 같은 채널 수의 행렬이 생성
		 - dtype : 출력 행렬의 깊이. 
				   src1과 src2의 깊이가 같은 경우에는 dtype에 -1을 지정할 수 있고, 이 경우 dst의 깊이는 src1, src2와 같은 깊이로 설정
				   src1과 src2의 깊이가 서로 다른 경우에는 dtype을 반드시 지정해야 합니다.
	*/
	subtract(src1, src2, dst3);
	/* 두 영상의 뺄셈 연산 
	void subtract(InputArray src1, InputArray src2, OutputArray dst,
              InputArray mask = noArray(), int dtype = -1);
		 - src1  : 첫 번째 입력 행렬 또는 스칼라
		 - src2  : 두 번째 입력 행렬 또는 스칼라
		 - dst   : 입력 행렬과 같은 크기, 같은 채널 수를 갖는 출력 행렬.
				   dst의 깊이는 src1, src2의 깊이와 같거나 또는 dtype 인자에 의해 결정됩니다.
		 - mask  : 8비트 1채널 마스크 영상. mask 행렬 원소 값이 0이 아닌 위치에서만 덧셈 연산을 수행합니다.
		 - dtype : 출력 행렬의 깊이. src1과 src2의 깊이가 같은 경우에는 dtype에 -1을 지정할 수 있고, 이 경우 dst의 깊이는 src1, src2와 같은 깊이로 설정
				   src1과 src2의 깊이가 서로 다른 경우에는 dtype을 반드시 지정해야 한다
	*/
	absdiff(src1, src2, dst4);
	/* 차이 연산
	* 두 영상의 뺄셈 순서에 상관없이 픽셀 값 차이가 큰 영역을 두드러지게 나타내고 싶다면 차이 연산을 수행
	* 차이 연산은 뺄셈 연산 결과에 절댓값을 취하는 연산이며, 차이 연산으로 구한 결과 영상을 차영상(difference image)이라 한다
	void absdiff(InputArray src1, InputArray src2, OutputArray dst);
		 - src1  : 첫 번째 입력 행렬 또는 스칼라
		 - src2  : 두 번째 입력 행렬 또는 스칼라
		 - dst   : 출력 행렬. 입력 행려과 같은 크기, 같은 채널 수의 행렬이 생성 

	*/

	// 영상도 일종의 행렬이므로 두 입력 영상을 행렬로 생각하여 행렬의 곱셈으로 수행할 수 있다 
	//  그러나 영상을 이용하여 행렬의 곱셈을 수행하는 경우는 거의 없다. 다만 두 영상에서 같은 위치에 있는 픽셀 값끼리 서로 곱하거나 나누는 연산을 수행할 수 있으며 
	// 이를 위해 opencv에서는 multiply()함수와 divide() 함수를 제공
	/*
	void multiply(InputArray src1, InputArray src2,
              OutputArray dst, double scale = 1, int dtype = -1);
		 - src1  : 첫 번째 입력 행렬 
		 - src2  : 두 번째 입력 행렬, src1과 크기와 타입이 같아야 한다 
		 - dst   : 출력 행렬. src1과 같은 크기, 같은 타입
			dst(x, y)＝saturate(scale·src1(x, y)·src2(x, y))
		 - scale : 추가적으로 확대/축소할 비율
		 - dtype : 출력 행렬의 깊이

	void divide(InputArray src1, InputArray src2, OutputArray dst,
            double scale = 1, int dtype = -1);
		 - src1  : 첫 번째 입력 행렬
		 - src2  : 두 번째 입력 행렬, src1과 크기와 타입이 같아야 한다
		 - dst   : 출력 행렬. src1과 같은 크기, 같은 타입
			dst(x, y)＝saturate(scale·src1(x, y)·src2(x, y))
		 - scale : 추가적으로 확대/축소할 비율
		 - dtype : 출력 행렬의 깊이
	*/
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();

	return 0;
}