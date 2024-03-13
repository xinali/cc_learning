// 测试观察者设计模式
// docs: https://refactoring.guru/design-patterns/observer/cpp/example

/**
 * Observer Design Pattern 观察者模式
 * 一般是一对多，当被观察者发生变更时，被观察者会枚举观察者列表，依次通知观察者
 * 观察者才有退出，被观察者只是更新数据/状态
 */

#include <iostream>
#include <list>
#include <string>

#include "../cc_learning_test.h"

// 观察者基类
class IObserver {
public:
    virtual ~IObserver(){};
    virtual void Update(const std::string &message_from_subject) = 0;
};

// 主题基类 (被观察者)
class ISubject {
public:
    virtual ~ISubject(){};
    // 附加
    virtual void Attach(IObserver *observer) = 0;
    // 解附
    virtual void Detach(IObserver *observer) = 0;
    // 通知
    virtual void Notify() = 0;
};

class Subject : public ISubject {
public:
    virtual ~Subject() {
        std::cout << "Goodbye, I was the Subject.\n";
    }

    void Attach(IObserver *observer) override {
        list_observer_.push_back(observer);
    }

    void Detach(IObserver *observer) override {
        list_observer_.remove(observer);
    }

    void Notify() override {
        std::list<IObserver *>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        // 通知所有观察者
        while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(std::string message = "Empty") {
        this->message_ = message;
        Notify();
    }

    void HowManyObserver() {
        std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
    }

    void SomeBusinessLogic() {
        this->message_ = "change message message";
        Notify();
        std::cout << "I'm about to do some thing important\n";
    }

private:
    // 观察者链
    std::list<IObserver *> list_observer_;
    // 消息
    std::string message_;
};

class Observer : public IObserver {
public:
    Observer(Subject &subject) :
        subject_(subject) {
        this->subject_.Attach(this);
        std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }

    virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
    }

    void Update(const std::string &message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }

    void RemoveMeFromTheList() {
        subject_.Detach(this);
        std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }

    void PrintInfo() {
        std::cout << "Observer \"" << this->number_
                  << "\": a new message is available --> "
                  << this->message_from_subject_ << "\n";
    }

private:
    // 消息
    std::string message_from_subject_;

    // 观察者存储被观察者
    Subject &subject_;

    // 通过静态变量确定该观察者编号 (所有线程共享)
    static int static_number_;

    // 特定观察者编号
    int number_;
};

// 观察者初始编号
int Observer::static_number_ = 0;

// ./run.sh TestObserverPattern
TEST(CCTest, CCTestserverPattern) {
    // 一个被观察者即可
    Subject *subject = new Subject;

    // 观察者在创建时，根据传入的被观察者，自动加入观察者列表
    Observer *observer1 = new Observer(*subject);
    Observer *observer2 = new Observer(*subject);
    Observer *observer3 = new Observer(*subject);
    Observer *observer4;
    Observer *observer5;

    // 所有操作均由观察者完成，被观察者只负责更新状态
    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today! :p");
    observer4 = new Observer(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);

    subject->CreateMessage("My new car is great! ;)");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    delete subject;

    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    // delete subject;
}