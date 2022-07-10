#include <iostream>

// 클래스 열거형(enumeration class)
/* 
enum class는 명확한 하나의 독립된 값이다. std::cout, std::printf 등 출력할 수 없다.
즉 swich ~ case ~:나 if 등에서 구분하는 것만 가능하다. 
스코프 연산자 :: 사용해야 하므로 클래스가 다르면 동일한 이름을 사용할 수 있다.
즉 enum class COLOR { RED, GREEN, BLUE }; enum class WALLCOLOR { RED, GREEN, BLUE}; 를 COLOR:RED, WALLCOLOR::RED 로 사용할 수 있다.
코드 타이핑이 늘어 귀찮을 수 있으나 명확할 수록 오류는 줄어든다.
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