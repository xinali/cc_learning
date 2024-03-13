/**
 * 一个简单的支付行为模式样例代码
 **/

#include "../cc_learning_test.h"

// 策略接口
// 支付方式
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual void pay(int amount) = 0;
};

// 具体策略
// 信用卡支付
class CreditPayment : public PaymentStrategy {
public:
    CreditPayment(const std::string name, const std::string &id) :
        name_(name), id_(id){};

    void pay(int amount) {
        std::cout << "pay " << amount << " by credit payment." << std::endl;
    }

private:
    std::string name_;
    std::string id_;
};

// 具体策略
// paypal支付
class PaypalPayment : public PaymentStrategy {
public:
    PaypalPayment(const std::string &email) :
        email_(email){};
    void pay(int amount) {
        std::cout << "pay " << amount << " by paypal payment." << std::endl;
    }

private:
    std::string email_;
};

// 上下文
class PayContext {
public:
    void set_pay_method(std::unique_ptr<PaymentStrategy> pay_method) {
        pay_method_ = std::move(pay_method);
    }
    void pay(int amount) {
        pay_method_->pay(amount);
    }

private:
    std::unique_ptr<PaymentStrategy> pay_method_;
};

// ./run.sh TestStrategy
TEST(CCTest, TestStrategy) {
    PayContext pay_context;
    std::unique_ptr<CreditPayment> credit_pay = std::make_unique<CreditPayment>("credit_card", "11111111");
    std::unique_ptr<PaypalPayment> paypal_pay = std::make_unique<PaypalPayment>("test@g.com");

    pay_context.set_pay_method(std::move(credit_pay));
    pay_context.pay(10);

    pay_context.set_pay_method(std::move(paypal_pay));
    pay_context.pay(20);
}