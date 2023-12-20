#include "cc_learning_test.h"

namespace cc_learning_test
{

    namespace unique_ptr_test
    {

        class Base
        {
        public:
            virtual void foo() const = 0;
            virtual void bar() const = 0;

            virtual ~Base();
        };

        class Derived : public Base
        {
        public:
            void foo() const override
            {
                std::cout << "foo" << std::endl;
            };

            void bar() const override
            {
                std::cout << "bar" << std::endl;
            };
        };

        // 构造虚函数unique_ptr
        TEST(CCLearningTest, UniquePtrVirtualInit)
        {

            // Constructs a std::unique_ptr that owns nothing
            // 默认会构造一个空指针
            // std::unique_ptr<Base> base_ptr;

            // EXPECT_EQ(base_ptr, nullptr);

            // std::cout << base_ptr;
            // std::unique_ptr<std::vector<std::string>> base_strs = new (std::vector<std::string>);
            // base_strs->append("test");
        }

        void test_func1()
        {
            std::unique_ptr<int> p5(new int);
            *p5 = 10;
            int *p = p5.release();

            if (p5 == nullptr)
            {
                std::cout << "p5 is null\n";
            }
            else
            {
                std::cout << "p5 is not null\n";
            }
            std::unique_ptr<int> p6;
            p6.reset(p);
            std::cout << *p6 << std::endl;
        }

    } // unique_ptr_test

} // cc_learning_test