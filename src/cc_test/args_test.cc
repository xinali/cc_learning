#include "cc_learning_test.h"

template <typename T, typename... Args>
void print(T t, Args... args)
{
    std::cout << t << std::endl;
    print(args...);
}

template <typename T>
void print(T t)
{
    std::cout << t << std::endl;
}

int main()
{
    print(1, 2.0, "hello", 'c');
    return 0;
}