#include "cc_learning_test.h"

class Book
{
    int mCount{1};
    std::string mName;

public:
    std::string &get_name()
    {
        return mName;
    }
    Book(std::string iName) : mName(iName) {}
    Book(Book &&iBook)
    {
        swap(this->mName, iBook.mName);
        mCount = 3;
    }
    int get_count()
    {
        return mCount;
    }
};

TEST(CCLearningTest, TestMoveFunc)
{
    Book b("Im");
    Book tb = std::move(b);
    std::cout << "old b name is " << b.get_name() << " count is " << b.get_count();
    std::cout << "\ntb name is " << tb.get_name() << " count is " << tb.get_count();

    std::string s("test string");
    std::string sb = std::move(s);
    std::cout << "s is: " << s << std::endl;
    std::cout << "sb is: " << sb << std::endl;
}