// test c++ CRPT
// CRPT wiki: https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
// docs: 
// 1. https://dzone.com/articles/applying-curiously-recurring-template-pattern-in-c
// 2. https://zhuanlan.zhihu.com/p/408668787


#include <iostream>
#include <exception>
#include <stdexcept>

#include "cc_learning_test.h"

// 测试静态多态 (Static Polymorphism)
// 不需要使用虚函数即可实现多态功能
template <typename specific_animal>
struct animal {
    void who() { static_cast<specific_animal*>(this)->who();}
};

struct dog: animal<dog> {
    void who() { std::cout << "this is in dog!\n"; }
};

struct cat: animal<cat> {
    void who() { std::cout << "this is in cat!\n"; }
};

// animal模板会根据specific_animal变化
template <typename specific_animal>
void who_am_i(animal<specific_animal> tmp_animal) {
    tmp_animal.who();
}

// 测试静态多态
TEST(CCLearningTest, TestCRPTStaticPolymorphism) {
    std::cout << "使用CRPT技术测试静态多态\n";
    cat c;
    std::cout << "cat call whao_am_i: ";
    who_am_i(c);

    dog d;
    std::cout << "dog call whao_am_i: ";
    who_am_i(d);
}
/**
 * 结果
 * 
    使用CRPT技术测试静态多态
    cat call whao_am_i: this is in cat!
    dog call whao_am_i: this is in dog! 
 *
 */


// 对象计数
template <typename ToBeLimited, uint32_t maxInstance>
struct LimitNoOfInstances {
    static std::atomic<uint32_t> cnt;

    LimitNoOfInstances() {
        // 超过maxInstance则抛出异常
        if (cnt >= maxInstance)  {
            throw std::logic_error("too many instances");
        }
        ++cnt;
    }

    ~LimitNoOfInstances() { --cnt; }
};

struct One: LimitNoOfInstances<One, 1> {};
struct Two: LimitNoOfInstances<Two, 2> {};

template <typename T, uint32_t maxNoOfInstance>
// 两种初始化方式
// std::atomic<uint32_t> LimitNoOfInstances<T, maxNoOfInstance>::cnt(0);
std::atomic<uint32_t> LimitNoOfInstances<T, maxNoOfInstance>::cnt = 0;


// 测试实例计数
TEST(CCLearningTest, TestCRPTCountInstance) {

    // 不捕获异常，但是gtest会捕获异常
    // 设置gtest不捕获异常：--gtest_catch_exceptions=0
    // lldb
    // (lldb) file out/cc_learning_test
    // (lldb) r --gtest_filter=CCLearningTest.TestCRPTCountInstance --gtest_catch_exceptions=0
    // (lldb) bt
    // * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGABRT
    //   * frame #0: 0x00007ff818b7300e libsystem_kernel.dylib`__pthread_kill + 10
    //     frame #1: 0x00007ff818ba91ff libsystem_pthread.dylib`pthread_kill + 263
    //     frame #2: 0x00007ff818af4d24 libsystem_c.dylib`abort + 123
    //     ...
    //     frame #9: 0x00000001000094b0 cc_learning_test`LimitNoOfInstances<Two, 2u>::LimitNoOfInstances(this=0x00007ff7bfeff110) at CRPT_test.cc:64:13
    //     frame #10: 0x0000000100009445 cc_learning_test`Two::Two(this=0x00007ff7bfeff110) at CRPT_test.cc:73:8
    //     frame #11: 0x0000000100007b65 cc_learning_test`Two::Two(this=0x00007ff7bfeff110) at CRPT_test.cc:73:8
    //     frame #12: 0x00000001000079aa cc_learning_test`CCLearningTest_TestCRPTCountInstance_Test::TestBody(this=0x0000600000004160) at CRPT_test.cc:83:21
    //     frame #13: 0x000000010002d3fd cc_learning_test`void testing::internal::HandleExceptionsInMethodIfSupported<testing::Test, void>(testing::Test*, void (testing::Test::*)(), char const*) + 653
    //     frame #14: 0x000000010002d123 cc_learning_test`testing::Test::Run() + 195
    //     frame #15: 0x000000010002e182 cc_learning_test`testing::TestInfo::Run() + 290
    //     frame #16: 0x000000010002f25d cc_learning_test`testing::TestSuite::Run() + 317
    //     frame #17: 0x000000010003e8e0 cc_learning_test`testing::internal::UnitTestImpl::RunAllTests() + 1008
    //     frame #18: 0x000000010003e4c4 cc_learning_test`bool testing::internal::HandleExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, bool>(testing::internal::UnitTestImpl*, bool (testing::internal::UnitTestImpl::*)(), char const*) + 676
    //     frame #19: 0x000000010003e16b cc_learning_test`testing::UnitTest::Run() + 203
    //     frame #20: 0x0000000100072df1 cc_learning_test`RUN_ALL_TESTS() + 17
    //     frame #21: 0x0000000100072dcd cc_learning_test`main + 61
    //     frame #22: 0x000000010016552e dyld`start + 462
    Two _2_0, _2_1, _2_2;
    std::cout << "second test\n";

    // 测试捕获异常
    try {
        One _1_0, _1_1;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}