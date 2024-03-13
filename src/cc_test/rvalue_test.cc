#include <iostream>


// template <typename T>
// void func(T& data) {
//     std::cout << "lvalue: " << data << std::endl;
// }

template <typename T>
void func(T&& data) {
    std::cout << "rvalue: " << data << std::endl;
}

int main() {
    int a = 100;
    func(a);
    func(1000);
    return 0;
}