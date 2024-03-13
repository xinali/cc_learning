
#include "test_const.h"
#include "test_const_var.h"

// void test_extern_const() {
//   std::cout << "a value: " << a << std::endl;
//   std::cout << "var value: " << var << std::endl;
//   // std::cout << "var value: " << var_local << std::endl;
// }

// // 测试const引用
// void test_const_reference() {

//   const int a = 1;
//   const int &ra = a;

//   int b = 1;
//   int &rb = b;
//   int c = 2;
//   // 可以更改引用指向
//   rb = c;
//   // ra = c; ra为const reference(read only)

//   std::cout << "a value: " << std::endl;
//   std::cout << "ra value: " << ra << std::endl;

//   std:: cout << "rb value: " << rb << std::endl;
// }

// // 测试初始化和const
// void test_init_const() {

//   int a = 1;
//   // const引用
//   const int &ra = a;

//   std::cout << "a value: " << a << std::endl;
//   std::cout << "ra value: " << ra << std::endl;

//   a = 3;
//   std::cout << "a value: " << a << std::endl;
//   std::cout << "ra value: " << ra << std::endl;

//   int b = 4;
//   // ra = b; 出错，const引用

//   int c = 1;
//   // 非const引用
//   int &rc = c;

//   int d = 1111;
//   rc = d;

//   std::cout << "c value: " << c << std::endl;
//   std::cout << "d value: " << d << std::endl;
//   std::cout << "rc value: " << rc << std::endl;

//   /*
//   result:
//     c value: 1111
//     d value: 1111
//     rc value: 1111
//   */
// }

// // 测试const和指针
// void test_pointer_const() {
//   int a = 1;
//   const int *p = &a;
//   // *p = 3; 错误，p为const指针，不能改变其值
//   int b = 3;
//   p = &b; // 正确，p为const指针，但是可以改变其指向

//   const int var_c = 1;
//   const int *p_var = &var_c;

//   // *p_var = 2; 错误

//   const int var_d = 2;
//   p_var = &var_d;

// }

// // 测试const指针
// void test_const_pointer() {
//   int a = 1;
//   int *const pa = &a;

//   a = 3;
//   std::cout << "a value: " << a << std::endl;
//   std::cout << "pa value: " << *pa << std::endl;

//   *pa = 5; // const指针，pa的值可以改变
//   std::cout << "a value: " << a << std::endl;
//   std::cout << "pa value: " << *pa << std::endl;

//   int b = 2;
//   // pa = b; // const指针，其本身不可以改变

//   const int c = 3;
//   const int *const pc = &c;
//   const int d = 4;
//   // pc = &d; 错误，pc为const类型，不可以变
//   // *pc = 5; 错误，*pc为const int类型，不可以变
// }

TEST(CCTest, TestConstexpr) {
    int a = 1;
    constexpr int b = 2;
    // constexpr int c = a; 错误，a不是常量表达式
    const int d = 4;
    constexpr int e = d; // 正确，d为const常量
    std::cout << "e value: " << e << std::endl;
}
