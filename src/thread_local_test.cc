
#include "cc_learning_test.h"
#include <thread>
#include <mutex>

namespace CCLearningTestSpace {

namespace TestThreadLocalSpace {

std::mutex cout_mutex;

// 直接使用static，不使用thread_local
void thread_func0(const std::string& thread_name) {
    for (int i = 0; i < 3; ++i) {
        // 初始化一次，所有线程共享
        static int x = 1;
        x++;
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "thread[" << thread_name << "]: x = " << x << std::endl;
    }
    return;
}

TEST(CCLearningTest, TestThreadLocalVSStatic) { 
    std::cout << "测试只使用static，不使用thread_local" << std::endl;
    std::thread t1(thread_func0, "t1");
    std::thread t2(thread_func0, "t2");

    t1.join();
    t2.join(); 
}
/**
 * 结果
    测试只使用static，不使用thread_local
    thread[t1]: x = 2
    thread[t1]: x = 3
    thread[t1]: x = 4
    thread[t2]: x = 5
    thread[t2]: x = 6
    thread[t2]: x = 7
*/


thread_local int func1_g_x = 1;
void thread_func1(const std::string& thread_name) {
    for (int i = 0; i < 3; ++i) {
        // 各个线程初始值相同，但是变化，互相不影响
        func1_g_x++;
        // RALL，创建即获取mutext
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "thread[" << thread_name << "]: x = " << func1_g_x << std::endl;
        // 自动释放mutext
    }
}

// 测试使用thread_local定义的全局变量，在多线程中的变化
TEST(CCLearningTest, TestThreadLocalGlobal)
{
    std::cout << "测试全局thread_local变量，线程间独立" << std::endl;
    std::thread t1(thread_func1, "t1");
    std::thread t2(thread_func1, "t2");

    t1.join();
    t2.join();
}

/**
 * 测试全局thread_local变量，线程间独立
    thread[t1]: x = 2
    thread[t1]: x = 3
    thread[t1]: x = 4
    thread[t2]: x = 2
    thread[t2]: x = 3
    thread[t2]: x = 4
 */


// 测试局部thread_local变量，在线程间的变化
void thread_func2(const std::string& thread_name) {
    for (int i = 0; i < 3; ++i) {
        // 每个线程初始化一次，独立变化，与全局变量不同的是，全局变量初始化一次
        thread_local int x = 1;
        x++;
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "thread[" << thread_name << "]: x = " << x << std::endl;
    }
    return;
}


TEST(CCLearningTest, TestThreadLocal)
{
    std::cout << "测试线程局部thread_local变量" << std::endl;
    std::thread t1(thread_func2, "t1");
    std::thread t2(thread_func2, "t2");
    t1.join();
    t2.join();
}
/**
 * 测试线程局部thread_local变量
    thread[t1]: x = 2
    thread[t1]: x = 3
    thread[t1]: x = 4
    thread[t2]: x = 2
    thread[t2]: x = 3
    thread[t2]: x = 4
 */


// 无thread_local
void thread_func3(const std::string& thread_name) {
    for (int i = 0; i < 3; ++i) {
        // 函数每次执行都初始化，所以每次输出均是2
        int x = 1;
        x++;
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "thread[" << thread_name << "]: x = " << x << std::endl;
    }
    return;
}


TEST(CCLearningTest, TestNOThreadLocal)
{
    std::cout << "测试无thread_local变量" << std::endl;
    std::thread t1(thread_func3, "t1");
    std::thread t2(thread_func3, "t2");
    t1.join();
    t2.join();
}

/**
 * 测试无thread_local变量
    thread[t1]: x = 2
    thread[t1]: x = 2
    thread[t1]: x = 2
    thread[t2]: x = 2
    thread[t2]: x = 2
    thread[t2]: x = 2
 */


class A {
public:
    A() {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "create A" << std::endl;
    }

    ~A() {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "destroy A" << std::endl;
    }

    int counter = 0;
    int get_value() {
        return counter++;
    }
};

// 测试使用thread_local声明类实例
// 每个线程中的类实例独立计数
void thread_func4(const std::string& thread_name) {
    for (int i = 0; i < 3; ++i) {
        // 跟上面的测试一样，只会测试一次
        thread_local A* a = new A();
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "thread[" << thread_name << "]: a.counter:" << a->get_value() << std::endl;
    }
    return;
}

TEST(CCLearningTest, TestThreadLocalClass) {
    std::cout << "测试使用thread_local计算类实例\n";
    std::thread t1(thread_func4, "t1");
    std::thread t2(thread_func4, "t2");
    t1.join();
    t2.join();
}
/**
 * 结果
    create A
    thread[t1]: a.counter:0
    thread[t1]: a.counter:1
    thread[t1]: a.counter:2
    create A
    thread[t2]: a.counter:0
    thread[t2]: a.counter:1
    thread[t2]: a.counter:2
*/


class B {
public:
    B() {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "create B" << std::endl;
    }
    ~B() {}
    // 必须使用static声明，否则出错
    thread_local static int b_key;
    // thread_local int b_key; // 编译错误
    int b_value = 24;
    // 所有线程共享
    static int b_static;
};

// 每个线程初始化一次
thread_local int B::b_key = 12;
// 所有线程初始化一次
int B::b_static = 36;

// 测试thread_local定义类的成员变量
void thread_func5(const std::string& thread_name) {
    B b;
    for (int i = 0; i < 3; ++i) {
        b.b_key--;
        b.b_value--;
        b.b_static--;   // not thread safe
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "thread[" << thread_name << "]: b_key:" << b.b_key 
                 << ", b_value:" << b.b_value << ", b_static:" << b.b_static << std::endl;
        std::cout << "thread[" << thread_name << "]: B::key:" << B::b_key 
                  << ", b_value:" << b.b_value << ", b_static: " << B::b_static << std::endl;
    }
}

TEST(CCLearningTest, TestThreadLocalClassVar) {
    std::cout << "测试thread_local声明类变量\n";

    std::thread t1(thread_func5, "t1");
    std::thread t2(thread_func5, "t2");
    t1.join();
    t2.join();
}

} // TestThreadLocalSpace
} // CCLearningTest