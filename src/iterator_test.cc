// 测试std::iterator
// docs: https://en.cppreference.com/w/cpp/iterator/iterator

#include <iostream>
#include <algorithm>

#include "inc/cc_learning_test.h"

template<long FROM, long TO>
class Range {
public:
    class iterator: public std::iterator<
                            std::input_iterator_tag, // iterator_category
                            long,                    // value_type
                            long,                    // difference_type
                            const long*,             // pointer
                            long                     // reference
                            > 
    { 
        long num = FROM;
        public:
            explicit iterator(long _num = 0): num(_num) {};
            iterator& operator++() {num = TO >= FROM ? num + 1: num - 1; return *this; }
            iterator operator++(int) {iterator retval = *this; ++(*this); return retval; }
            bool operator==(iterator other) const { return num == other.num; }
            bool operator!=(iterator other) const { return !(*this == other); }

            reference operator*() const { return num; }
    };

    iterator begin() { return iterator(FROM); }
    iterator end() { return iterator(TO >= FROM ? TO + 1: TO - 1); }
};


// make && ./TestIterator --gtest_filter=CCLearningTest.TestIterator
TEST(CCLearningTest, TestIterator) 
{
    auto range = Range<15, 25>();
    auto itr = std::find(range.begin(), range.end(), 18);
    std::cout << *itr << std::endl;

    for (long l: Range<3, 5>()) {
        std::cout << l << std::endl;
    }
}