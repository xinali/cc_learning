// test vector
// docs: https://en.cppreference.com/w/cpp/container/vector/insert

// std::size (since C++ 17)

#include <iostream>
#include <iterator>
#include <vector>

#include "cc_learning_test.h"
 
void print(int id, const std::vector<int>& container)
{
    std::cout << id << ". ";
    for (const int x: container) {
         std::cout << x << ' ';
    }
    std::cout << '\n';
}

// run: ./TestVector --gtest_filter=CCLearningTest.TestVectorOverflow
// 关联的chromium bugs id: https://bugs.chromium.org/p/chromium/issues/detail?id=1196309
/* 样例:
==18252==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x603000001f58 at pc 0x000105f897f7 bp 0x7ff7b9f83620 sp 0x7ff7b9f83618
WRITE of size 4 at 0x603000001f58 thread T0
    #0 0x105f897f6 in void std::__1::allocator<int>::construct<int, int>(int*, int&&) memory:1881
    #1 0x105f8971f in void std::__1::allocator_traits<std::__1::allocator<int> >::__construct<int, int>(std::__1::integral_constant<bool, true>, std::__1::allocator<int>&, int*, int&&) memory:1773
    #2 0x105f8965a in void std::__1::allocator_traits<std::__1::allocator<int> >::construct<int, int>(std::__1::allocator<int>&, int*, int&&) memory:1600
    #3 0x105f89178 in std::__1::__split_buffer<int, std::__1::allocator<int>&>::push_back(int&&) __split_buffer:593
    #4 0x105f7e1c1 in std::__1::vector<int, std::__1::allocator<int> >::insert(std::__1::__wrap_iter<int const*>, int&&) vector:1826
    #5 0x105f7d9ed in CCLearningTest_TestVectorOverflow_Test::TestBody() vector_test.cc:27
    #6 0x105fe6b23 in void testing::internal::HandleSehExceptionsInMethodIfSupported<testing::Test, void>(testing::Test*, void (testing::Test::*)(), char const*) gtest.cc:2599
    #7 0x105fa8d1a in void testing::internal::HandleExceptionsInMethodIfSupported<testing::Test, void>(testing::Test*, void (testing::Test::*)(), char const*) gtest.cc:2635
    #8 0x105fa8c52 in testing::Test::Run() gtest.cc:2674
    #9 0x105fa9cc4 in testing::TestInfo::Run() gtest.cc:2853
    #10 0x105faae3d in testing::TestSuite::Run() gtest.cc:3012
    #11 0x105fba0ee in testing::internal::UnitTestImpl::RunAllTests() gtest.cc:5870
    #12 0x105febb53 in bool testing::internal::HandleSehExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, bool>(testing::internal::UnitTestImpl*, bool (testing::internal::UnitTestImpl::*)(), char const*) gtest.cc:2599
    #13 0x105fb9a7a in bool testing::internal::HandleExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, bool>(testing::internal::UnitTestImpl*, bool (testing::internal::UnitTestImpl::*)(), char const*) gtest.cc:2635
    #14 0x105fb994c in testing::UnitTest::Run() gtest.cc:5444
    #15 0x105f8f900 in RUN_ALL_TESTS() gtest.h:2293
    #16 0x105f8f8df in main gtest_main.cc:51
    #17 0x109ddf51d in start+0x1cd (dyld:x86_64+0x551d)
*/
TEST(CCLearningTest, TestVectorOverflow)
{
    std::vector<int> c1(3, 100);
    print(1, c1);
 
    // 测试溢出插入
    c1.insert(c1.begin()+10, 600);
}

// run: ./TestVector --gtest_filter=CCLearningTest.TestVectorInsert
TEST(CCLearningTest, TestVectorInsert)
{
    std::vector<int> c1(3, 100);
    print(1, c1);
 
    auto it = c1.begin();

    // 在最前面插入200
    it = c1.insert(it, 200);
    print(2, c1);
    
    // 在最前面插入2个300
    c1.insert(it, 2, 300);
    print(3, c1);

    // 插入之后，it依然指向begin
    // 验证过程
    std::string cut_line(50, '*');
    std::cout << cut_line << std::endl;
    
    std::cout << *it << std::endl;
    std::cout << *(it+1) << std::endl;
    std::cout << *(it+2) << std::endl;
    std::cout << *(it+3) << std::endl;
    std::cout << cut_line << std::endl;
 
    // `it` no longer valid, get a new one:
    it = c1.begin();
 
    std::vector<int> c2(2, 400);
    c1.insert(std::next(it, 2), c2.begin(), c2.end());
    print(4, c1);
 
    int arr[] = { 501,502,503 };
    c1.insert(c1.begin(), arr, arr + std::size(arr));
    print(5, c1);
 
    c1.insert(c1.end(), { 601,602,603 } );
    print(6, c1);
}