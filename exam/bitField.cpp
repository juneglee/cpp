#include <iostream>

// 비트필드(Bit Field)
// struct, class를 이용하고 명시적으로 bit 크기를 지정하여 멤버변수를 선언

struct S {
    unsigned int b : 2;
};
int main()
{
    S s = { 2 };
    ++s.b;
    printf("%d\n", s.b);
    ++s.b;
    printf("%d\n", s.b);
}