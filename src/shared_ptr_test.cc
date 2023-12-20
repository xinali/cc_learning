// test shared_ptr
// doc: https://en.cppreference.com/w/cpp/memory/shared_ptr
// compile && run: clang++ test_shared_ptr.cc --std=c++11 -o test.bin && ./test.bin

#include <iostream>
#include <memory>
#include <thread>
#include <chrono> 
#include <mutex>

void output(std::string out_str);

struct Base {
    Base() { std::cout << "Base::Base()\n"; }
    ~Base() { std::cout << "Base::~Base()\n"; }
};



struct Derived: public Base {
    Derived() { std::cout << "Derived::Derived()\n"; }
    ~Derived() { std::cout << "Derived::~Derived()\n"; }
};

void thr(std::shared_ptr<Base> p) {

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p;
    {

        // 静态变量，多个线程共享
        static std::mutex io_mutex;

        // 加锁
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "local pointer in a thread: \n"
                  << "  lp.get() = " << lp.get() 
                  << ", lp.use_count() = " << lp.use_count() << "\n";
    }
}

// void func_shared_ptr() {

//     std::shared_ptr<int> p1;
//     std::shared_ptr<int> p2(nullptr);
//     std::shared_ptr<int> p3(new int(10));

//     std::cout << p1 << std::endl;
//     std::cout << p2 << std::endl;
//     std::cout << p3 << std::endl;
// }


void test_class_shared() {
    std::shared_ptr<Base> p = std::make_shared<Derived>();

    std::cout << "Create a shared Derived (as a pointer to Base) \n"
              << "  p.get() = " << p.get() 
              << ", p.use_count() = " << p.use_count() << "\n";
    
    std::thread t1(thr, p), t2(thr, p), t3(thr, p);
    // p.reset();

    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';

    t1.join();
    t2.join(), 
    t3.join();
}