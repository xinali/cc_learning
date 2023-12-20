# cc_learning

平常学习`c/c++`过程中，练习代码记录，代码可能来源于`blog/docs`等，不讲原理性的内容，
所有均在代码注释中加入个人理解说明，因为目前主要在学习浏览器相关的内容，所以构建组件选择`gn+ninja`
其中很多代码来源于学习`《C++ Primer》`

## 测试环境

```
# linux/mac
gn + ninja + clang
```

`build`配置文件来自于[gn-build](https://github.com/timniederhausen/gn-build)，其中拿掉了对`ios`和`andriod`的支持，
并根据自己的需求做了部分定制化的更改

## 编译测试

`mac`环境

```bash
git clone --recurse-submodules https://github.com/xinali/cc_learning

# 编译googletest
cd /path/to/cc_learning/third_party/googletests
cmake . -B build
cd build && make

# 编译本项目
cd /path/to/cc_learning
third_party/tools/mac/gn gen out
third_party/tools/mac/ninja -C out

# 测试
out/cc_learning_test --gtest_filter=CCLearningTest.TestCRPTCountInstance
```

## 添加测试用例

添加测试用例分为三步

1. 引入头文件 `#include "cc_learning_test.h"`
2. 编写测试用例，在`TEST`函数中集成`CCLearningTest`
3. 在测试文件`run_all_test.cc`中添加`#include "xxx_test.cc"`

添加完测试用例，直接编译指令即可

## 已学习

- [x] std::forword
- [x] std::shared_ptr
- [x] static_cast
- [x] std::unique_ptr
- [x] std::weak_ptr
- [x] rvalue
- [x] std::iterator
- [x] std::vector
- [x] thread_local


## 计划学习

- [ ] c++ CRPT (v8 fast properties example)
- [ ] c++ nested class design (v8 ElementsAccessor -> InternalElementsAccessor)
- [ ] dynamic_cast
- [ ] const_cast
- [ ] reinterpret_cast
- [ ] std::optional value reference
- [ ] lazy initialization (Lazy init and Multi-threading -> chromium)
- [ ] c++ callback (https://zhuanlan.zhihu.com/p/88434924)
- [ ] c++ proxy delegate (https://chromium-review.googlesource.com/c/chromium/src/+/590913/#:~:text=Let%27s%20try%20making-,proxy%20delegate,-always%20there.%0A%0AIn) 来源于看chromium实现headless download manager
- [ ] chromium demo (https://github.com/keyou/chromium_demo)

### 设计模式

#### 未完成 

> 目前优先学习在看chromium代码中遇到的设计模式

- [ ] singleton design pattern (https://refactoringguru.cn/design-patterns/singleton/cpp/example)
- [ ] proxy design pattern (https://refactoringguru.cn/design-patterns/proxy/cpp/example)
- [ ] factory design pattern

#### 已完成

- [x] observer pattern (https://refactoringguru.cn/design-patterns/observer/cpp/example)