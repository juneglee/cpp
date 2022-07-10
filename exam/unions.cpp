#include <iostream>

// Ŭ���� ������(enumeration class)
/* 
enum class�� ��Ȯ�� �ϳ��� ������ ���̴�. std::cout, std::printf �� ����� �� ����.
�� swich ~ case ~:�� if ��� �����ϴ� �͸� �����ϴ�. 
������ ������ :: ����ؾ� �ϹǷ� Ŭ������ �ٸ��� ������ �̸��� ����� �� �ִ�.
�� enum class COLOR { RED, GREEN, BLUE }; enum class WALLCOLOR { RED, GREEN, BLUE}; �� COLOR:RED, WALLCOLOR::RED �� ����� �� �ִ�.
�ڵ� Ÿ������ �þ� ������ �� ������ ��Ȯ�� ���� ������ �پ���.
*/
int main(int argc, char* argv[])
{
    enum class COLOR { RED, GREEN, BLUE };

    COLOR c = COLOR::RED;

    switch (c) {
    case COLOR::RED:
        std::printf("Color is RED.\n");
        break;
    case COLOR::GREEN:
        std::printf("Color is GREEN.\n");
        break;
    case COLOR::BLUE:
        std::printf("Color is BLUE.\n");
        break;
    default:
        std::printf("There is no correct Color.\n");
        break;
    }

    return EXIT_SUCCESS;
}