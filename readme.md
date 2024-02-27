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
cd /path/to/cc_learning/src
../tools/mac/gn gen out
../tools/mac/ninja -C out

# 测试
out/cc_learning_test --gtest_filter=CCLearningTest.TestCRPTCountInstance

# 或者直接使用运行脚本
./run.sh TestFactoryPattern
```

编译过程中可能会遇到`gn/ninja`或其他脚本错误`Permission denied`，这是因为没有执行权限，通过`chmod`赋予执行权限即可

```bash
chmod +x ../tools/mac/gn
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

> 目前优先学习在看chromium代码中遇到的设计模式

1. singleton 单例设计模式

    [参考](https://refactoringguru.cn/design-patterns/singleton/cpp/example)

    单例模式（Singleton Pattern）是一种常用的设计模式，用于确保一个类只有一个实例，并提供该实例的全局访问点。
    这种模式特别适用于当你需要确保全局只有一个对象的情况，如配置管理器、线程池或数据库连接池。

    单例模式的实现涉及以下几个关键点：
    私有化构造函数：确保不能从类外部实例化。
    提供一个私有静态属性：用于存放类的唯一实例。
    公开一个公共静态方法：用于获取这个唯一实例，如果实例不存在，则在方法内部创建。

2. factory 工厂设计模式

    工厂模式（Factory Pattern）属于创建型设计模式，用于创建对象而不需要指定对象具体的类。
    工厂模式主要分为三种：简单工厂模式（Simple Factory）、工厂方法模式（Factory Method）和抽象工厂模式（Abstract Factory）。
    这些模式在解耦对象的实例化过程中起到了关键作用，使得一个类的实例化延迟到其子类。

3. delegate 委托设计模式

    Delegate（委托）设计模式是一种对象行为模式，它允许对象外部通过一个代理对象来间接地调用另一个对象的方法或处理任务。
    这种模式主要用于解耦模块间的依赖关系，增加程序的灵活性和可扩展性。
    委托模式在软件开发中非常常见，尤其是在需要将任务或方法的执行从一个对象转移到另一个对象的场景中。

    基本概念：
    委托者（Delegator）：这是将要执行一个任务，但希望另一个对象（代理）来实现这个任务的对象。
    代理（Delegate）：这是实际执行任务的对象。委托者会将任务委托给代理，代理完成任务后可能会返回结果给委托者。
    客户端（Client）：这是使用委托者的对象，它不直接与代理交互。

    实现方法
    定义委托接口：这个接口声明了委托者要委托的方法。
    实现委托接口：一个或多个具体的代理类实现了委托接口，定义了具体的任务执行逻辑。
    在委托者中持有代理的引用：委托者类中包含一个指向代理对象的引用，通过这个引用来调用具体的任务执行方法。
    客户端通过委托者调用任务：客户端创建或获得一个委托者对象，并通过委托者来间接调用代理执行的任务。

    优点
    减少类之间的耦合度：委托模式可以将任务的执行从一个类转移到另一个类，从而降低类之间的直接依赖。
    增加程序的灵活性和可扩展性：通过改变代理类，可以在不修改委托者代码的情况下改变任务的执行逻辑，方便程序的扩展和维护。
    复用性和灵活性：代理对象可以被多个委托者复用，增加了代码的复用性；同时，代理逻辑的修改对委托者透明，提高了系统的灵活性。

    使用场景
    事件处理：如在GUI编程中，控件的事件处理（如按钮点击）经常使用委托模式，将事件的处理逻辑委托给专门的处理器。
    回调机制：在异步编程中，完成异步任务后的回调处理通常使用委托模式实现。
    代理模式的一种变体：在代理模式中，代理对象控制对另一个对象的访问，而委托模式更侧重于任务或方法的委托。


4. proxy 代理设计模式

    [参考](https://refactoringguru.cn/design-patterns/proxy/cpp/example)

    代理模式是软件设计模式中的一种，属于结构型模式。
    它通过创建一个代理对象来代表真实对象，这样就可以在不改变真实对象的前提下，通过代理对象来间接访问真实对象。
    这种模式主要用于控制对真实对象的访问，或在访问真实对象时添加一些额外的操作。代理模式通常用于实现懒加载、访问控制、日志记录、监控、智能指针等功能。

    代理模式主要包括以下几个组成部分：
    Subject（抽象主题角色）：一个接口，声明了真实主题和代理主题的共同接口。这样一来，任何使用真实主题的地方都可以使用代理主题。
    RealSubject（真实主题角色）：实现了 Subject 的接口的类，定义了代理所代表的真实对象。
    Proxy（代理主题角色）：同样实现了 Subject 的接口，用于代理访问 RealSubject。它维护一个对 RealSubject 类的引用，可以在访问 RealSubject 之前或之后执行一些操作。
    代理模式的类型
    代理模式根据使用目的可以分为以下几种类型：

    远程代理：为一个对象在不同的地址空间提供局部代表，这样可以隐藏一个对象存在于不同地址空间的事实。
    虚拟代理：根据需要创建开销很大的对象。通过它来存放实例化需要很长时间的真实对象。
    保护代理：控制对原始对象的访问。保护代理用于对象应该有不同的访问权限时。
    智能指引：当调用真实的对象时，代理处理另外一些事情，比如计算真实对象的引用次数，或者在访问对象时执行一些附加操作。

    代理模式和委托模式，我总是混淆，所以做如下的总结区分

    a. 代理模式（Proxy Pattern）
    代理模式主要用于控制对另一个对象的访问，这种控制可以是出于各种原因，如安全控制、延迟初始化、网络通信、日志记录等。

    代理模式通常涉及三个角色：
    主题（Subject）：定义了真实主题和代理的共同接口，让代理可以用来替代真实主题。
    真实主题（Real Subject）：定义了代理所代表的真实对象。
    代理（Proxy）：包含对真实主题的引用，控制对真实主题的访问，并可能负责其创建和删除。代理通常会对其服务的对象进行附加操作，然后调用真实主题的操作。

    b. 委托模式（Delegate Pattern）
    委托模式是一种允许对象将某个任务委托给外部函数或对象的行为型设计模式。它主要用于实现回调机制和事件处理。在委托模式中，有两个主要的参与者：

    委托者（Delegator）：负责将某些任务委托给委托对象的对象。
    委托对象（Delegate）：执行委托者交给它的任务。

    区别
    目的和用途：代理模式主要用于控制对对象的访问，而委托模式用于将任务或行为委托给另一个对象或方法。代理模式强调的是控制访问，而委托模式强调的是分离责任，将任务委托给其他组件。
    实现机制：在代理模式中，代理对象和真实对象实现相同的接口，代理对象内部通常会持有一个真实对象的引用，来间接访问或控制对真实对象的访问。而在委托模式中，委托者不需要和委托对象有共同的接口，委托者通过直接调用委托对象的方法来委托任务。
    控制层次：代理模式通常涉及到一个控制层次，即代理对象在访问真实对象之前或之后可以进行一些附加操作。委托模式更多地关注于行为的委托，不涉及控制真实对象的访问。

5. observer 观察者设计模式 

    [参考](https://refactoringguru.cn/design-patterns/observer/cpp/example)

    观察者模式（Observer Pattern）是一种行为设计模式，它定义了对象间的一种一对多的依赖关系，
    当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。
    观察者模式非常适用于事件处理系统、数据监控和通知机制等场景。

    观察者模式的组成
    主题（Subject）：维护一组观察者，提供用于增加和删除观察者的方法。当其内部状态改变时，主题对象通知所有注册过的观察者。
    观察者（Observer）：为所有具体观察者定义一个接口，在得到主题的通知时更新自己。
    具体主题（Concrete Subject）：存储与主题相关的状态。当状态改变时，向所有当前注册的观察者发出通知。
    具体观察者（Concrete Observer）：实现观察者接口的类，以便在主题状态改变时更新自身状态。