#include "../cc_learning_test.h"

class Image {
public:
    virtual void display() = 0;
    virtual ~Image(){};
};

class RealImage : public Image {
public:
    void display() override {
        std::cout << "RealImage display" << std::endl;
    }
};

class ProxyImage : public Image {
public:
    void display() override {
        if (real_image == nullptr) {
            real_image = new RealImage();
        }
        // 代理做完相关控制会调用真正的实现类
        real_image->display();
    }
    ~ProxyImage() override {
        delete real_image;
    }

private:
    RealImage *real_image;
};

TEST(CCTest, TestProxyPattern) {
    // 使用代理类作相关控制
    Image *image = new ProxyImage();
    image->display();
    delete image;
}