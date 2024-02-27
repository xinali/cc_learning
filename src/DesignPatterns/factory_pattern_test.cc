/*
工厂设计模式（Factory Pattern）在C++中用于创建对象，
而不需要将对象的创建逻辑暴露给客户端。工厂方法通过定义一个创建对象的接口，
但让子类决定要实例化哪一个类，从而将对象的实例化推迟到子类进行。
这样做的主要目的是增加代码的灵活性和扩展性，使得添加新的类或改变对象的创建逻辑时，
不需要修改现有代码。

该源码测试了工厂模式以及unique_prt/shared_ptr的区别
*/
#include "../cc_learning_test.h"

class Animal {
public:
    // virtual void speak() { std::cout << "all animal speak!\n"; };
    virtual void speak() = 0;
    // 需要定义虚的析构函数，否则unique_ptr析构时无法找到
    // warnning: delete called on 'Animal' that is abstract but has non-virtual destructor
    virtual ~Animal(){};
};

class Cat : public Animal {
public:
    void speak() override { std::cout << "meow\n"; };
    ~Cat(){};
};

class Dog : public Animal {
public:
    void speak() override { std::cout << "wang\n"; }
    ~Dog(){};
};

class AnimalFactory {
public:
    // 不满足工类的定义
    // void createAnimal(const std::string &type) {
    //     if (type == "Dog") {
    //         Dog *dog = new Dog();
    //         dog->speak();
    //     }
    //     if (type == "Cat") {
    //         Cat *cat = new Cat();
    //         cat->speak();
    //     }
    // }

    // 设置创建对象的接口
    static Animal *createAnimal(const std::string &type) {
        if (type == "dog") {
            return new Dog();
        }
        if (type == "cat") {
            return new Cat();
        } else {
            return nullptr;
        }
    }
};

// ./run.sh TestFactoryPattern
TEST(CCLearningTest, TestFactoryPattern) {
    // AnimalFactory *factory = new AnimalFactory();
    // factory->createAnimal("Dog");

    // 这里存在隐式转换，所以会有报错，unique_prt不允许隐式转换
    // std::unique_ptr<Animal> cat = AnimalFactory::createAnimal("cat");
    // 这里直接使用的是unique_ptr提供的构造函数
    std::unique_ptr<Animal> cat(AnimalFactory::createAnimal("cat"));
    std::unique_ptr<Animal> dog(AnimalFactory::createAnimal("dog"));

    cat->speak();
    dog->speak();

    // 无法引用，已被删除，只能有一个指针
    // std::unique_ptr<Animal> cat1 = cat;

    // shared_prt可以有多个指针，在将其所有指针删除时才会删除对象
    std::shared_ptr<Animal> cat_shared(AnimalFactory::createAnimal("cat"));
    cat_shared->speak();
    std::shared_ptr<Animal> cat_2 = cat_shared;
    cat_2->speak();

    // delete cat;
    // delete dog;
}