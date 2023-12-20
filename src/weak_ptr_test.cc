#include <iostream>
#include <memory>


std::weak_ptr<int> gw;

void observe() {
    std::cout << "gw.use_count() == " << gw.use_count() << "\n";

    if (std::shared_ptr<int> spt = gw.lock()) {
        std::cout << "*spt == " << *spt << "\n";
    }
    else {
        std::cout << "gw is expired\n";
    }
}

int main() {
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;

        // 测试没有lock，直接使用
        // std::cout << *gw << "\n"; // 不支持*operator

        // lock使用
        std::cout << *gw.lock() << "\n";

        std::cout << "first call. \n";
        observe();
    }
    std::cout << "sencond call. \n";

    // std::cout << *sp; => error: sp已经回收
    if (gw.expired()) {
        std::cout << "gw expired\n";
    }
    observe();
}