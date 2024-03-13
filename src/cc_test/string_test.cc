// test string

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "cc_learning_test.h"

void test_string() {
    // std::string &s = "abc"; // 常量引用，出错
    const std::string &s = "abc"; // 常量引用
    std::string &&s_rvalue = "abc"; // 右值引用

    std::cout << s << std::endl;
    std::cout << s_rvalue << std::endl;
}