#include "cc_learning_test.h"

class A {
public:
    A() {}
    A(int a, double b, std::string c) {
        std::cout << "A(int, double, std::string)" << std::endl;
    }
};

template <typename T>
class Wrapper {
public:
    template <typename... Args>
    Wrapper(Args &&...args) :
        _data(std::forward<Args>(args)...) {}

private:
    T _data;
};

TEST(CCTest, TestForward) {
    Wrapper<A> w1(1, 2.0, "hello"); // 构造函数接受三个参数
    int a = 1;
    float b = 2.0;
    std::string test_str = "hello";
    Wrapper<A> w2(a, b, test_str);
    // Wrapper<A> w2(w1);              // 拷贝构造函数接受一个参数
}