#include "opencv2/opencv.hpp"
#include <iostream>

// ȯ�� ���� 
// opencv ȯ�� ���� (�ý��� ȯ�� ���� �Ϸ� ��)
// ������Ʈ --> �Ӽ� --> c++ --> �Ϲ� --> �߰� ���� ���͸� --> opencv (build����)
// ������Ʈ --> �Ӽ� --> ��Ŀ --> �Ϲ� --> �߰� ���̺귯�� ���͸� --> opencv (build/x64/lib)
// ������Ʈ --> �Ӽ� --> ��Ŀ --> �Է� --> �߰� ���Ӽ� -->  opencv_world453d.lib �Է� (�������� �ٸ� �� ������ xxxd�� Ȯ�� �� ����)

int main()
{
	std::cout << CV_VERSION << std::endl;

	return 0;
}