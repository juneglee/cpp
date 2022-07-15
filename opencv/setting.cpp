#include "opencv2/opencv.hpp"
#include <iostream>

// 환경 구성 
// opencv 환경 설정 (시스템 환경 설정 완료 후)
// 프로젝트 --> 속성 --> c++ --> 일반 --> 추가 포함 디렉터리 --> opencv (build까지)
// 프로젝트 --> 속성 --> 링커 --> 일반 --> 추가 라이브러리 디렉터리 --> opencv (build/x64/lib)
// 프로젝트 --> 속성 --> 링커 --> 입력 --> 추가 종속성 -->  opencv_world453d.lib 입력 (버전마다 다를 수 있으니 xxxd는 확인 후 변경)

int main()
{
	std::cout << CV_VERSION << std::endl;

	return 0;
}