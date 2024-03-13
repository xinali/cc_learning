#include "cc_learning_test.h"

class TestUnique {
private:
    int *a = nullptr;
    int *b = nullptr;

public:
    void display() {
        if (a) {
            std::cout << "a is " << *a << std::endl;
        }
    }
    void set_a(int *c) {
        a = c;
    }
    void set_b(int *c) {
        b = c;
    }
};

// UAF
// test_a会在test_unique_raw结束时被释放
// 当test_unique再次访问a时，导致UAF
void test_unique_raw(TestUnique *test_unique) {
    std::unique_ptr<int> test_a = std::make_unique<int>(3);
    test_unique->set_a(test_a.get());
}

void test_weak_raw(TestUnique *test_unique) {
    std::shared_ptr<int> test_share = std::make_shared<int>(20);
    std::weak_ptr<int> test_b = test_share;
    // 这里就会出错，weak_ptr无法直接赋值给裸指针
    // test_unique->set_b(test_b);
}

// ./run.sh TestUniqueRawPtr
TEST(CCTest, TestUniqueRawPtr) {
    TestUnique *test_unique = new TestUnique();
    test_unique_raw(test_unique);
    test_unique->display();
    delete test_unique;
}