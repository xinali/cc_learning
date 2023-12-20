// test static_cast<newType>(expression)
// doc: https://en.cppreference.com/w/cpp/language/static_cast
// compile && run: clang++ test_static_cast.cc --std=c++11 -o test.bin && ./test.bin

#include "cc_learning_test.h"

struct B {
    int m;
    const char* hello() const {
        return "hello world, this is in B!\n";
    }
};


struct D: B {
    const char* hello() const {
        return "hello world, this is in D!\n";
    }
    int c;
};

enum class E { ONE = 1, TWO, THREE };
enum EU { ONE = 1, TWO, THREE };


TEST(CCLearningTest, StaticCastTest) {
    D d;

    // 隐含转换
    B& br = d; 
    std::cout << "1) " << br.hello(); 

    // 这么转有风险，因为d可能存在b中没有的数据
    D& another_d = static_cast<D&>(br);
    std::cout << "1) " << another_d.hello();

    // 数据未定义
    std::cout << "child data: " << another_d.c << "\n";

    std::vector<int> v0{1, 2, 3}; 
    // 左值转化为右值 -> 延伸万能引用， 左值会reset，这里应该相当于move
    std::vector<int> v2 = static_cast<std::vector<int>&&>(v0);
    std::cout << "2) after move, v0.size() = " << v0.size() << "\n";
    std::cout << "2) after get, v2.size() = " << v2.size() << "\n";

    int n = static_cast<int>(3.14);
    std::cout << "3) n = " << n << "\n";
    std::vector<int> v = static_cast<std::vector<int>>(10);
    std::cout << "3) v.size() = " << v.size() << "\n";

    void *nv = &n;
    int* ni = static_cast<int*>(nv);
    std::cout << "4) *ni = " << *ni << "\n";

    D a[10];
    // 数组指针转移
    B* dp = static_cast<B*>(a);
    std::cout << dp[0].hello(); // in B!

    // 枚举类转化为整数
    E e = E::TWO;
    int two = static_cast<int>(e);
    std::cout << "two value is " << two << "\n";

    // 整数转化为枚举类
    E e2 = static_cast<E>(two);
    std::cout << (e2 == E::TWO) << "\n";

    // 枚举类转化为枚举结构体
    EU eu = static_cast<EU>(e2);
    std::cout << (eu == EU::TWO) << "\n";

    // 指向结构体成员变量的指针
    int D::*pm = &D::m;
    std::cout << "未初始化value: " << pm << "\n";
    // 这种转化目前没有接触过，不太理解
    std::cout << br.*static_cast<int B::*>(pm) << '\n';

    void* voidp = &e;
    // 没理解转化的意义
    std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
    // 输出的是指针地址
    std::cout << p << "\n";
}