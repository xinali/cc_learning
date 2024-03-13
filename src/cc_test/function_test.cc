#include "cc_learning_test.h"

#include <functional>

void display(int a) {
    std::cout << "display num: " << a << std::endl;
}

// 函数对象
struct Add {
    void operator()(int c) const {
        std::cout << "display num(function object): " << c << std::endl;
    }
};

TEST(CCTest, TestFunction) {
    // 存储普通函数
    std::function<void(int)> func1 = display;
    func1(1);

    // 存储lambda
    std::function<void(int)> func2 = [](int b) { std::cout << "display num(lambda): " << b << std::endl; };
    func2(2);

    // 存储函数对象
    std::function<void(int)> func3 = Add();
    func3(3);
}