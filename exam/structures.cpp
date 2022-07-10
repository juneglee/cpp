#include <iostream>

// ����ü(Unions)
/*
union�� ���������� ����ϴ� ��� ���ٴ� struct�� class�� �����Ͽ� ����Ѵ�. 
�ٸ� �ڷ����� ���� ��Ȳ�� ���� �ϳ��� ���������� ����ϱ� ���� ������ ��������� 
������ ���� ����� ����ص� ������ ���ʿ��� ������ �ּ�ȭ �ϱ� ���� ���̴�.
C���� �̾��� ����� ���� �ڷ��� ���� ���
*/
union UserType {
    /*
    int �Ǵ� double �� �ϳ��� ����ϴ� ��� union���� ������ ���� ū �ڷ����� �޸� ������ ���������. 
    int�� double�� ���� ������� �� 4+8byte ������ �ʿ�(�����δ� ����Ʈ ���ķ� 16byte) ������ union���� �����ϸ� 8byte�� ����Ѵ�. 
    �Ϲ������� struct �� �ڷḦ ������ �� �ִ� �÷��׸� ����� union���� ������ ���� �� ��Ȳ�� �´� ���� �̿��Ѵ�.
    ������ ���� union ���� ���� ������ ���� ������ �ִ� ���� �ֱ� ������ �ٸ� ������ ����ϸ� ���� �ٲ��.
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
