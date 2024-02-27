
#include "../cc_learning_test.h"

#include <iostream>
#include <functional>

// 委托接口
class IDelegate {
public:
    virtual void Execute() = 0;
};

// 具体执行者类
class ConcreteTask {
public:
    void PerformTask() {
        std::cout << "Performing Concrete Task." << std::endl;
    }
};

// 委托类
class Delegate : public IDelegate {
private:
    // std::function作为类成员变量，增加灵活性
    std::function<void()> callbackFunction;

public:
    Delegate(std::function<void()> function) :
        callbackFunction(function) {}
    void Execute() override { callbackFunction(); }
};

// ./run.sh TestDelegatePattern
TEST(CCLearningTest, TestDelegatePattern) {
    ConcreteTask task;
    // lambda 表达式捕获task引用
    // delegate 将具体的任务委托为task去执行
    Delegate delegate([&task]() { task.PerformTask(); });
    delegate.Execute();
}
