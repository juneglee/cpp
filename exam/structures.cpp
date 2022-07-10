#include <iostream>

// 공용체(Unions)
/*
union은 독립적으로 사용하는 경우 보다는 struct나 class에 포함하여 사용한다. 
다른 자료형의 값을 상황에 따라 하나만 선택적으로 사용하기 위한 것으로 멤버변수를 
여러개 따로 만들어 사용해도 되지만 불필요한 공간을 최소화 하기 위한 것이다.
C부터 이어진 사용자 정의 자료형 선언 방법
*/
union UserType {
    /*
    int 또는 double 중 하나만 사용하는 경우 union으로 묶으면 가장 큰 자료형의 메모리 공간이 만들어진다. 
    int와 double을 따로 만들었을 때 4+8byte 공간이 필요(실제로는 바이트 정렬로 16byte) 하지만 union으로 정의하면 8byte만 사용한다. 
    일반적으로 struct 내 자료를 구분할 수 있는 플래그를 만들고 union으로 정의한 것을 각 상황에 맞는 것을 이용한다.
    주의할 점은 union 내의 여러 변수는 같은 공간에 있는 것이 있기 때문에 다른 변수를 사용하면 값이 바뀐다.
    */
    int nValue;
    double dValue;
};

int main(int argc, char* argv[])
{
    UserType user;

    printf("%d\n", sizeof(user));

    user.nValue = 10;
    printf("%d\n", sizeof(user.nValue));
    printf("%p\n", &user.nValue);
    printf("%d\n", user.nValue);

    user.dValue = 12.34;
    printf("%d\n", sizeof(user.dValue));
    printf("%p\n", &user.dValue);
    printf("%lf\n", user.dValue);

    printf("%d, %lf\n", user.nValue, user.dValue);
    return EXIT_SUCCESS;
}
