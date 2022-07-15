#include <iostream>
#include <sstream>
// 클래스 선언
/*
 클래스의 구현 (implementation)은 객체가 어떻게 동작할지와 객체가 갖는 자료를 만든는 것
 여기서 동작은 멤버함수를 말하며 같은 의미로 메서드(method)라고 한다 
 그리고 의미적으로 구분하는 프로퍼티(property), 이벤트(event)라고도하며, 자료는 멤버변수를 말하고 속성(attribute), 필드(field)라고도 한다
*/
class UserType;

// 클래스 정의
/* 
구성 요소는 함수(member functions), 변수(member variables), 그리고 각 함수와 변수에 대한 보호정책(protection)으로 public, protected, private를 사용하여 멤버 접근 제어(member access control)한다.

클래스 멤버는 특수함수인 생성자(constructor), 소멸자(destructor), 복사생성자(copy constructor), 이동생성자(move constructor), 
복사 대입 연산자(copy assignment operator), 이동 대입 연산자(move assignment operator)와 비교, 산술 연산자(logic & arithmetic operators)와 이외 동작을 위한 함수인 멤버함수가 있고. 
멤버함수는 정적(static), 가상(virtual), 상수(const) 함수로 만들 수 있다.
그리고 enum, enum class, type alias, netsted class, 변수, 객체 등 멤버변수가 있다.
*/
class UserType {
public:
    // type alias
    using value_type = char;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    // 기본생성자, default
    UserType() = default;
    // 소멸자, default
    virtual ~UserType() = default;
    // 복사생성자
    UserType(const UserType& user);
    // 복사 대입 연산자
    UserType& operator=(const UserType& user);
    // 이동생성자
    UserType(UserType&& user);
    // 이동 대입 연산자
    UserType& operator=(UserType&& user);

    // nested struct 정의
    struct DateType {
        // 생성자 선언과 정의
        DateType(int year, int month, int day)
            : nYear(year), nMonth(month), nDay(day) {}
        // 멤버변수 정의
        int nYear;
        int nMonth;
        int nDay;
        // 멤버함수 선언과 정의
        const std::string to_string() const {
            std::ostringstream oss;
            oss << nYear << '.' << nMonth << '.' << nDay;
            return oss.str();
        }
    };
    // 멤버 함수 선언
    // void setName(std::string_view str);
    void setBirth(const DateType& date);

    // 멤버 함수 선언과 정의
    const std::string& getName() const { return strName_; }
    const DateType& getBirth() const { return Birth_; }

private:
    // 멤버변수 정의
    std::string strName_;
    // 멤버변수 정의와 초기화
    DateType Birth_ = DateType{ 1900, 01, 01 };
};

// 멤버함수 정의
// void UserType::setName(std::string_view str) { strName_ = str; }
void UserType::setBirth(const DateType& date) { Birth_ = date; }

int main()
{
    // 객체 정의
    UserType User;
    std::cout << User.getName() << '\t' << User.getBirth().to_string() << std::endl;
    // User.setName("David");
    User.setBirth(UserType::DateType(1999, 12, 31));
    std::cout << User.getName() << '\t' << User.getBirth().to_string() << std::endl;

    return EXIT_SUCCESS;
}