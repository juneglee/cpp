#include <iostream>
#include <sstream>
// Ŭ���� ����
/*
 Ŭ������ ���� (implementation)�� ��ü�� ��� ���������� ��ü�� ���� �ڷḦ ����� ��
 ���⼭ ������ ����Լ��� ���ϸ� ���� �ǹ̷� �޼���(method)��� �Ѵ� 
 �׸��� �ǹ������� �����ϴ� ������Ƽ(property), �̺�Ʈ(event)����ϸ�, �ڷ�� ��������� ���ϰ� �Ӽ�(attribute), �ʵ�(field)��� �Ѵ�
*/
class UserType;

// Ŭ���� ����
/* 
���� ��Ҵ� �Լ�(member functions), ����(member variables), �׸��� �� �Լ��� ������ ���� ��ȣ��å(protection)���� public, protected, private�� ����Ͽ� ��� ���� ����(member access control)�Ѵ�.

Ŭ���� ����� Ư���Լ��� ������(constructor), �Ҹ���(destructor), ���������(copy constructor), �̵�������(move constructor), 
���� ���� ������(copy assignment operator), �̵� ���� ������(move assignment operator)�� ��, ��� ������(logic & arithmetic operators)�� �̿� ������ ���� �Լ��� ����Լ��� �ְ�. 
����Լ��� ����(static), ����(virtual), ���(const) �Լ��� ���� �� �ִ�.
�׸��� enum, enum class, type alias, netsted class, ����, ��ü �� ��������� �ִ�.
*/
class UserType {
public:
    // type alias
    using value_type = char;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    // �⺻������, default
    UserType() = default;
    // �Ҹ���, default
    virtual ~UserType() = default;
    // ���������
    UserType(const UserType& user);
    // ���� ���� ������
    UserType& operator=(const UserType& user);
    // �̵�������
    UserType(UserType&& user);
    // �̵� ���� ������
    UserType& operator=(UserType&& user);

    // nested struct ����
    struct DateType {
        // ������ ����� ����
        DateType(int year, int month, int day)
            : nYear(year), nMonth(month), nDay(day) {}
        // ������� ����
        int nYear;
        int nMonth;
        int nDay;
        // ����Լ� ����� ����
        const std::string to_string() const {
            std::ostringstream oss;
            oss << nYear << '.' << nMonth << '.' << nDay;
            return oss.str();
        }
    };
    // ��� �Լ� ����
    // void setName(std::string_view str);
    void setBirth(const DateType& date);

    // ��� �Լ� ����� ����
    const std::string& getName() const { return strName_; }
    const DateType& getBirth() const { return Birth_; }

private:
    // ������� ����
    std::string strName_;
    // ������� ���ǿ� �ʱ�ȭ
    DateType Birth_ = DateType{ 1900, 01, 01 };
};

// ����Լ� ����
// void UserType::setName(std::string_view str) { strName_ = str; }
void UserType::setBirth(const DateType& date) { Birth_ = date; }

int main()
{
    // ��ü ����
    UserType User;
    std::cout << User.getName() << '\t' << User.getBirth().to_string() << std::endl;
    // User.setName("David");
    User.setBirth(UserType::DateType(1999, 12, 31));
    std::cout << User.getName() << '\t' << User.getBirth().to_string() << std::endl;

    return EXIT_SUCCESS;
}